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
    
    void Run();
    
private:
    std::unique_ptr<pMipsCpu> priv;

};

#endif // MIPSCPU_H
