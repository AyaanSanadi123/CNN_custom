#include "core/tensor.hpp"
#include <numeric>
#include <stdexcept>
#include <algorithm>
#include <iostream>
using namespace std;

// initializing the default constructor
Tensor :: Tensor(): data_(nullptr),total_size_(0){}

// create a tensor with a specific shape and allocate required memory 
Tensor::Tensor(const vector <int>&shape) : shape_(shape){
    // if shape is empty 
    if(shape.empty()){
        throw invalid_argument("Tensor shape cannot be empty.\n");
    }
   total_size_ = 1;
   for(int dim = 0 ; dim < this -> shape_.size();dim++){
        int size = shape[dim];
        if (size <= 0) throw invalid_argument("Tensor dimensions must be strictly positive.\n");
        total_size_ *= size;
   }
   // allocate memory 
   data_ = new float [total_size_]();
}

// default destructor 
Tensor::~Tensor(){
    delete [] data_;
}


// deep copy constructor, basically allocate new memory and create a new object,rather than two objects pointing to the same memory 
Tensor::Tensor(const Tensor& other):shape_(other.shape_),total_size_(other.total_size_){
    data_ = new float[total_size_];
    // std::copy(source_start, source_end, destination_start);
    copy(other.data_,other.data_ + other.total_size_,data_); 
}

// this is a not a constructor, this is a member function with a return type being a reference to a tensor 
// other is the tensor you are trying to copy and this is the tensor that is getting updated
Tensor& Tensor::operator=(const Tensor& other){
    if(this == &other) return *this;

    // delete this's data 
    delete[] data_;

    // now update the shape and size of this to that of other 
    shape_ = other.shape_;
    total_size_ = other.total_size_;

    // allocate new memory 
    data_ = new float[total_size_];
    // copy 
    copy(other.data_, other.data_ + total_size_, data_);
    return *this;
}


// transfer ownership of one tensor to a new object (thats why this is a constructor), 
// fundamentally, dont create a new memory and copy, just make this point to the memory and disconnect other 
Tensor :: Tensor(Tensor&& other) noexcept:
        data_(other.data_),shape_(move(other.shape_)),
        total_size_(other.total_size_){
            other.data_ = nullptr;
            other.total_size_ = 0;
        }



// creating a new member function, its utility is to 
// transfer ownership of one tensor object to an already existing tensor object 
// we are transfering ownership from other to this 
Tensor& Tensor::operator=(Tensor&& other) noexcept{
    if(this == &other) return *this;

    delete[] data_;

    data_ = other.data_;
    shape_ = move(other.shape_);
    total_size_ = other.total_size_;

    other.data_ = nullptr;
    other.total_size_ = 0;

    return *this;
}

void Tensor :: fill(float value){
    for (size_t i = 0; i < total_size_; i++)
    {
        data_[i] = value;
    }
    
}

void Tensor::print_shape() const {
    cout << "Tensor Shape: [";
    for (size_t i = 0; i < shape_.size(); ++i) {
        cout << shape_[i] << (i < shape_.size() - 1 ? ", " : "");
    }
    cout << "] (Total size: " << total_size_ << ")\n";
}