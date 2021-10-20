#include <stdint.h>
#include <iostream>
#include "JInstProc.h"

#define J_OPCODE   0x02
#define JAL_OPCODE 0x03

JInstProc::JInstProc()
{
}

JInstProc::~JInstProc()
{
}

void JInstProc::ProcessInstruction(MipsInstruction &inst)
{
    uint32_t pc = 0;
    uint32_t r31 = pc;
    switch (inst.opcode) {
        case J_OPCODE:
            pc = (pc & 0xf0000000) | (inst.j_inst.addr << 2);
            break;
        case JAL_OPCODE:
            pc = (pc & 0xf0000000) | (inst.j_inst.addr << 2);
            r31 = pc;
            break;
        default:
            std::cout << "Invalid J-Type Instruction!" << std::endl;
            assert(false);
            break;
    }
}