#ifndef _PRIV_MIPS_CPU_H_
#define _PRIV_MIPS_CPU_H_

#include "MipsCpu.h"
#include "Mmu.h"
#include "instruction.h"
#include "RInstProc.h"
#include "JInstProc.h"
#include "IInstProc.h"

class pMipsCpu: std::enable_shared_from_this<pMipsCpu>
{
public:
    pMipsCpu();
    ~pMipsCpu();
    
    void LoadProgram(uint32_t inst[], uint32_t num_inst);
    void Run();
    
private:
    uint32_t Fetch();
    
    void Decode(uint32_t instruction, MipsInstruction& decoded);
    void Execute(MipsInstruction &inst);
    
    friend class RInstProc;
    friend class JInstProc;
    friend class IInstProc;

    RInstProc rinst;
    JInstProc jinst;
    IInstProc iinst;
    Mmu mmu;
    uint32_t registers[MIPS_NUM_REGISTERS];
    uint32_t pc;
    uint32_t cpu_cycles;
    bool halted;

};

#endif