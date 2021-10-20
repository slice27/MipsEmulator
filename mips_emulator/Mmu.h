#ifndef _MMU_H_
#define _MMU_H_

class pMmu;

class Mmu
{
public:
    Mmu(uint32_t stack_addr, uint32_t stack_size);
    ~Mmu();
    
    Mmu(const Mmu&) = delete;
    Mmu& operator=(const Mmu&) = delete;
    Mmu(Mmu&&) = delete;
    Mmu& operator=(Mmu&&) = delete;
    
    uint32_t& operator[](uint32_t);
private:
    std::unique_ptr<pMmu> priv;
};

#endif // _MMU_H_
