#include <array>
#include <unordered_map>
#include <utility>
#include <string.h>
#include "Mmu.h"

#define MEM_PAGE_SIZE 4096U
#define MEM_PAGE_MASK 0xfffff000U
#define MEM_PAGE_ADDR ~MEM_PAGE_MASK
#define MEM_PAGE_PRINT_WIDTH 64
#define MEM_PAGE_PAGE std::array<uint8_t, MEM_PAGE_SIZE>

class pMmu
{
public:
    pMmu(uint32_t stack_addr, uint32_t stack_size)
    {
        // Calculate the number of memory pages required for initial stack
        int pages = (int)ceil((double)stack_size / (double)MEM_PAGE_SIZE);
        // Create the pages in the MMU.  This will initialize the pages to 0.
        for (int i = 0; i < pages; ++i) {
            GetPage(stack_addr - (i * MEM_PAGE_SIZE));
        }
    }
    
    ~pMmu()
    {
        
    }
    
    pMmu(const pMmu&) = delete;
    pMmu& operator=(const pMmu&) = delete;
    pMmu(pMmu&&) = delete;
    pMmu& operator=(pMmu&&) = delete;
    
    uint32_t& operator[](uint32_t addr)
    {
        return *(uint32_t*)(&GetPage(addr)[addr & MEM_PAGE_ADDR]);
    }

    void PrintPage(uint32_t addr)
    {
        uint8_t *page = GetPage(addr);
        for (int i = 0; i < MEM_PAGE_SIZE; ++i)
    }
    
private:
    uint8_t* GetPage(uint32_t addr)
    {
        MEM_PAGE_PAGE mem_page;
        auto page = mmu.insert(std::pair<uint32_t, MEM_PAGE_PAGE>(addr & MEM_PAGE_MASK, mem_page));
        if (page.second) {
            memset(&page.first->second[0], 0x00, MEM_PAGE_SIZE);
        }
        return &page.first->second[0];
    }
    
    std::unordered_map <uint32_t, MEM_PAGE_PAGE > mmu;
};

Mmu::Mmu(uint32_t stack_addr, uint32_t stack_size):
    priv(std::make_unique<pMmu>(stack_addr, stack_size))
{
}

Mmu::~Mmu()
{
}

uint32_t& Mmu::operator[](uint32_t addr)
{
    return priv->operator[](addr);
}

