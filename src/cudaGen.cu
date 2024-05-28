#include "cudaGen.h"

__global__ void cuda::countBinary(int n, std::bitset<BITSET_SIZE> *results) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    if (idx < (1 << n)) {
        results[idx] = std::bitset<BITSET_SIZE>(idx);
    }
}

int cuda::generate() {
    int n;
    std::cout << "Enter the number of binary digits (n): ";
    std::cin >> n;

    if (n > BITSET_SIZE) {
        std::cerr << "Error: n must be less than or equal to " << BITSET_SIZE << std::endl;
        return 1;
    }

    int maxNumber = (1 << n); // 2^n
    std::vector<std::bitset<BITSET_SIZE>> bitsets(maxNumber);

    std::bitset<BITSET_SIZE> *d_results;
    cudaMalloc((void**)&d_results, maxNumber * sizeof(std::bitset<BITSET_SIZE>));

    int threadsPerBlock = 256;
    int blocksPerGrid = (maxNumber + threadsPerBlock - 1) / threadsPerBlock;

    auto start = std::chrono::high_resolution_clock::now();

    countBinary<<<blocksPerGrid, threadsPerBlock>>>(n, d_results);
    cudaDeviceSynchronize();
    cudaMemcpy(bitsets.data(), d_results, maxNumber * sizeof(std::bitset<BITSET_SIZE>), cudaMemcpyDeviceToHost);

    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Time taken: " << duration.count() << " milliseconds" << std::endl;
    std::cout << "Last generated number is: "<< bitsets[maxNumber - 1].to_string() << std::endl;
 
    cudaFree(d_results);
    return 0;
}
