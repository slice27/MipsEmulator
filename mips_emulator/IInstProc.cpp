#include <iostream>
#include "IInstProc.h"
#include "priv_mips_cpu.h"

#define BLTZ_OPCODE   0x01  // rt = 0x00
#define BGEZ_OPCODE   0x01  // rt = 0x01
#define BGEZAL_OPCODE 0x01  // rt = 0x11
#define BLTZAL_OPCODE 0x01  // rt = 0x10

#define BEQ_OPCODE    0x04
#define BNE_OPCODE    0x05
#define BLEZ_OPCODE   0x06
#define BGTZ_OPCODE   0x07
#define ADDI_OPCODE   0x08
#define ADDIU_OPCODE  0x09
#define SLTI_OPCODE   0x0a
#define SLTIU_OPCODE  0x0b
#define ANDI_OPCODE   0x0c
#define ORI_OPCODE    0x0d
#define XORI_OPCODE   0x0e
#define LUI_OPCODE    0x0f

IInstProc::IInstProc(std::shared_ptr<pMipsCpu> cpu):
    InstProc(cpu)
{
}

IInstProc::~IInstProc()
{
}

void IInstProc::ProcessInstruction(MipsInstruction& inst)
{
    switch (inst.opcode) {
        case ADDIU_OPCODE:
            cpu->registers[inst.i_inst.rt] = cpu->registers[inst.i_inst.rs] + inst.i_inst.immed;
            break;
        default:
            std::cout << "Unimplemented I-Type instruction!" << std::endl;
            assert(false);
            break;
    }
}

