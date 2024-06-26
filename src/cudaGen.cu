#include "cudaGen.h"

namespace cuda {
    template <int BITSET_SIZE>
    __global__ void countBinary(int n, std::bitset<BITSET_SIZE>* results) {
        int idx = blockIdx.x * blockDim.x + threadIdx.x;
        if (idx < (1 << n)) {
            results[idx] = std::bitset<BITSET_SIZE>(idx);
        }
    }

    template <int BITSET_SIZE>
    std::vector<std::bitset<BITSET_SIZE>> cheesenerate(int n) {
        int maxNumber = (1 << n); // 2^n
        std::vector<std::bitset<BITSET_SIZE>> bitsets(maxNumber);

        std::bitset<BITSET_SIZE>* d_results;
        cudaMalloc((void**)&d_results, maxNumber * sizeof(std::bitset<BITSET_SIZE>));

        int threadsPerBlock = 256;
        int blocksPerGrid = (maxNumber + threadsPerBlock - 1) / threadsPerBlock;

        auto start = std::chrono::high_resolution_clock::now();

        countBinary<BITSET_SIZE><<<blocksPerGrid, threadsPerBlock>>>(n, d_results);
        cudaDeviceSynchronize();
        cudaMemcpy(bitsets.data(), d_results, maxNumber * sizeof(std::bitset<BITSET_SIZE>), cudaMemcpyDeviceToHost);

        auto end = std::chrono::high_resolution_clock::now();

        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

        std::cout << "Generated all possible cheeses in: " << duration.count() << " milliseconds" << std::endl;
        std::cout << "Last cheesenerated number is: " << bitsets[maxNumber - 1].to_string() << std::endl;
        std::cout<<std::endl;

        cudaFree(d_results);
        return bitsets;
    }

    template std::vector<std::bitset<8>> cheesenerate<8>(int n);
    template std::vector<std::bitset<16>> cheesenerate<16>(int n);
    template std::vector<std::bitset<24>> cheesenerate<24>(int n);
    template std::vector<std::bitset<27>> cheesenerate<27>(int n);
    template std::vector<std::bitset<32>> cheesenerate<32>(int n);
}
