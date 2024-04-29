
#include <stdio.h>
#define N 8
#define numThread 2 // 2 threads in a block
#define numBlock 4  // 4 blocks

/*
 * 1.
 *  The 'kernel' function that will be executed on the GPU device hardware.
 */
__global__ void add( int *a, int *b, int *c ) {

    // the initial index that this thread will work on
    int tid = blockDim.x * blockIdx.x + threadIdx.x;
    while (tid < N) {
        c[tid] = a[tid] + b[tid];       // The actual computation done by the thread
        tid += blockDim.x;       // Increment this thread's index by the number of threads per block:
                                 // in this small case, each thread would then have a tid > N
    }
}
/*
 * The main program that directs the execution of vector add on the GPU
 */
int main( void ) {
    int *a, *b, *c;               // The arrays on the host CPU machine
    int *dev_a, *dev_b, *dev_c;   // The arrays for the GPU device

    // 2.a allocate the memory on the CPU
    a = (int*)malloc( N * sizeof(int) );
    b = (int*)malloc( N * sizeof(int) );
    c = (int*)malloc( N * sizeof(int) );

    // 2.b. fill the arrays 'a' and 'b' on the CPU with dummy values
    for (int i=0; i<N; i++) {
        a[i] = i;
        b[i] = i;
    }

    // 2.c. allocate the memory on the GPU
     cudaMalloc( (void**)&dev_a, N * sizeof(int) );
     cudaMalloc( (void**)&dev_b, N * sizeof(int) );
     cudaMalloc( (void**)&dev_c, N * sizeof(int) );

    // 2.d. copy the arrays 'a' and 'b' to the GPU
     cudaMemcpy( dev_a, a, N * sizeof(int),
                              cudaMemcpyHostToDevice );
     cudaMemcpy( dev_b, b, N * sizeof(int),
                              cudaMemcpyHostToDevice );

    // 3. Execute the vector addition 'kernel function' on th GPU device,
    // declaring how many blocks and how many threads per block to use.
    add<<<numBlock,numThread>>>( dev_a, dev_b, dev_c );

    // 4. copy the array 'c' back from the GPU to the CPU
    cudaMemcpy( c, dev_c, N * sizeof(int),
                              cudaMemcpyDeviceToHost );

    // verify that the GPU did the work we requested
    bool success = true;
    int total=0;
    printf("Checking %d values in the array.\n", N);
    for (int i=0; i<N; i++) {
        if ( c[i] = (a[i] + b[i])) {
            printf( "Addition: %d + %d = %d\n", a[i], b[i], c[i] );
            success = false;
        }
        total += 1;
    }
    if (success)  printf( "We did it, %d values correct!\n", total );

    // free the memory we allocated on the CPU
    free( a );
    free( b );
    free( c );

    // free the memory we allocated on the GPU
     cudaFree( dev_a );
     cudaFree( dev_b );
     cudaFree( dev_c );

    return 0;
}
