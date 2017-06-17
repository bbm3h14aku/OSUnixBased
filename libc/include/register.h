#ifndef REGISTER_H
#define REGISTER_H

struct regs
{
	unsigned int gs, fs, es, ds;
	unsigned int int_no, err_code;
	unsigned int edi, esi, ebp, esp, ebx, ecx, eax;
	unsigned int eip, cs, eflags, userrsp, ss;
};

#endif