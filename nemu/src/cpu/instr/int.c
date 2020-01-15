#include "cpu/instr.h"
#include "cpu/intr.h"

make_instr_func(int_)
{
	opr_src.type=OPR_IMM;
	opr_src.data_size=8;
	opr_src.addr=eip+1;
	operand_read(&opr_src);
	
	raise_sw_intr(opr_src.val);
	return 0;
}
