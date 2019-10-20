#include "cpu/instr.h"
//make_instr_func(jmp_short)
make_instr_func(jmp_near)
{
        OPERAND rel;
        rel.type = OPR_IMM;
        rel.sreg = SREG_CS;
        rel.data_size = data_size;
        rel.addr = eip + 1;

        operand_read(&rel);

        int offset = sign_ext(rel.val, data_size);
        // thank Ting Xu from CS'17 for finding this bug
        print_asm_1("jmp", "", 1 + data_size / 8, &rel);

        cpu.eip += offset;

        return 1 + data_size / 8;
}

make_instr_func(je)
{
	int len=2;
	OPERAND imm;
	imm.type=OPR_IMM;
	imm.data_size=8;
	imm.addr=cpu.eip+8;
	operand_read(&imm);
	//uint8_t imm=instr_fetch(eip+1,1);
	if(cpu.eflags.ZF)
	{
		cpu.eip+=imm.val;
	}	
	print_asm_0("je"," ",2,&imm);
	return len;
}

make_instr_func(jg)
{
	int len=2;
	uint8_t imm=instr_fetch(eip+1,1);
	if((cpu.eflags.SF==cpu.eflags.OF)&&(cpu.eflags.ZF==0))
		cpu.eip+=imm;
	return len;
}

