#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

struct r_instruction {
    uint32_t rs;
    uint32_t rt;
    uint32_t rd;
    uint32_t shft_amt;
    uint32_t func;
};

struct i_instruction {
    uint32_t rs;
    uint32_t rt;
    uint32_t immed;
};

struct j_instruction {
    uint32_t addr;
};

struct MipsInstruction
{
    uint32_t opcode;
    union {
        struct r_instruction r_inst;
        struct i_instruction i_inst;
        struct j_instruction j_inst;
    };
};



#endif