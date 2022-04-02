#include <stdint.h>
#include <iostream>
#include "RInstProc.h"

#define SLL_FUNC     0

#define SRL_FUNC     2
#define SRA_FUNC     3
#define SLLV_FUNC    4

#define SRLV_FUNC    6
#define SRAV_FUNC    7
#define JR_FUNC      8
#define JALR_FUNC    9

#define SYSCALL_FUNC 12
#define BREAK_FUNC   13

#define MFHI_FUNC    16
#define MTHI_FUNC    17
#define MFLO_FUNC    18
#define MTLO_FUNC    19

#define MULT_FUNC    24
#define MULTU_FUNC   25
#define DIV_FUNC     26
#define DIVU_FUNC    27

#define ADD_FUNC     32
#define ADDU_FUNC    33
#define SUB_FUNC     34
#define SUBU_FUNC    35
#define AND_FUNC     36
#define OR_FUNC      37
#define XOR_FUNC     38
#define NOR_FUNC     39

#define SLT_FUNC     42
#define SLTU_FUNC    43

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
        default:
            std::cout << "Invalid R-Type instruction!" << std::endl;
            assert(false);
            break;
    }
}