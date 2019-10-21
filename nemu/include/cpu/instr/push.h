#ifndef __INSTR_PUSH_H__
#define __INSTR_PUSH_H__

int push_gr(uint32_t eip,uint8_t opcode);
int push_eip();
make_instr_func(push_rm_v);
#endif
