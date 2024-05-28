#ifndef CUDAGEN_H
#define CUDAGEN_H

#include "main.h"

namespace cuda {
    __global__ void countBinary(int n, std::bitset<BITSET_SIZE> *results);
    int generate();
}

#endif
