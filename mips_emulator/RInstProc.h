#ifndef _R_INST_PROC_H_
#define _R_INST_PROC_H_

#include "instruction.h"
#include "MipsCpu.h"

#define RINST_OPCODE 0x00

class RInstProc
{
public:
    RInstProc();
    virtual ~RInstProc();
    
    RInstProc(const RInstProc&) = delete;
    RInstProc& operator=(const RInstProc&) = delete;
    RInstProc(RInstProc&&) = delete;
    RInstProc& operator=(RInstProc&&) = delete;
    
    void ProcessInstruction(pMipsCpu* cpu, MipsInstruction &inst);

};

#endif // _R_INST_PROC_H_
