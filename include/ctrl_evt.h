/*
** Copyright (C) 2011 EADS France, stephane duverger <stephane.duverger@eads.net>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License along
** with this program; if not, write to the Free Software Foundation, Inc.,
** 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#ifndef __CTRL_EVT_H__
#define __CTRL_EVT_H__

#include <types.h>

#define CTRL_EVT_FAIL     0
#define CTRL_EVT_DONE     1
#define CTRL_EVT_INTERN   2
#define CTRL_EVT_IGNORE   3
#define CTRL_EVT_FAULT    3

typedef int (*ctrl_evt_hdl_t)(arg_t);

#define CTRL_EVT_TYPE_CR_RD    0
#define CTRL_EVT_TYPE_CR_WR    1
#define CTRL_EVT_TYPE_EXCP     2
#define CTRL_EVT_TYPE_BRK      3
#define CTRL_EVT_TYPE_SSTEP    4

typedef struct controller_event
{
   uint8_t         type;
   arg_t           arg;
   ctrl_evt_hdl_t  hdl;

} __attribute__((packed)) ctrl_evt_t;

/*
** Functions
*/
int  ctrl_event();
int  ctrl_evt_setup(uint8_t, ctrl_evt_hdl_t, arg_t);
int  ctrl_evt_excp(uint32_t);
int  ctrl_evt_cr_rd(uint8_t);
int  ctrl_evt_cr_wr(uint8_t);

int  __ctrl_evt_excp_dbg(uint32_t);

#endif
