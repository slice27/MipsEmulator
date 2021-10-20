#include <iostream>
#include <iomanip>
#include "MipsCpu.h"
#include "Mmu.h"
#include "instruction.h"
#include "RInstProc.h"

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
        mmu(MIPS_STACK_START_ADDR, MIPS_STACK_SIZE)
    {
        memset(&registers[0], 0x00, sizeof(registers));
        pc = 0x004000d0;
    }
    
    ~pMipsCpu()
    {
    }
    
    void Run()
    {
        uint32_t instructions[] = {
            0x27bdffd8, // 0x4000d0     addiu	sp,sp,-40
            0xafbf0024, // 0x4000d4     sw	ra,36(sp)
            0xafbe0020, // 0x4000d8     sw	s8,32(sp)
            0x03a0f025, // 0x4000dc     move	s8,sp
            0xafc40028, // 0x4000e0     sw	a0,40(s8)
            0xafc5002c, // 0x4000e4     sw	a1,44(s8)
            0x24020002, // 0x4000e8     li	v0,2
            0xafc20018, // 0x4000ec     sw	v0,24(s8)
            0x8fc40018, // 0x4000f0     lw	a0,24(s8)
            0x0c100047, // 0x4000f4     jal	40011c <square(int)>
            0x00000000, // 0x4000f8     nop
            0xafc20018, // 0x4000fc     sw	v0,24(s8)
            0x8fc20018, // 0x400104     lw	v0,24(s8)
            0x03c0e825, // 0x400100     move	sp,s8
            0x8fbf0024, // 0x400108     lw	ra,36(sp)
            0x8fbe0020, // 0x40010c     lw	s8,32(sp)
            0x27bd0028, // 0x400110     addiu	sp,sp,40
            0x03e00008, // 0x400114     jr	ra
            0x00000000, // 0x400118     nop
            //square(int):
            0x27bdfff8, // 0x40011c     addiu	sp,sp,-8
            0xafbe0004, // 0x400120     sw	s8,4(sp)
            0x03a0f025, // 0x400124     move	s8,sp
            0xafc40008, // 0x400128     sw	a0,8(s8)
            0x8fc30008, // 0x40012c     lw	v1,8(s8)
            0x8fc20008, // 0x400130     lw	v0,8(s8)
            0x00000000, // 0x400134     nop
            0x00620018, // 0x400138     mult	v1,v0
            0x00001012, // 0x40013c     mflo	v0
            0x03c0e825, // 0x400140     move	sp,s8
            0x8fbe0004, // 0x400144     lw	s8,4(sp)
            0x27bd0008, // 0x400148     addiu	sp,sp,8
            0x03e00008, // 0x40014c     jr	ra
            0x00000000, // 0x400150     nop
        };
        int size = sizeof(instructions) / sizeof(instructions[0]);

        // Push all the instructions into the MMU.
        for (int i = 0; i < size; ++i) {
            mmu[MIPS_PRG_START_ADDR + (i * sizeof(uint32_t))] = instructions[i];
        }

        uint64_t nop_count = 0;
        std::cout << "Total Instructions: " << size << std::endl;
        MipsInstruction inst;
        for (int j = 0; j < 1000000000; ++j) {
            for (int i = 0; i < size; ++i) {
                uint32_t opcode = Fetch();
                Decode(opcode, inst);
                Execute(inst);
                
                ++cpu_cycles;
            }
        }
        std::cout << "NOP: " << nop_count << std::endl;
    }

private:
    uint32_t Fetch()
    {
        uint32_t op_addr = pc;
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
            case J_OPCODE:
            case JAL_OPCODE:
                break;
            
                
                break;
        }
    }
    
    RInstProc rinst;
    Mmu mmu;
    uint32_t registers[MIPS_NUM_REGISTERS];
    uint32_t pc;
    uint32_t cpu_cycles;
    
    friend class JInstProc;

};

MipsCpu::MipsCpu():
    priv(std::make_unique<pMipsCpu>())
{
}

MipsCpu::~MipsCpu()
{
}

void MipsCpu::Run()
{
    priv->Run();
}
