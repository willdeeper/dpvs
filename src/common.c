/*
 * DPVS is a software load balancer (Virtual Server) based on DPDK.
 *
 * Copyright (C) 2017 iQIYI (www.iqiyi.com).
 * All Rights Reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <net/ethernet.h>
#include "common.h"

struct dpvs_err_tab {
    int errcode;
    const char *errmsg;
};

const char *dpvs_strerror(int err)
{
    /* TODO: "per-lcorelize" it */
    const static struct dpvs_err_tab err_tab[] = {
        { EDPVS_OK,             "OK" },
        { EDPVS_INVAL,          "invalid parameter" },
        { EDPVS_NOMEM,          "no memory" },
        { EDPVS_EXIST,          "already exist" },
        { EDPVS_NOTEXIST,       "not exist" },
        { EDPVS_INVPKT,         "invalid packet" },
        { EDPVS_DROP,           "packet dropped" },
        { EDPVS_DPDKAPIFAIL,    "failed dpdk api" },
        { EDPVS_IDLE,           "nothing to do" },
        { EDPVS_BUSY,           "resource busy" },
        { EDPVS_NOTSUPP,        "not support" },
        { EDPVS_OVERLOAD,       "overloaded" },
        { EDPVS_NOSERV,         "no service" },
        { EDPVS_DISABLED,       "disabled" },
        { EDPVS_NOROOM,         "no room" },
        { EDPVS_NONEALCORE,     "non-EAL thread lcore" },
        { EDPVS_CALLBACKFAIL,   "callback failed" },
        { EDPVS_IO,             "I/O error" },
        { EDPVS_MSG_FAIL,       "msg callback failed"},
        { EDPVS_MSG_DROP,       "msg dropped"},
        { EDPVS_SYSCALL,        "system call failed"},
        { EDPVS_KNICONTINUE,    "kni to continue"},
        { EDPVS_PKTSTOLEN,      "stolen packet"},
        { EDPVS_INPROGRESS,     "in progress"},
        { EDPVS_NODEV,          "no such device"},
    };
    int i;

    for (i = 0; i < NELEMS(err_tab); i++) {
        if (err == err_tab[i].errcode)
            return err_tab[i].errmsg;
    }

    return "<unknow>";
}

static dpvs_state_t g_dpvs_tate = DPVS_STATE_STOP;

void dpvs_state_set(dpvs_state_t stat)
{
    g_dpvs_tate = stat;
}

dpvs_state_t dpvs_state_get(void)
{
    return g_dpvs_tate;
}

/* if (num+offset) == 2^n, return true,
 * otherwise return false and 'lower' is filled with
 * the closest lower bound value to 'num' */
bool is_power2(int num, int offset, int *lower)
{
    int i, onum;
    bool ret = true;

    onum = num + offset;
    if (num < 2 || onum < 2) {
        if (lower)
            *lower = num;
        return false;
    }

    for (i = 1; (onum >> i) > 1;i++) {
        if ((onum >> i) % 2) {
            ret = false;
        }
    }

    if (lower)
        *lower = (1u << i);
    return ret;
}

int linux_set_if_mac(const char *ifname, const unsigned char mac[ETH_ALEN])
{
    int sock_fd;
    struct ifreq ifr = {};

    if (!ifname || !mac || !strncmp(ifname, "lo", 2))
        return EDPVS_INVAL;

    sock_fd = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock_fd < 0)
        return EDPVS_SYSCALL;

    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), "%s", ifname);
    ifr.ifr_hwaddr.sa_family = 1;
    memcpy(ifr.ifr_hwaddr.sa_data, mac, ETH_ALEN);

    if (ioctl(sock_fd, SIOCSIFHWADDR, &ifr)) {
        close(sock_fd);
        return EDPVS_SYSCALL;
    }

    close(sock_fd);
    return EDPVS_OK;
}

static int linux_hw_mc_mod(const char *ifname,
                           const uint8_t hwma[ETH_ALEN], bool add)
{
    int fd, cmd;
    struct ifreq ifr = {};

    snprintf(ifr.ifr_name, IFNAMSIZ, "%s", ifname);
    memcpy(&ifr.ifr_hwaddr.sa_data, hwma, ETH_ALEN);

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd < 0)
        return EDPVS_SYSCALL;

    cmd = add ? SIOCADDMULTI : SIOCDELMULTI;
    if (ioctl(fd, cmd, (void *)&ifr) != 0) {
        fprintf(stderr, "%s: fail to set link mcast to %s: %s\n",
                __func__, ifname, strerror(errno));
        close(fd);
        return EDPVS_SYSCALL;
    }

    close(fd);
    return 0;
}

int linux_hw_mc_add(const char *ifname, const uint8_t hwma[ETH_ALEN])
{
    return linux_hw_mc_mod(ifname, hwma, true);
}

int linux_hw_mc_del(const char *ifname, const uint8_t hwma[ETH_ALEN])
{
    return linux_hw_mc_mod(ifname, hwma, false);
}