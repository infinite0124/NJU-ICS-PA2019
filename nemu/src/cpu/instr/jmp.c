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
	//printf("jmp:eip=%x\n",cpu.eip+1+data_size/8);
        return 1 + data_size / 8;
}

make_instr_func(jmp_short)
{
	OPERAND imm;
	imm.type=OPR_IMM;
	imm.data_size=data_size;
	imm.data_size=8;
	imm.addr=eip+1;
	operand_read(&imm);
	int8_t t=imm.val;
	int offset=sign_ext(t,data_size);
	print_asm_1("jmp","",1+imm.data_size/8,&imm);
	cpu.eip+=offset;
	//printf("jmp_rel:eip=%x\n",cpu.eip+1+imm.data_size/8);
	return 1+imm.data_size/8;
}

static void instr_execute_1op()
{
	operand_read(&opr_src);
	cpu.eip=opr_src.val&(0xffffffff>>(32-data_size));
}
make_instr_impl_1op(jmp,rm,v)
make_instr_func(jmp_near_indirect)
{
	jmp_rm_v(eip,opcode);
	return 0;
}

make_instr_func(jmp_ptr)
{
	OPERAND imm,imm2;
	imm.type=OPR_IMM;
	imm2.type=OPR_IMM;
	imm.data_size=data_size;
	imm2.data_size=16;
	imm.addr=eip+1;
	imm2.addr=eip+1;
	operand_read(&imm);
	operand_read(&imm2);

	cpu.eip=imm.val;
	cpu.cs.val=imm2.val;
	if(data_size==16)
		cpu.eip&=0x0000ffff;
	//load_sreg(1);
	return 1+data_size/8;
}

/*make_instr_func(je)
{
	int len=2;
	//OPERAND imm;
	//imm.type=OPR_IMM;
	//imm.data_size=8;
	//imm.addr=cpu.eip+8;
	//operand_read(&imm);
	int8_t imm=instr_fetch(eip+1,1);
	if(cpu.eflags.ZF)

{
		cpu.eip+=sign_ext(imm,data_size);
	}	
	//print_asm_1("je"," ",2,&imm);
	//printf("eip=%x\n",cpu.eip);
	//printf("je:eip=%x\n",cpu.eip+len);
	return len;
}

make_instr_func(jne)
{
	int len=2;
	int8_t imm=instr_fetch(eip+1,1);
	if(!cpu.eflags.ZF)
		cpu.eip+=sign_ext(imm,data_size);
	//printf("jne:eip=%x\n",cpu.eip+len);
	return len;
}

make_instr_func(jg)
{
	int len=2;
	int8_t imm=instr_fetch(eip+1,1);
	if((cpu.eflags.SF==cpu.eflags.OF)&&(cpu.eflags.ZF==0))
		cpu.eip+=sign_ext(imm,data_size);
	//printf("jg:eip=%x\n",cpu.eip+len);
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
	//printf("jl:eip=%x\n",cpu.eip+2);
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
	//printf("jle:eip=%x\n",cpu.eip+len);
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
	//printf("jbe:eip=%x\n",cpu.eip+2+data_size/8);
	return 2+data_size/8;
}

make_instr_func(jbe_b)
{
	OPERAND IMM;
	imm.type=OPR_IMM;
	imm.data_size=8;
	imm.addr=eip+1;
	operand_read(&imm);
	int8_t t=imm.val;
	int offset=sign_ext(t,data_size);
	print_asm_1("jbe","",2,&imm);
	if((cpu.eflags.SF!=cpu.eflags.CF)||(cpu.eflags.ZF!=0))
		cpu.eip+=offset;
	//printf("jbe_b:eip=%x\n",cpu.eip+2);
	return 2;
}*/
