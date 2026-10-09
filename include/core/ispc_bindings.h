#pragma once

extern "C"{
    // Category I: Pointwise Kernels
    void ispc_leaky_relu(float* data, int count, float alpha);
    void ispc_add_bias(float* output, const float* bias, int batch_size, int num_features);

    // Category III: GEMM (Matrix Multiplication)
    void ispc_gemm(const float* A, const float* B, float* C, int M, int N, int K);
}