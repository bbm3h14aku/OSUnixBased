/*
 * global_os.h
 *
 *  Created on: 20.11.2016
 *      Author: jan
 */

#ifndef KERNEL_ARCH_I386_GLOBAL_OS_H_
#define KERNEL_ARCH_I386_GLOBAL_OS_H_

struct regs
{
	unsigned int gs, fs, es, ds;
	unsigned int int_no, err_code;
	unsigned int edi, esi, ebp, esp, ebx, ecx, eax;
	unsigned int eip, cs, eflags, userrsp, ss;
};

#endif /* KERNEL_ARCH_I386_GLOBAL_OS_H_ */
