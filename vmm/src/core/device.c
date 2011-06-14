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
#include <dev.h>
#include <vm.h>
#include <pf.h>
#include <dev_io_ports.h>
#include <info_data.h>
#include <debug.h>

extern info_data_t *info;

int dev_proxify(io_insn_t *io)
{
   io_size_t sz = { .available = 1 };
   uint8_t   data;

   if(io->d)
   {
      data = in(io->port);
      debug(DEV, "proxy io in  0x%x data 0x%x\n", io->port, data);
      return dev_io_insn(io, &data, &sz);
   }
   else
   {
      dev_io_insn(io, &data, &sz);
      debug(DEV, "proxy io out 0x%x data 0x%x\n", io->port, data);
      out(data, io->port);
      return 1;
   }
}

void dev_a20_set(uint8_t on)
{
   if(!__rmode())
      panic("accessing a20 while in protected mode !");

   if(on != info->vm.dev.mem.a20)
   {
      info->vm.dev.mem.a20 = on;
      __pf_setup_a20();
   }
}

int dev_access()
{
   io_insn_t io;

   __io_init(&io);

   /* if(range(io.port, PIC1_START_PORT, PIC1_END_PORT)) */
   /*    return dev_pic(&info->vm.dev.pic[0], &io); */

   /* if(range(io.port, PIC2_START_PORT, PIC2_END_PORT)) */
   /*    return dev_pic(&info->vm.dev.pic[1], &io); */

   if(io.port == PS2_SYS_CTRL_PORT_A)
      return dev_ps2(&info->vm.dev.ps2, &io);

   if(range(io.port, KBD_START_PORT, KBD_END_PORT))
      return dev_kbd(&info->vm.dev.kbd, &io);

   if(range(io.port, COM1_START_PORT, COM1_END_PORT))
   {
      int rc = dev_uart(&info->vm.dev.uart, &io);
#ifdef __UART_PROXY__
      if(rc == DEV_UART_NEED_PROXY)
	 return dev_proxify(&io);
#endif
      return rc;
   }

   return 0;
}

