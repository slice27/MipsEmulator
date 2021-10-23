#ifndef _IINSTPROC_H_
#define _IINSTPROC_H_

#include "InstProc.h"

// TODO: Potentially remove this code if it takes too long.  IInstProc, JInstProc, and RInstProc
//       don't need the inheritance, and their ProcessInstruction can take a pointer to the CPU.

class IInstProc: public InstProc
{
public:
    IInstProc(std::shared_ptr<pMipsCpu> cpu);
    virtual ~IInstProc();
    
    IInstProc(const IInstProc&) = delete;
    IInstProc& operator=(const IInstProc&) = delete;
    IInstProc(IInstProc&&) = delete;
    IInstProc& operator=(IInstProc&&) = delete;
    
    virtual void ProcessInstruction(MipsInstruction &inst);

};

#endif // _IINSTPROC_H_
