#include "cpu/instr.h"

make_instr_func(lgdt)
{
	OPERAND start;
	start.type=OPR_IMM;
	start.data_size=1;
	start.addr=eip+1;
	operand_read(&start);

	OPERAND limit;
	limit.type=OPR_IMM;
	limit.data_size=2;
	limit.addr=start.val;
	operand_read(&limit);

	OPERAND base;
	base.type=OPR_IMM;
	base.data_size=4;
	base.addr=start.val+16;
	operand_read(&base);

	cpu.gdtr.limit=limit.val;
	cpu.gdtr.base=base.val;

	return 4;

}
