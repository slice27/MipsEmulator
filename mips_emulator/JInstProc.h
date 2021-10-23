#ifndef _JINST_PROC_H_
#define _JINST_PROC_H_

#include <instruction.h>

#define JINST_OPCODE     0x02
#define JALINST_OPCODE   0x03

class JInstProc: public InstProc
{
public:
    JInstProc(std::shared_ptr<pMipsCpu> cpu);
    virtual ~JInstProc();

    JInstProc(const JInstProc&) = delete;
    JInstProc& operator=(const JInstProc&) = delete;
    JInstProc(JInstProc&&) = delete;
    JInstProc& operator=(JInstProc&&) = delete;
    
    virtual void ProcessInstruction(MipsInstruction &inst);
    
};

#endif // _JINST_PROC_H_
