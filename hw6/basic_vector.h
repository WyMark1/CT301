#ifndef BASIC_VECTOR_H_DEFINED
#define BASIC_VECTOR_H_DEFINED
#include <string>
#include <iostream>
#include <cstddef>
#include <cmath>

template<typename T> class basic_vector {
    T* data_;
    std::size_t size_;
    std::size_t capacity_;

public:

    /** Constructor
     * @Param size_t for starting capacity of the vector
     * @Return None
     * starts size at 0 capacity at capacity and allocates capacity amount of memory
    */
    basic_vector(std::size_t capacity) {
        capacity_ = capacity;
        size_ = 0;
        data_ = new T[capacity_];
    }

    /** Constructor
     * @Param None
     * @Return None
     * Calls the constructor with capacity as input and passes it 1 as the value
    */
    basic_vector() : basic_vector(1) {}

    /** Constructor
     * @Param basic_vector the vector you want to copy
     * @Return None
     * It changes the size and capacity of the current vector into that of the other vector 
     * Then it allocates memory and copies over all data from the other vector 
    */
    basic_vector(const basic_vector & rhs) {
        size_ = rhs.size();
        capacity_ = rhs.capacity();
        data_ = new T[capacity_];
        for (std::size_t i = 0; i < size_; ++i) {
            data_[i] = rhs[i];
        }
    }

    /** operator=
     * @Param basic_vector the vector you want to assign to the current vector
     * @Return basic_vector a reference to the current vector
     * Deletes the current data then changes size and capacity then reallocates memory then finally copys over the data
    */
    basic_vector& operator=(const basic_vector& rhs) {
        if (this != &rhs) {
            delete[] data_;
            size_ = rhs.size();
            capacity_ = rhs.capacity();
            data_ = new T[rhs.capacity()];
            for (std::size_t i = 0; i < rhs.size(); ++i) {
                data_[i] = rhs[i];
            }
        }
        return *this;
    } 

    /** Destructor
     * @Param None
     * @Return None
     * Deletes the current data
    */
    ~ basic_vector() {delete[] data_;}

    /** size
     * @Param None
     * @Return size_t the current size
     * It returns the size of the vector
    */
    std::size_t size() const {return size_;}

    /** max_size
     * @Param None
     * @Return size_t the maximum size of the vector
     * Calculates the maximum possible size of the vector based off of what data type T is
    */
    std::size_t max_size() const {return (std::pow(2,32) / (sizeof(T))) - 1;}

    /** capacity
     * @Param None
     * @Return size_t current capacity of the vector
     * It returns the capacity of the vector
    */
    std::size_t capacity() const {return capacity_;}

    /** shrink_to_fit
     * @Param None
     * @Return None
     * It reallocates the data into a memory allocation that is size large
    */
    void shrink_to_fit() {
        if (capacity_ > size_) {
            capacity_ = size_;
            T* copy = new T[capacity_];
            for (std::size_t i = 0; i < capacity_; ++i) {
                copy[i] = data_[i];
            }
            delete[] data_;
            data_ = copy;
        }
    }

    /** reserve
     * @Param size_t the new capacity
     * @Return None
     * reallocate data into new memory location that has capcity size.
     * Throws an error if n is larger than max_size()
    */
    void reserve(std::size_t n) {
        if (n > max_size())
            throw std::range_error("basic_vector - reserve(size_t) - Value "+std::to_string(n)+" larger than max size "+std::to_string(max_size())+"\n");
        if (n > capacity_) {
            capacity_ = n;
            T* copy = new T[capacity_];
            for (std::size_t i = 0; i < size_; ++i) {
                copy[i] = data_[i];
            }
            delete[] data_;
            data_ = copy;
        }
    }

    /** resize
     * @Param size_t the new size
     * @Param T the value to use to fill up the new size
     * @Return None
     * If n is larger than the current size then reserve more memory if needed and fill in the new size with val
     * If n is smaller than the current size then delete the data past the new size
    */
    void resize(std::size_t n, const T& val) {
        if (size_ > n) {
            for (std::size_t i = n; i < size_; ++i)
                data_[i].~T();
            size_ = n;
        } else if (size_ < n) { 
            reserve(n);
            for (std::size_t i = 0; i < n - size_; ++i)
                data_[size_ + i] = val;
            size_ = n;
        }
    }
    
    /** resize
     * @Param size_t the new size
     * @Return None
     * Calls the resize(n,val) method but with the variable val as the default contructor of T 
    */
    void resize(std::size_t n) {
        resize(n,T());
    }

    /** empty
     * @Param None
     * @Return bool represents whether or not the vector is empty
     * If size is 0 it returns true else returns false
    */
    bool empty() {return size_ == 0;}

    /** operator[]
     * @Param size_t n the index you want
     * @Return T the value at the index
     * Uses the data_ pointer and adds the index given to it and the dereferences it to get the real value at that point
    */
    T& operator[](std::size_t n) const {
        return data_[n];
    }

    /** at
     * @Param size_t n the index you want
     * @Return T the value at the index
     * Uses the [] operator to get the value at index n but also throws an error if n is larger than size
    */
    T& at(std::size_t n) const {
        if (n >= size_){
            throw std::range_error("basic_vector - at(size_t) - Index: "+std::to_string(n)+" out of bounds for range: "+std::to_string(size_)+"\n");
        } else {
            return data_[n];
        }
    }

    /** front
     * @Param none
     * @Return T the value at the first index
     * Uses the [] operator to get the value at index 0
    */
    T& front() const {return data_[0];}

    /** back
     * @Param none
     * @Return T the value at the last index
     * Uses the [] operator to get the value at index size_-1
    */
    T& back() const {return data_[size_-1];}

    /** data
     * @Param none
     * @Return T* the pointer at the begining of the data
     * returns data_
    */
    T* data() const {return data_;}

    /** push_back
     * @Param T the value to insert
     * @Return None
     * If size + 1 is greater than the current capacity reserve 2 time more then call resize(size + 1, val) to add val to the end of the vector
    */
    void push_back(const T& val) {
        if (size_ + 1 > capacity_) reserve(capacity_*2);
        resize(size_ + 1, val);
    }

    /** pop_back
     * @Param None
     * @Return None
     * removes the last value in the vector by calling resize(size-1)
    */
    void pop_back() {
        resize(size_ - 1);
    }

    /** swap
     * @Param basic_vector vector to swap with
     * @Return None
     * calls the copy constructor to create a copy of the current vector the swaps the current vector with other and swaps other with the copy
    */
    void swap(basic_vector& other) {
        basic_vector<T> copy(*this);
        *this = other;
        other = copy;
    }

    /** clear
     * @Param None
     * @Return None
     * deletes the current data then reallocates the capacity and changes size to 0
    */
    void clear() {
        delete[] data_;
        data_ = new T[capacity_];
        size_ = 0;
    }

};
#endif