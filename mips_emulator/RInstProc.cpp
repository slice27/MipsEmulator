#include <stdint.h>
#include <iostream>
#include "RInstProc.h"

RInstProc::RInstProc()
{
}

RInstProc::~RInstProc()
{
}

void RInstProc::ProcessInstruction(MipsInstruction &inst)
{
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