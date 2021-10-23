#include <iostream>
#include <iomanip>
#include <vector>
#include "MipsCpu.h"
#include "Mmu.h"
#include "instruction.h"
#include "RInstProc.h"
#include "JInstProc.h"
#include "IInstProc.h"

#define MIPS_NUM_REGISTERS    32U
#define MIPS_STACK_START_ADDR 0x80000000U  // The MIPS 1 stack starts here
#define MIPS_STACK_SIZE       0x00004000U  // 16KB stack size (to start)
#define MIPS_PRG_START_ADDR   0x00040000U  // Program start location

#define SP_REG  29

#define BGEZ_OPCODE   0x01  // rt = 0x01
#define BGEZAL_OPCODE 0x01  // rt = 0x11
#define BLTZ_OPCODE   0x01  // rt = 0x00
#define BLTZAL_OPCODE 0x01  // rt = 0x10
#define J_OPCODE      0x02
#define JAL_OPCODE    0x03
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


class pMipsCpu
{
public:
    pMipsCpu():
        mmu(MIPS_STACK_START_ADDR, MIPS_STACK_SIZE),
        halted(false)
    {
        memset(&registers[0], 0x00, sizeof(registers));
        pc = 0x004000d0;
    }
    
    ~pMipsCpu()
    {
    }
    
    void LoadProgram(uint32_t inst[], uint32_t num_inst)
    {
        std::cout << "Total Instructions: " << num_inst << std::endl;
        // Push all the instructions into the MMU.
        for (int i = 0; i < num_inst; ++i) {
            mmu[MIPS_PRG_START_ADDR + (i * sizeof(uint32_t))] = inst[i];
        }
    }
    
    void Run()
    {
        uint64_t nop_count = 0;
        
        MipsInstruction inst;
        while (!halted) {
            uint32_t opcode = Fetch();
            Decode(opcode, inst);
            Execute(inst);
            
            ++cpu_cycles;
        }
        std::cout << "NOP: " << nop_count << std::endl;
    }

private:
    uint32_t Fetch()
    {
        uint32_t op_addr = pc;
        // TODO: Add breakpoint handling here.
        pc += sizeof(uint32_t);
        return mmu[op_addr];
    }
    
    void Decode(uint32_t instruction, MipsInstruction& decoded)
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
            case J_OPCODE:    // All of the Jump instructions use opcodes 2 and 3. (J type)
            case JAL_OPCODE:
                decoded.j_inst.addr = (instruction & 0x3ffffff);
                break;
            default:          // Everything else is an I instruction (I type)
                decoded.i_inst.rs = (instruction >> 21) & 0x0000001f;
                decoded.i_inst.rt = (instruction >> 16) & 0x0000001f;
                decoded.i_inst.immed = (instruction & 0x0000ffff);
                break;
        }
    }
    
    void Execute(MipsInstruction &inst)
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
                //iinst.ProcessInstruction(inst);
                break;
        }
    }
    
    friend class RInstProc;
    friend class JInstProc;
    friend class IInstProc;

    RInstProc rinst;
    JInstProc jinst;
    IInstProc iinst;
    Mmu mmu;
    uint32_t registers[MIPS_NUM_REGISTERS];
    uint32_t pc;
    uint32_t cpu_cycles;
    bool halted;
    
    friend class JInstProc;

};

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
