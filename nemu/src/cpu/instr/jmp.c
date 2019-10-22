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

make_instr_func(jmp_rel)
{
	OPERAND imm;
	imm.type=OPR_IMM;
	imm.data_size=data_size;
	imm.data_size=8;
	imm.addr=eip+1;
	operand_read(&imm);
	print_asm_1("jmp","",1+imm.data_size/8,&imm);
	cpu.eip+=sign_ext(imm.val,data_size);
	return 1+imm.data_size/8;
}

make_instr_func(je)
{
	int len=2;
	//OPERAND imm;
	//imm.type=OPR_IMM;
	//imm.data_size=8;
	//imm.addr=cpu.eip+8;
	//operand_read(&imm);
	uint8_t imm=instr_fetch(eip+1,1);
	if(cpu.eflags.ZF)
	{
		cpu.eip+=sign_ext(imm,data_size);
	}	
	//print_asm_1("je"," ",2,&imm);
	//printf("eip=%x\n",cpu.eip);
	return len;
}

make_instr_func(jne)
{
	int len=2;
	uint8_t imm=instr_fetch(eip+1,1);
	if(!cpu.eflags.ZF)
		cpu.eip+=sign_ext(imm,data_size);
	return len;
}

make_instr_func(jg)
{
	int len=2;
	uint8_t imm=instr_fetch(eip+1,1);
	if((cpu.eflags.SF==cpu.eflags.OF)&&(cpu.eflags.ZF==0))
		cpu.eip+=sign_ext(imm,data_size);
	return len;
}

make_instr_func(jl)
{
	OPERAND imm;
	imm.data_size=8;
	imm.type=OPR_IMM;
	imm.addr=eip+1;
	operand_read(&imm);
	int8_t t=imm.val;
	int offset=sign_ext(t,data_size);
	//printf("data_size=%x,offset=%x\n",data_size,offset);
	print_asm_1("jl","",2,&imm);
	if(cpu.eflags.SF!=cpu.eflags.OF)
		cpu.eip+=offset;
	return 2;
}
make_instr_func(jle)
{
	int len=2;
	int8_t imm=instr_fetch(eip+1,1);
	if((cpu.eflags.SF!=cpu.eflags.OF)||(cpu.eflags.ZF!=0))
		cpu.eip+=sign_ext(imm,32);
	//printf("jle	%x\n",imm);
//printf("eip=%x\n",cpu.eip);
	//print_asm_1("jle","",2,&imm);
	return len;
}

make_instr_func(jbe)
{
	OPERAND imm;
	imm.type=OPR_IMM;
	imm.data_size=data_size;
	imm.addr=eip+1;
	operand_read(&imm);
	if((cpu.eflags.SF!=cpu.eflags.CF)||(cpu.eflags.ZF!=0))
		cpu.eip+=sign_ext(imm.val,data_size);
	print_asm_1("jbe","",1+data_size/8,&imm);
	return 2+data_size/8;
}
