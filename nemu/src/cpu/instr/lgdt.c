#include "cpu/instr.h"

make_instr_func(lgdt)
{
	OPERAND mem;
	mem.type=OPR_MEM;
	mem.data_size=data_size;
	mem.mem_addr=eip+1;
	if(data_size==32)
	{
		;
	}
	return 3;

}
