export void ispc_leaky_relu(uniform float data[],uniform int count,uniform float alpha){
    for(uniform int i = 0 ; i < count ; i++){
        float value = data[i];

        if(value > 0.0f) data[i] = value;
        else data[i] =  alpha * value;
    }
}


export void ispc_add_bias(uniform float output[], uniform const float bias[], 
                          uniform int batch_size, uniform int num_features)
                          
{
        
    // The outer loop steps one chunk at a time (Scalar)
    for (uniform int b = 0; b < batch_size; ++b) {
        uniform int offset = b * num_features;
        
        // The inner loop executes the addition 8 channels at a time (Vectorized)
        foreach (f = 0 ... num_features) {
            output[offset + f] += bias[f];
        }
    }
}


export void ispc_gemm(uniform const float A[], uniform const float B[], uniform float C[], 
                      uniform int M, uniform int N, uniform int K) {
                      
    for (uniform int i = 0; i < M; ++i) {
        // Zero out the target row in C first using vector lanes
        foreach (j = 0 ... N) {
            C[i * N + j] = 0.0f;
        }
        
        for (uniform int k = 0; k < K; ++k) {
            // Load a single scalar value from A
            uniform float a_val = A[i * K + k]; 
            
            // Broadcast multiply that scalar against an entire vectorized row of B
            foreach (j = 0 ... N) {
                C[i * N + j] += a_val * B[k * N + j];
            }
        }
    }
}