#ifndef _INSTPROC_H_
#define _INSTPROC_H_

#include "instruction.h"
#include "MipsCpu.h"

class InstProc
{
public:
    InstProc(std::shared_ptr<pMipsCpu> mainCpu);
    virtual ~InstProc();
    
    InstProc(const InstProc&) = delete;
    InstProc& operator=(const InstProc&) = delete;
    InstProc(InstProc&&) = delete;
    InstProc& operator=(InstProc&&) = delete;

    virtual void ProcessInstruction(MipsInstruction &inst) = 0;
    
protected:
    std::shared_ptr<pMipsCpu> cpu;

};

#endif // _INSTPROC_H_
