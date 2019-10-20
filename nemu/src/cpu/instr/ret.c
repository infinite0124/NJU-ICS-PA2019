#include "cpu/instr.h"

int ret_near()
{
	int len=1;
	cpu.eip=pop();
	if(data_size==16)
		cpu.eip&=0x0000ffff;
	printf("eip=%x\n",cpu.eip);
	return len;
}
