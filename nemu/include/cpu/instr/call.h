#ifndef __INSTR_CALL_H__
#define __INSTR_CALL_H__

int call_near(uint32_t eip,uint8_t opcode);
make_instr_func(call_near_indirect);

#endif
