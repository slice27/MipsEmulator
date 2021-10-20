#ifndef _JINST_PROC_H_
#define _JINST_PROC_H_

#include <instruction.h>

class JInstProc
{
public:
    JInstProc();
    ~JInstProc();

    JInstProc(const JInstProc&) = delete;
    JInstProc& operator=(const JInstProc&) = delete;
    JInstProc(JInstProc&&) = delete;
    JInstProc& operator=(JInstProc&&) = delete;
    
    void ProcessInstruction(MipsInstruction &inst);
    
};

#endif // _JINST_PROC_H_
