#include <stdint.h>
#include <iostream>
#include "MipsCpu.h"
#include "InstProc.h"
#include "JInstProc.h"

#define J_OPCODE   0x02
#define JAL_OPCODE 0x03

JInstProc::JInstProc(std::shared_ptr<pMipsCpu> cpu):
    InstProc(cpu)
{
}

JInstProc::~JInstProc()
{
}

void JInstProc::ProcessInstruction(MipsInstruction &inst)
{
    /*
    if (inst.opcode == JAL_OPCODE) {
        priv->registers[31] = priv->pc;
    }
    priv->pc = (priv->pc & 0xf0000000) | (inst.j_inst.addr << 2);
    */
}