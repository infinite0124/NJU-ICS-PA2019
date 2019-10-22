#include "cpu/instr.h"

make_instr_func(leave)
{
	cpu.esp=cpu.ebp;
	cpu.ebp=pop();
}
