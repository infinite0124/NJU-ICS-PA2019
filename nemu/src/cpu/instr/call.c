#include "cpu/instr.h"

int call_near(uint32_t eip,uint8_t opcode)
{
	int len=1;
	//push_eip();
	//printf("esp=%x\n",cpu.esp);
	uint32_t imm=instr_fetch(eip+1,data_size/8);
//	printf("original_eip=%x\n",cpu.eip);
//	printf("imm=%x\n",imm);
	len+=data_size/8;
//	printf("len=%x\n",len);
	cpu.eip+=len;
	push_eip();
	cpu.eip=cpu.eip+imm;
	if(data_size==16)
		cpu.eip=cpu.eip&0x0000ffff;
//	printf("eip=%x\n",cpu.eip);
	//printf("%x         call  %x\n",opcode,eip);
	return 0;
}

static void instr_execute_1op()
{
	operand_read(&opr_src);
	eip=opr_src.val&(0xffffffff>>(32-data_size));
}
make_instr_impl_1op(call,rm,v)
make_instr_func(call_near_indirect)
{
	call_rm_v(eip,opcode);
	return 0;
}
