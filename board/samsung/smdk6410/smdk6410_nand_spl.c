/*
 * (C) Copyright 2002
 * Sysgo Real-Time Solutions, GmbH <www.elinos.com>
 * Marius Groeger <mgroeger@sysgo.de>
 *
 * (C) Copyright 2002
 * David Mueller, ELSOFT AG, <d.mueller@elsoft.ch>
 *
 * (C) Copyright 2008
 * Guennadi Liakhovetki, DENX Software Engineering, <lg@denx.de>
 *
 * See file CREDITS for list of people who contributed to this
 * project.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#include <common.h>
/*
void print_address(int address)
{
	asm(
	"	mov r11, %0\n"
	"	mov r4, #8\n"
	"l0_0:\n"
	"l0_1:\n"
	"	ldr r3, =0x7F005010\n"
	"	ldr r3, [r3]\n"
	"	and r3, r3, #2\n"
	"	cmp r3, #0\n"
	"	beq l0_1\n"
	"		ldr r0, =0x7F005020\n"
	"		and r3, r11,#0b1111\n"
	"		add r3, r3, #48\n"
	"		str r3, [r0]\n"
	"\n"
	"		mov r11, r11,  LSR#4\n"
	"\n"
	"	sub r4, r4, #1\n"
	"	cmp r4, #0\n"
	"	bne l0_0\n"
	:
	:"r"(address)
	:"r11", "r4", "r3", "r0"
	);

}
*/

void board_init_f(unsigned long bootflag)
{

/*
	int reg_lr;
	asm( 
		"mov %0,pc\n" 	//打印lr寄存器，也就是这个这个函数的返回地址
				//如果要打印代码的当前地址(也就是当前执行地址)，用pc替代lr
		:"=r"(reg_lr) 
		: 
	); 

	print_address(reg_lr);
*/

//	int a = 0;
//	relocate_code(CONFIG_SYS_TEXT_BASE - TOTAL_MALLOC_LEN, NULL,
//			CONFIG_SYS_TEXT_BASE);
//	int b = 2;

/*
	int reg_pc;
	asm( 
		"mov %0,pc\n" 	//打印lr寄存器，也就是这个这个函数的返回地址
				//如果要打印代码的当前地址(也就是当前执行地址)，用pc替代lr
		:"=r"(reg_pc) 
		: 
	); 
*/



/*
	asm(
	"mov r0, #2"
	"l0_1_0:\n"
	"	ldr r3, =0x7F005010\n"
	"	ldr r3, [r3]\n"
	"	and r3, r3, #2\n"
	"	cmp r3, #0\n"
	"	beq l0_1_0\n"
	"		ldr r0, =0x7F005020\n"
	"		mov r3, #'A'\n"
	"		str r3, [r0]\n"
	"\n"
	"mov r0, #0"
	:
	:
	:"r3", "r0"
	);
*/





}
