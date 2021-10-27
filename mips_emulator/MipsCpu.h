#ifndef MIPSCPU_H
#define MIPSCPU_H

#include <memory>

#define MIPS_NUM_REGISTERS    32U
#define MIPS_STACK_START_ADDR 0x80000000U  // The MIPS 1 stack starts here
#define MIPS_STACK_SIZE       0x00004000U  // 16KB stack size (to start)
//#define MIPS_PRG_START_ADDR   0x00040000U  // Program start location
#define MIPS_PRG_START_ADDR   0x004000d0

class pMipsCpu;

class MipsCpu
{
public:
    MipsCpu();
    ~MipsCpu();
    
    MipsCpu(const MipsCpu&) = delete;
    MipsCpu& operator=(const MipsCpu&) = delete;
    MipsCpu(MipsCpu&&) = delete;
    MipsCpu& operator=(MipsCpu&&) = delete;
    
    void LoadProgram(uint32_t inst[], uint32_t num_inst);
    void Run();
    
private:
    std::unique_ptr<pMipsCpu> priv;

};

#endif // MIPSCPU_H
