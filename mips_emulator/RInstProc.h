#ifndef _R_INST_PROC_H_
#define _R_INST_PROC_H_

#include "instruction.h"
#include "InstProc.h"

#define RINST_OPCODE 0x00

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

class RInstProc: public InstProc
{
public:
    RInstProc(std::shared_ptr<pMipsCpu> cpu);
    virtual ~RInstProc();
    
    RInstProc(const RInstProc&) = delete;
    RInstProc& operator=(const RInstProc&) = delete;
    RInstProc(RInstProc&&) = delete;
    RInstProc& operator=(RInstProc&&) = delete;
    
    virtual void ProcessInstruction(MipsInstruction &inst);

};

#endif // _R_INST_PROC_H_
