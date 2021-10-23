#ifndef _IINSTPROC_H_
#define _IINSTPROC_H_

#include "MipsCpu.h"
#include "instruction.h"

class IInstProc
{
public:
    IInstProc();
    ~IInstProc();
    
    IInstProc(const IInstProc&) = delete;
    IInstProc& operator=(const IInstProc&) = delete;
    IInstProc(IInstProc&&) = delete;
    IInstProc& operator=(IInstProc&&) = delete;
    
    void ProcessInstruction(pMipsCpu* cpu, MipsInstruction &inst);

};

#endif // _IINSTPROC_H_
