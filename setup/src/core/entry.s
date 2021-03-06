/*
** Copyright (C) 2016 Airbus Group, stephane duverger <stephane.duverger@airbus.com>
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

/*
** 8KB kernel stack
*/
.section .stack, "aw", @nobits
.align 16
.space 0x2000

/* .byte 0 */
/* .p2align 13 */

.text
.globl entry
.type  entry,"function"

/*
** - make us uninterruptible
** - set initial stack for loader
** - clear eflags
** - init setup with grub multiboot info
** - start the vmm
*/
entry:
        cli
        movq    $__kernel_start__, %rsp
        pushq   $0
        popf
        call    init
        jmp     vmm_start
