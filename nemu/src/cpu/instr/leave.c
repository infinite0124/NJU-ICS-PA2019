#include "cpu/instr.h"

make_instr_func(leave)
{
	if(data_size==16)
	{
		cpu.gpr[4]._16=cpu.gpr[5]._16;
		cpu.gpr[5]._16=pop();
	}
	else
	{
		cpu.gpr[4]._32=cpu.gpr[5]._32;		
		cpu.gpr[5]._32=pop();
	
	}
	return 1;
}
