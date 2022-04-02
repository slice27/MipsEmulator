#include <iostream>
#include <iomanip>
#include <ios>
#include <vector>
#include <memory>
#include "priv_mips_cpu.h"

#define SP_REG  29

pMipsCpu::pMipsCpu():
    mmu(MIPS_STACK_START_ADDR, MIPS_STACK_SIZE),
    halted(false)
{
    memset(&registers[0], 0x00, sizeof(registers));
    pc = 0x004000d0;
    registers[SP_REG] = MIPS_STACK_START_ADDR;
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
        PrintRegisters();
        uint32_t opcode = Fetch();
        Decode(opcode, inst);
        Execute(inst);
        PrintRegisters();
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
    uint32_t inst = mmu[op_addr];
    std::cout << "Inst: 0x" << std::hex << inst;
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
            rinst.ProcessInstruction(this, inst);
            break;
        case JINST_OPCODE:
        case JALINST_OPCODE:
            jinst.ProcessInstruction(this, inst);
            break;
        default:
            iinst.ProcessInstruction(this, inst);
            break;
    }
}

void pMipsCpu::PrintRegisters()
{
    std::cout << "Cycles: " << cpu_cycles << std::endl;
    std::cout << "at: 0x";
    std::cout << std::setfill('0') << std::hex << std::setw(8) << std::right;
    std::ios_base::fmtflags f(std::cout.flags());
    std::cout << registers[1] << std::endl;
    
    std::cout << "v0: 0x";
    std::cout.flags(f);
    std::cout << registers[2] << "\tv1: 0x" << registers[3] << std::endl;
    std::cout << "a0: 0x" << registers[4]  << "\ta1: 0x" << registers[5] << "\t";
    std::cout.flags(f);
    std::cout << "a2: 0x" << registers[6]  << "\ta3: 0x" << registers[7] << std::endl;
    std::cout.flags(f);
    std::cout << "t0: 0x" << registers[8]  << "\tt1: 0x" << registers[9] << "\t";
    std::cout.flags(f);
    std::cout << "t2: 0x" << registers[10] << "\tt3: 0x" << registers[11] << std::endl;
    std::cout << "t4: 0x" << registers[12] << "\tt5: 0x" << registers[13] << "\t";
    std::cout << "t6: 0x" << registers[14] << "\tt7: 0x" << registers[15] << std::endl;
    
    std::cout << "s0: 0x" << registers[16] << "\ts1: 0x" << registers[17] << "\t";
    std::cout << "s2: 0x" << registers[18] << "\ts3: 0x" << registers[19] << std::endl;
    std::cout << "s4: 0x" << registers[20] << "\ts5: 0x" << registers[21] << "\t";
    std::cout << "s6: 0x" << registers[22] << "\ts7: 0x" << registers[23] << std::endl;
    
    std::cout << "T8: 0x" << registers[24] << "\tT9: 0x" << registers[25] << std::endl;
    std::cout << "K0: 0x" << registers[26] << "\tK1: 0x" << registers[27] << std::endl;
    
    std::cout << "GP: 0x" << registers[28] << "\tSP: 0x" << registers[29] << std::endl;
    std::cout << "S8: 0x" << registers[30] << "\tRA: 0x" << registers[31] << std::endl;
    
    std::cout << "LO: 0x" << lo << "\tHI: 0x" << hi << std::endl;
    std::cout << "PC: 0x" << pc << "\tEPC: 0x" << epc << std::endl << std::endl;
}

void pMipsCpu::PrintInstruction(MipsInstruction inst)
{
    switch (inst.type)
    {
        case R_INST:
            break;
        case I_INST:
            std::cout << "\tRS  (" << std::dec << inst.i_inst.rs << "): 0x" << std::setfill('0') << std::setw(0) << std::right << std::hex << registers[inst.i_inst.rs];
            std::cout << "\tRT  (" << inst.i_inst.rt << "): 0x" << registers[inst.i_inst.rt];
            std::cout << "\tIMD (" << (uint32_t)inst.i_inst.immed << ")" << std::endl;
            break;
        case J_INST:
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
