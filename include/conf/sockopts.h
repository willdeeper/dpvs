/*
 * DPVS is a software load balancer (Virtual Server) based on DPDK.
 *
 * Copyright (C) 2021 iQIYI (www.iqiyi.com).
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
#ifndef __DPVS_SOCKOPTS_CONF_H__
#define __DPVS_SOCKOPTS_CONF_H__

#include <conf/common.h>

enum {
    /* laddr */
    SOCKOPT_SET_LADDR_ADD    = 100,
    SOCKOPT_SET_LADDR_DEL,
    SOCKOPT_SET_LADDR_FLUSH,
    SOCKOPT_GET_LADDR_GETALL = 100,
#define SOCKOPT_LADDR_BASE     SOCKOPT_SET_LADDR_ADD
#define SOCKOPT_GET_LADDR_MAX  199

    /* service */
    DPVS_SO_SET_FLUSH   = 200,
    DPVS_SO_SET_ZERO,
    DPVS_SO_SET_ADD,
    DPVS_SO_SET_EDIT,
    DPVS_SO_SET_DEL,
    DPVS_SO_SET_ADDDEST,
    DPVS_SO_SET_EDITDEST,
    DPVS_SO_SET_DELDEST,
    DPVS_SO_SET_GRATARP,
    DPVS_SO_GET_VERSION = 200,
    DPVS_SO_GET_INFO,
    DPVS_SO_GET_SERVICES,
    DPVS_SO_GET_SERVICE,
    DPVS_SO_GET_DESTS,
#define SOCKOPT_SVC_BASE         DPVS_SO_SET_FLUSH
#define SOCKOPT_SVC_SET_CMD_MAX  DPVS_SO_SET_GRATARP
#define SOCKOPT_SVC_GET_CMD_MAX  DPVS_SO_GET_DESTS
#define SOCKOPT_SVC_MAX          299

    /* route */
    SOCKOPT_SET_ROUTE_ADD   = 300,
    SOCKOPT_SET_ROUTE_DEL,
    SOCKOPT_SET_ROUTE_SET,
    SOCKOPT_SET_ROUTE_FLUSH,
    SOCKOPT_GET_ROUTE_SHOW  = 300,

    /* ifaddr */
    SOCKOPT_SET_IFADDR_ADD  = 400,
    SOCKOPT_SET_IFADDR_DEL,
    SOCKOPT_SET_IFADDR_SET,
    SOCKOPT_SET_IFADDR_FLUSH,
    SOCKOPT_GET_IFADDR_SHOW = 400,

    /* netif */
    SOCKOPT_NETIF_SET_LCORE      = 500,
    SOCKOPT_NETIF_SET_PORT,
    SOCKOPT_NETIF_SET_BOND,
    SOCKOPT_NETIF_SET_MAX,
    SOCKOPT_NETIF_GET_LCORE_MASK = 500,
    SOCKOPT_NETIF_GET_LCORE_BASIC,
    SOCKOPT_NETIF_GET_LCORE_STATS,
    SOCKOPT_NETIF_GET_PORT_LIST,
    SOCKOPT_NETIF_GET_PORT_BASIC,
    SOCKOPT_NETIF_GET_PORT_STATS,
    SOCKOPT_NETIF_GET_PORT_EXT_INFO,
    SOCKOPT_NETIF_GET_BOND_STATUS,
    SOCKOPT_NETIF_GET_MAX,

    /* neigh */
    SOCKOPT_SET_NEIGH_ADD     = 600,
    SOCKOPT_SET_NEIGH_DEL,
    SOCKOPT_GET_NEIGH_SHOW    = 600,

    /* blklst */
    SOCKOPT_SET_BLKLST_ADD    = 700,
    SOCKOPT_SET_BLKLST_DEL,
    SOCKOPT_SET_BLKLST_FLUSH,
    SOCKOPT_GET_BLKLST_GETALL = 700,

    /* vlan */
    SOCKOPT_SET_VLAN_ADD  = 800,
    SOCKOPT_SET_VLAN_DEL,
    SOCKOPT_GET_VLAN_SHOW = 800,

    /* tc */
    SOCKOPT_TC_ADD  = 900,
    SOCKOPT_TC_DEL,
    SOCKOPT_TC_CHANGE,
    SOCKOPT_TC_REPLACE,
    SOCKOPT_TC_SHOW = 900,

    /* connection */
    SOCKOPT_SET_CONN     = 1000,
    SOCKOPT_GET_CONN_ALL = 1000,
    SOCKOPT_GET_CONN_SPECIFIED,

    /* ip6 */
    SOCKOPT_IP6_SET   = 1100,
    SOCKOPT_IP6_STATS = 1100,

    /* tunnel */
    SOCKOPT_TUNNEL_ADD  = 1200,
    SOCKOPT_TUNNEL_DEL,
    SOCKOPT_TUNNEL_CHANGE,
    SOCKOPT_TUNNEL_REPLACE,
    SOCKOPT_TUNNEL_SHOW = 1200,

    /* whtlst */
    SOCKOPT_SET_WHTLST_ADD = 1300,
    SOCKOPT_SET_WHTLST_DEL,
    SOCKOPT_SET_WHTLST_FLUSH,
    SOCKOPT_GET_WHTLST_GETALL = 1300,

    /* ipset */
    SOCKOPT_SET_IPSET = 3300,
    SOCKOPT_GET_IPSET_TEST = 3300,
    SOCKOPT_GET_IPSET_LIST,

    /* route6 */
    SOCKOPT_SET_ROUTE6_ADD_DEL = 6300,
    SOCKOPT_SET_ROUTE6_FLUSH,
    SOCKOPT_GET_ROUTE6_SHOW    = 6300,

    /* iftraf */
    SOCKOPT_SET_IFTRAF_ADD  = 6400,
    SOCKOPT_SET_IFTRAF_DEL,
    SOCKOPT_GET_IFTRAF_SHOW = 6400,
};

#endif /* __DPVS_SOCKOPTS_CONF_H__ */
