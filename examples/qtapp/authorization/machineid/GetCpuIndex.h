#pragma once

#include <string>

namespace GWTools{
// InstructionSet.cpp
// Compile by using: cl /EHsc /W4 InstructionSet.cpp
// processor: x86, x64
// Uses the __cpuid intrinsic to get information about
// CPU extended instruction set support.

// cmd get by 
// > wmic cpu get processorid

std::string GetCpuIndex();

}