#include "cpu/instr.h"

make_instr_func(lgdt)
{
	OPERAND start;
	modrm_rm(eip+1,&start);
/*	start.type=OPR_IMM;
	start.data_size=32;
	start.addr=eip+2;
	operand_read(&start);*/
	operand_read(&start);
	printf("addr=%x\n",start.val);

	OPERAND limit;
	limit.type=OPR_IMM;
	limit.data_size=16;
	limit.addr=start.val;
	printf("limit.addr=%x\n",limit.addr);
	operand_read(&limit);
	printf("limit=%x\n",limit.val);

	OPERAND base;
	base.type=OPR_IMM;
	base.data_size=32;
	base.addr=start.val+2;
	operand_read(&base);
	printf("base.addr=%x\n",base.addr);
	printf("base=%x\n",base.val);

	cpu.gdtr.limit=limit.val;
	cpu.gdtr.base=base.val;

	return 6;

}
