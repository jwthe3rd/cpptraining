#include <math.h>
#include <iostream>
#include <cuda_runtime.h>

using namespace std;


__global__
void mat_mul(float *result, float *mat1, float *mat2, int rows1, int cols1, int cols2)
{

    for (int i=0; i < rows1; i++)
    {
        for (int j = 0; j < cols2; j++)
        {
            float count = 0;
            for (int k=0; k < cols1; k++)
            {
                count += mat1[i * cols1 + k]*mat2[k*cols2 + j];
            } 
        result[i*cols2 + j] = count;
        }
    }
    
}

int main()
{
    int a = 64;  // rows of first matrix
    int b = 64;  // cols of first matrix / rows of second matrix
    int c = 64;  // cols of second matrix

    // Host arrays
    float h_m1[a][b];
    float h_m2[b][c];
    float h_res[a][c];

    // Device pointers
    float *d_m1, *d_m2, *d_res;

    // Allocate device memory
    cudaMalloc(&d_m1, a * b * sizeof(float));
    cudaMalloc(&d_m2, b * c * sizeof(float));
    cudaMalloc(&d_res, a * c * sizeof(float));

    // Initialize host arrays
    for (int i = 0; i < a; i++) {
        for (int j = 0; j < b; j++) {
            h_m1[i][j] = i * j + 2.0f;
        }
    }

    for (int i = 0; i < b; i++) {
        for (int j = 0; j < c; j++) {
            h_m2[i][j] = i * j + 2.0f;
        }
    }

    // Copy data to device
    cudaMemcpy(d_m1, h_m1, a * b * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_m2, h_m2, b * c * sizeof(float), cudaMemcpyHostToDevice);

    // Set up grid and block dimensions
    int blockSize = 256;
    int numThreads = (a*b + blockSize - 1 )/blockSize;

    // Launch kernel
    mat_mul<<<blockSize, numThreads>>>(d_res, d_m1, d_m2, a, b, c);

    // Copy result back to host
    cudaMemcpy(h_res, d_res, a * c * sizeof(float), cudaMemcpyDeviceToHost);

    // Print a small portion of the result (for verification)
    cout << "First few elements of result matrix:" << endl;
    for (int i = 0; i < min(5, a); i++) {
        for (int j = 0; j < min(5, c); j++) {
            cout << h_res[i][j] << " ";
        }
        cout << endl;
    }

    // Free device memory
    cudaFree(d_m1);
    cudaFree(d_m2);
    cudaFree(d_res);

    return 0;
}