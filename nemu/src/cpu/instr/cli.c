#include "cpu/instr.h"

make_instr_func(cli)
{
	cpu.eflags.IF=0;
	printf("eip:%x\n",cpu.eip);
	return 1;
}
