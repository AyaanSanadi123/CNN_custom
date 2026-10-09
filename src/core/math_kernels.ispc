export void ispc_leaky_relu(uniform float data[],uniform int count,uniform float alpha){
    for(uniform int i = 0 ; i < count ; i++){
        float value = data[i];

        if(value > 0.0f) data[i] = value;
        else data[i] =  alpha * value;
    }
}