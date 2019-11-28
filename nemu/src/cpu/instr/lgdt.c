#include "cpu/instr.h"

make_instr_func(lgdt)
{
	OPERAND limit;
	limit.type=OPR_IMM;
	limit.data_size=2;
	limit.addr=eip+1;
	if(data_size==32)
	{
		mem;
	}
	return 3;

}
