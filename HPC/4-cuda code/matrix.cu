#include <stdio.h>

#define N 3  // Size of matrices (3x3)

// CUDA kernel for matrix multiplication
__global__ void matrixMultiply(int *a, int *b, int *c) {
    int row = blockIdx.y * blockDim.y + threadIdx.y;
    int col = blockIdx.x * blockDim.x + threadIdx.x;

    if (row < N && col < N) {
        int sum = 0;
        for (int i = 0; i < N; ++i) {
            sum += a[row * N + i] * b[i * N + col];
        }
        c[row * N + col] = sum;
    }
}

int main() {
    // Matrices dimensions
    const int size = N * N;

    // Host matrices
    int h_a[size], h_b[size], h_c[size];

    // Input matrices from user
    printf("Enter elements of matrix A (3x3):\n");
    for (int i = 0; i < size; ++i) {
        scanf("%d", &h_a[i]);
    }

    printf("Enter elements of matrix B (3x3):\n");
    for (int i = 0; i < size; ++i) {
        scanf("%d", &h_b[i]);
    }

    // Allocate memory for matrices on the device
    int *d_a, *d_b, *d_c;
    cudaMalloc((void **)&d_a, size * sizeof(int));
    cudaMalloc((void **)&d_b, size * sizeof(int));
    cudaMalloc((void **)&d_c, size * sizeof(int));

    // Copy matrices from host to device
    cudaMemcpy(d_a, h_a, size * sizeof(int), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, h_b, size * sizeof(int), cudaMemcpyHostToDevice);

    // Define grid and block dimensions
    dim3 dimBlock(3, 3);
    dim3 dimGrid(1, 1);

    // Launch kernel
    matrixMultiply<<<dimGrid, dimBlock>>>(d_a, d_b, d_c);

    // Copy result matrix from device to host
    cudaMemcpy(h_c, d_c, size * sizeof(int), cudaMemcpyDeviceToHost);

    // Display result
    printf("Result Matrix:\n");
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            printf("%d\t", h_c[i * N + j]);
        }
        printf("\n");
    }

    // Free device memory
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return 0;
}
