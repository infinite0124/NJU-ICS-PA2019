#include "cpu/instr.h"

static void instr_execute_1op()
{
	operand_read(&opr_src);
	cpu.esp-=data_size/8;
	opr_dest.type=OPR_MEM;
	opr_dest.data_size=data_size;
	opr_dest.addr=cpu.esp;
	opr_dest.val=opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_1op(push,r,v)
make_instr_impl_1op(push,rm,v)
make_instr_impl_1op(push,i,b)
make_instr_impl_1op(push,i,v)

int push_gr(uint32_t eip, uint8_t opcode)
{
	int len=1;
	OPERAND r,mem;
	r.type=OPR_REG;
	r.addr=opcode&0x7;
	r.data_size=data_size;
	r.val=cpu.gpr[r.addr]._32;
	cpu.esp-=data_size/8;
	mem.type=OPR_MEM;
	mem.addr=cpu.esp;
	mem.data_size=data_size;
	mem.val=r.val;
	operand_write(&mem);
	print_asm_1("push"," ",1,&r);
	return len;
}

make_instr_func(pusha)
{
	printf("pusha");
	push_gr(eip,0);
	push_gr(eip,1);
	push_gr(eip,2);
	push_gr(eip,3);
	push_gr(eip,4);
	push_gr(eip,5);
	push_gr(eip,6);
	push_gr(eip,7);
	return 1;	
}

int pushf()
{
	cpu.esp-=4;
	opr_dest.type=OPR_MEM;
	opr_dest.addr=cpu.esp;
	opr_dest.data_size=32;
	opr_dest.val=cpu.eflags.val;
	operand_write(&opr_dest);
	return 1;
}

int push_segReg(int no)
{
	cpu.esp-=2;
	opr_dest.type=OPR_MEM;
	opr_dest.addr=cpu.esp;
	opr_dest.data_size=16;
	opr_dest.val=cpu.segReg[no].val;
	operand_write(&opr_dest);
	return 1;
}

int push_eip()
{
	//printf("data_size=%x\n",data_size);
	opr_src.type=OPR_REG;
	opr_src.data_size=data_size;
	opr_src.val=cpu.eip;
	cpu.esp-=4;
	opr_dest.type=OPR_MEM;
	opr_dest.addr=cpu.esp;
	opr_dest.data_size=data_size;
	opr_dest.val=opr_src.val;
	operand_write(&opr_dest);
//	printf("push_eip:%x\n",opr_dest.val);
	return 1;
}
