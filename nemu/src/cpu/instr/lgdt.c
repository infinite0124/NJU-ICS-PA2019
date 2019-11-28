#include "cpu/instr.h"

make_instr_func(lgdt)
{
	return 1+data_size/8;

}
