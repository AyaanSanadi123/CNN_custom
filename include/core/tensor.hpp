#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <vector>
#include <cstddef>
using namespace std;


class Tensor{
    private:
        float* data_; // this is the flat memory 
        vector <int> shape_; // this is the shape of the image 2D,3D,etc...
        size_t total_size_;

    public:
        // default constructor 
        Tensor();
        // shape constructor 
        explicit Tensor(const vector <int> &shape);
        // destructor 
        ~Tensor();

        // deep copy constructor 
        Tensor(const Tensor& other);

        // copy assignment operator 
        Tensor& operator=(const Tensor& other);

};



#endif 