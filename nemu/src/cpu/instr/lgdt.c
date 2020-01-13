#include "cpu/instr.h"

make_instr_func(lgdt)
{
	int len=1;
	OPERAND start;
	len+=modrm_rm(eip+1,&start);
	start.data_size=32;
	//printf("addr=%x\n",start.mem_addr.disp);

	OPERAND limit;
	limit.type=OPR_IMM;
	limit.data_size=16;
	limit.addr=start.mem_addr.disp;
	//printf("limit.addr=%x\n",limit.addr);
	operand_read(&limit);
	//printf("limit=%x\n",limit.val);

	OPERAND base;
	base.type=OPR_IMM;
	base.data_size=32;
	base.addr=start.mem_addr.disp+2;
	operand_read(&base);
	//printf("base.addr=%x\n",base.addr);
	//printf("base=%x\n",base.val);

	cpu.gdtr.limit=limit.val;
	cpu.gdtr.base=base.val;
	printf("len=%x\n",len);
	return len;

}
