#include <iostream>
#include <iomanip>
#include <vector>
#include "priv_mips_cpu.h"

#define SP_REG  29

pMipsCpu::pMipsCpu():
    rinst(shared_from_this()),
    jinst(shared_from_this()),
    iinst(shared_from_this()),
    mmu(MIPS_STACK_START_ADDR, MIPS_STACK_SIZE),
    halted(false)
{
    memset(&registers[0], 0x00, sizeof(registers));
    pc = 0x004000d0;
}
    
pMipsCpu::~pMipsCpu()
{
}
    
void pMipsCpu::LoadProgram(uint32_t inst[], uint32_t num_inst)
{
    std::cout << "Total Instructions: " << num_inst << std::endl;
    // Push all the instructions into the MMU.
    for (int i = 0; i < num_inst; ++i) {
        mmu[MIPS_PRG_START_ADDR + (i * sizeof(uint32_t))] = inst[i];
    }
}
    
void pMipsCpu::Run()
{
    uint64_t nop_count = 0;
    
    MipsInstruction inst;
    while (!halted) {
        uint32_t opcode = Fetch();
        Decode(opcode, inst);
        Execute(inst);
        
        ++cpu_cycles;
        assert(false);
    }
    std::cout << "NOP: " << nop_count << std::endl;
}


uint32_t pMipsCpu::Fetch()
{
    uint32_t op_addr = pc;
    // TODO: Add breakpoint handling here.
    pc += sizeof(uint32_t);
    return mmu[op_addr];
}
    
void pMipsCpu::Decode(uint32_t instruction, MipsInstruction& decoded)
{
    decoded.opcode = (instruction >> 26) & 0x0000003f;
    switch (decoded.opcode) {
        case RINST_OPCODE:  // All of the ALU operations run on opcode 0 (R type)
            decoded.r_inst.rs = (instruction >> 21) & 0x0000001f;
            decoded.r_inst.rt = (instruction >> 16) & 0x0000001f;
            decoded.r_inst.rd = (instruction >> 11) & 0x0000001f;
            decoded.r_inst.shft_amt = (instruction >> 6) & 0x0000001f;
            decoded.r_inst.func = (instruction & 0x0000003f);
            break;
        case JINST_OPCODE:    // All of the Jump instructions use opcodes 2 and 3. (J type)
        case JALINST_OPCODE:
            decoded.j_inst.addr = (instruction & 0x3ffffff);
            break;
        default:          // Everything else is an I instruction (I type)
            decoded.i_inst.rs = (instruction >> 21) & 0x0000001f;
            decoded.i_inst.rt = (instruction >> 16) & 0x0000001f;
            decoded.i_inst.immed = (instruction & 0x0000ffff);
            break;
    }
}
    
void pMipsCpu::Execute(MipsInstruction &inst)
{
    switch (inst.opcode) {
        case RINST_OPCODE:
            rinst.ProcessInstruction(inst);
            break;
        case JINST_OPCODE:
        case JALINST_OPCODE:
            jinst.ProcessInstruction(inst);
            break;
        default:
            iinst.ProcessInstruction(inst);
            break;
    }
}

MipsCpu::MipsCpu():
    priv(std::make_unique<pMipsCpu>())
{
}

MipsCpu::~MipsCpu()
{
}

void MipsCpu::LoadProgram(uint32_t inst[], uint32_t num_inst)
{
    priv->LoadProgram(inst, num_inst);
}

void MipsCpu::Run()
{
    priv->Run();
}
