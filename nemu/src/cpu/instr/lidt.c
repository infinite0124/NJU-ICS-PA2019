#include "cpu/instr.h"

make_instr_func(lidt)
{
	int len=1;
	OPERAND start;
	len+=modrm_rm(eip+1,&start);
	
	//printf("addr=%x\n",start.val);

	OPERAND limit;
	limit.type=OPR_IMM;
	limit.data_size=16;
	limit.addr=start.addr;

	//printf("limit.addr=%x\n",limit.addr);

	operand_read(&limit);
	printf("limit=%x\n",limit.val);

	OPERAND base;
	base.type=OPR_IMM;
	base.data_size=32;
	base.addr=start.addr+2;
	operand_read(&base);
	//printf("base.addr=%x\n",base.addr);
	printf("base=%x\n",base.val);

	cpu.idtr.limit=limit.val;
	cpu.idtr.base=base.val;
	//printf("len=%x\n",len);
	return len;

}
