#include <stdint.h>
#include <iostream>
#include "RInstProc.h"
#include "priv_mips_cpu.h"

#define SLL_FUNC     0x00  // 0

#define SRL_FUNC     0x02  // 2
#define SRA_FUNC     0x03  // 3
#define SLLV_FUNC    0x04  // 4

#define SRLV_FUNC    0x06  // 6
#define SRAV_FUNC    0x07  // 7
#define JR_FUNC      0x08  // 8
#define JALR_FUNC    0x09  // 9

#define SYSCALL_FUNC 0x0c  // 12
#define BREAK_FUNC   0x0d  // 13

#define MFHI_FUNC    0x10  // 16
#define MTHI_FUNC    0x11  // 17
#define MFLO_FUNC    0x12  // 18
#define MTLO_FUNC    0x13  // 19

#define MULT_FUNC    0x18  // 24
#define MULTU_FUNC   0x19  // 25
#define DIV_FUNC     0x1a  // 26
#define DIVU_FUNC    0x1b  // 27

#define ADD_FUNC     0x20  // 32
#define ADDU_FUNC    0x21  // 33
#define SUB_FUNC     0x22  // 34
#define SUBU_FUNC    0x23  // 35
#define AND_FUNC     0x24  // 36
#define OR_FUNC      0x25  // 37
#define XOR_FUNC     0x26  // 38
#define NOR_FUNC     0x27  // 39

#define SLT_FUNC     0x2a  // 42
#define SLTU_FUNC    0x2b  // 43

RInstProc::RInstProc()
{
}

RInstProc::~RInstProc()
{
}

void RInstProc::ProcessInstruction(pMipsCpu* cpu, MipsInstruction &inst)
{
    inst.type = R_INST;
    switch (inst.r_inst.func) {
#ifdef COMPILE_CODE
        case SLL_FUNC:
            break;
        case SRL_FUNC:
            break;
        case SRA_FUNC:
            break;
        case SLLV_FUNC:
            break;
        case SRLV_FUNC:
            break;
        case SRAV_FUNC:
            break;
        case JR_FUNC:
            break;
        case JALR_FUNC:
            break;
        case SYSCALL_FUNC:
            break;
        case BREAK_FUNC:
            break;
        case MFHI_FUNC:
            break;
        case MTHI_FUNC:
            break;
        case MFLO_FUNC:
            break;
        case MTLO_FUNC:
            break;
        case MULT_FUNC:
            break;
        case MULTU_FUNC:
            break;
        case DIV_FUNC:
            break;
        case DIVU_FUNC:
            break;
        case ADD_FUNC:
            break;
        case ADDU_FUNC:
            break;
        case SUB_FUNC:
            break;
        case SUBU_FUNC:
            break;
        case AND_FUNC:
            break;
        case OR_FUNC:
            break;
        case XOR_FUNC:
            break;
        case NOR_FUNC:
            break;
        case SLT_FUNC:
            break;
        case SLTU_FUNC:
            break;
#endif // COMPILE_CODE : This will remove code that isn't used yet.
        default:
            std::cout << "Invalid R-Type instruction!" << std::endl;
            cpu->PrintInstruction(inst);
            assert(false);
            break;
    }
}