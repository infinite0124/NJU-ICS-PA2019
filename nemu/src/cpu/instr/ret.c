#include "cpu/instr.h"

int ret_near(uint32_t eip,uint8_t opcode)
{
	//int len=1;
	cpu.eip=pop();
	if(data_size==16)
		cpu.eip&=0x0000ffff;
	//printf("eip=%x\n",cpu.eip);
	return 0;
}

make_instr_func(ret_near_imm16)
{
	ret_near(eip,opcode);
	OPERAND imm;
	imm.type=OPR_IMM;
	imm.addr=eip+1;
	imm.data_size=16;
	operand_read(&imm);
	cpu.esp+=imm.val;
	print_asm_1("ret","",3,&imm);
	return 0;
}

make_instr_func(iret)
{
	printf("iret");
	cpu.eip=pop();
	printf("iret:%x\n",cpu.eip);
	cpu.cs.val=pop();
	cpu.eflags.val=pop();
	assert(0);
	return 0;
}
