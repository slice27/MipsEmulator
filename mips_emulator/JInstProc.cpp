#include <stdint.h>
#include <iostream>
#include "MipsCpu.h"
#include "InstProc.h"
#include "JInstProc.h"
#include "priv_mips_cpu.h"

JInstProc::JInstProc(std::shared_ptr<pMipsCpu> cpu):
    InstProc(cpu)
{
}

JInstProc::~JInstProc()
{
}

void JInstProc::ProcessInstruction(MipsInstruction &inst)
{
    if (inst.opcode == JALINST_OPCODE) {
        cpu->registers[31] = cpu->pc;
    }
    cpu->pc = (cpu->pc & 0xf0000000) | (inst.j_inst.addr << 2);
}