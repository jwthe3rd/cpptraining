#define N 1000000


#include <stdlib.h>

__global__ void vector_add(float *out, float *a, float *b, int n) {

	for (int i = 0; i<n; i++) {
		out[i] = a[i] + b[i];
	}

}

int main() {


	float *a, *b, *out;
	float *d_a, *d_b, *d_out;

	// Allocate memory 
	//
	a = (float*)malloc(sizeof(float)*N);
	b = (float*)malloc(sizeof(float)*N);
	out = (float*)malloc(sizeof(float)*N);


	for (int i = 0; i<N; i++){
		a[i] = 1.0f; b[i] = 2.0f;
	}

	cudaMalloc((void**)&d_a, sizeof(float)*N);
	cudaMemcpy(d_a, a, sizeof(float)*N, cudaMemcpyHostToDevice);
	cudaMalloc((void**)&d_b, sizeof(float)*N);
	cudaMemcpy(d_b, b, sizeof(float)*N, cudaMemcpyHostToDevice);
	cudaMalloc((void**)&d_out, sizeof(float)*N);
	cudaMemcpy(d_out, out, sizeof(float)*N, cudaMemcpyHostToDevice);

	vector_add<<<1,1>>>(out, a, b, N);


	cudaFree(d_a);
	cudaFree(d_b);
	cudaFree(d_out);

	free(a);
	free(b);
	free(out);

}
