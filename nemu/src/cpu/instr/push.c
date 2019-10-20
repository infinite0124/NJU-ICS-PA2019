#include "cpu/instr.h"

/*static void instr_execute_1op()
{
	cpu.esp-=data_size;
	operand_read(&opr_src);
	opr_dest.type=OPR_MEM;
	opr_dest.addr=cpu.esp;
	opr_dest.val=opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_1op(push,r,v)*/

int push(uint32_t eip, uint8_t opcode)
{
	OPERAND r,mem;
	r.type=OPR_REG;
	r.addr=opcode&0x7;
	r.val=cpu.gpr[r.addr]._32;
	cpu.esp-=data_size;
	mem.type=OPR_MEM;
	mem.addr=cpu.esp;
	mem.val=r.val;
	operand_write(&mem);
}


