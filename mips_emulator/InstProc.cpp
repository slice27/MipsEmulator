#include "InstProc.h"
#include "InstProc.h"
#include "priv_mips_cpu.h"

InstProc::InstProc(std::shared_ptr<pMipsCpu> mainCpu):
    cpu(mainCpu)
{
}

InstProc::~InstProc()
{
}

