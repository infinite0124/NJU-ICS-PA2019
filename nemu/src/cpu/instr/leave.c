#include "cpu/instr.h"

make_instr_func(leave)
{
	if(data_size==16)
	{
		cpu.esp_16=cpu.ebp_16;
		cpu.ebp_16=pop();
	}
	else
	{
		cpu.esp_32=cpu.esp_32;		
		cpu.ebp_32=pop();
	
	}
	return 1;
}
