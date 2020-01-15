
make_instr_func(int_)
{
	uint8_t no;
	memcpy(&no,eip+1,1);
	raise_sw_intr(no);
	return 2;
}
