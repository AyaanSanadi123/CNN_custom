#ifndef TENSOR_HPP
#define TENSOR_HPP

#include <vector>
#include <cstddef>

class Tensor {
private:
    float* data_;
    std::vector<int> shape_;
    size_t total_size_;

public:
    // 1. Constructors & Destructor
    Tensor();
    // create a tensor with a specific shape,find how much memory it needs and allocate it
    explicit Tensor(const std::vector<int>& shape);
    ~Tensor();

    // 2. Copy Semantics (Deep Copy - allocates new memory)
    Tensor(const Tensor& other);
    Tensor& operator=(const Tensor& other);

    // 3. Move Semantics (Transfers ownership, prevents unnecessary copying)
    Tensor(Tensor&& other) noexcept;
    Tensor& operator=(Tensor&& other) noexcept;

    // 4. Core Accessors
    // Returns the raw pointer for ISPC kernels
    float* data() const { return data_; } 
    const std::vector<int>& shape() const { return shape_; }
    size_t size() const { return total_size_; }

    // 5. Utilities
    void fill(float value);
    void print_shape() const;
};

#endif // TENSOR_HPP