#include "IInstProc.h"

IInstProc::IInstProc(std::shared_ptr<pMipsCpu> cpu):
    InstProc(cpu)
{
}

IInstProc::~IInstProc()
{
}

void IInstProc::ProcessInstruction(MipsInstruction& inst)
{
}

