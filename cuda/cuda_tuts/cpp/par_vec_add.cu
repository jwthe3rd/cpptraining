#define N 1000000


#include <iostream>
#include <math.h>

__global__
void vector_add(float *out, float *a, float *b, int n) {


	// example of a grid-stride loop

	int index = blockIdx.x * blockDim.x + threadIdx.x;
	int stride = blockDim.x*gridDim.x;

	for (int i = index; i<n; i+=stride) {
		out[i] = a[i] + b[i];
	}

}

int main() {

/* cpu mem alloc
	float *a = new float[N];
	float *b = new float[N];
	float *out = new float[N];
*/

	// Unified mem alloc
	//
	
	float *a, *b, *out;
	int blockSize = 256;
	int numBlocks = (N + blockSize - 1) / blockSize;

	cudaMallocManaged(&a, N*sizeof(float));
	cudaMallocManaged(&b, N*sizeof(float));
	cudaMallocManaged(&out, N*sizeof(float));

	for (int i = 0; i<N; i++){
		a[i] = 1.0f; b[i] = 2.0f;
	}

	// kernel syntax <<<M, T>>> M thread blocks of T threads
	// blocks of threads are multiples of 32

	vector_add<<<numBlocks, blockSize>>>(out, a, b, N);

	cudaDeviceSynchronize(); // cpu wait til gpu done

	float maxError = 0.0f;

	for (int i = 0; i<N; i++){
		maxError = fmax(maxError, fabs(out[i]-3.0f));
	}

	std::cout << "Max Error: " << maxError << std::endl;

	/* Free mem from cpu mem
	//
	delete [] a;
	delete [] b;
	delete [] out; */

	cudaFree(a);
	cudaFree(b);
	cudaFree(out);


	return 0;

}
