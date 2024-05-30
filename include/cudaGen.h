#ifndef CUDAGEN_H
#define CUDAGEN_H

#include "main.h"

namespace cuda{
    template <int BITSET_SIZE>
    __global__ void countBinary(int n, std::bitset<BITSET_SIZE>* results);


    template <int BITSET_SIZE>
    std::vector<std::bitset<BITSET_SIZE>> cheesenerate(int n);
}

#endif
