#ifndef MIPSCPU_H
#define MIPSCPU_H

#include <memory>

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
