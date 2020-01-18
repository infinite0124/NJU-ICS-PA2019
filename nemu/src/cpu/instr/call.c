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
	printf("eax=%x\n",cpu.eax);
	printf("src:%x\n",opr_src.val);
	cpu.eip=opr_src.val&(0xffffffff>>(32-data_size));
}
make_instr_impl_1op(call,rm,v)

make_instr_func(call_near_indirect)
{
	int len=2;
	printf("len=%x\n",len);

	cpu.esp-=4;
	OPERAND temp1;
	temp1.type=OPR_MEM;
	temp1.data_size=data_size;
	temp1.addr=cpu.esp;
	temp1.sreg=SREG_SS;
	temp1.val=cpu.eip+len;
	operand_write(&temp1);

	OPERAND temp2;
	temp2.data_size=data_size;
	temp2.sreg=SREG_CS;
	modrm_rm(cpu.eip+1,&temp2);
	int offset=sign_ext(temp2.val,32);
	print_asm_1("call","",1+data_size/8,&temp2);
	cpu.eip=offset;
	return 0;
}
