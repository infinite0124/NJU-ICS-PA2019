#include "cpu/instr.h"
#include "device/port_io.h"

make_instr_func(in_b)
{
	pio_read(cpu.edx._16,1);
	return 1;
}

make_instr_func(in_v)
{
	if(data_size==16)
		pio_read(cpu.edx._16,2);
	else if(data_size==32)
		pio_read(cpu.edx._16,4);
	return 1;
}

make_instr_func(out_b)
{
	pio_write(cpu.edx._16,1,cpu.eax._8[0]);
	return 1;
}

make_instr_func(out_v)
{
	if(data_size==16)
		poi_write(cpu.edx._16,2,cpu.eax._16);
	else if(data_size==32)
		poi_write(cpu.edx._16,4,cpu.eax._32);
	return 1;
}
