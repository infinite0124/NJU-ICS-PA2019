#include "cpu/instr.h"

static void instr_execute_1op()
{
	if(data_size==16)
	{
	 	cpu.gpr[4].val-=2;
		//opr_src.val;
	}	
	else
	{
		cpu.gpr[4].val-=4;
		
	}
}

make_instr_impl_1op(push,r,v)

#endif
