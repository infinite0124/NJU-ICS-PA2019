#include "cpu/instr.h"

static void instr_execute_1op()
{
	//printf("data_size=%x\n",data_size);
	if(data_size==8)
		cpu.esp-=8;
	else if(data_size==16)
		cpu.esp-=16;
	else
		cpu.esp-=32;
	 printf("esp=%x\n",cpu.esp);
	operand_read(&opr_src);
	opr_dest.type=OPR_MEM;
	opr_dest.data_size=data_size;
	opr_dest.addr=cpu.esp;
	opr_dest.val=opr_src.val;
	printf("val=%x\n",opr_dest.val);
	printf("esp=%x\n\n",cpu.esp);
	operand_write(&opr_dest);
}

make_instr_impl_1op(push,r,v)
make_instr_impl_1op(push,rm,v)
make_instr_impl_1op(push,i,b)

int push_gr(uint32_t eip, uint8_t opcode)
{
	int len=1;
	OPERAND r,mem;
	r.type=OPR_REG;
	r.addr=opcode&0x7;
	r.data_size=data_size;
	r.val=cpu.gpr[r.addr]._32;
	cpu.esp-=data_size;
	mem.type=OPR_MEM;
	mem.addr=cpu.esp;
	mem.data_size=data_size;
	mem.val=r.val;
	operand_write(&mem);
	print_asm_1("push"," ",1,&r);
	return len;
}

int push_eip()
{
	//printf("data_size=%x\n",data_size);
	opr_src.type=OPR_REG;
	opr_src.data_size=data_size;
	opr_src.val=cpu.eip;
	cpu.esp-=data_size;
	opr_dest.type=OPR_MEM;
	opr_dest.addr=cpu.esp;
	opr_dest.data_size=data_size;
	opr_dest.val=opr_src.val;
	operand_write(&opr_dest);
	return 1;
}
