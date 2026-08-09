/* This file contains implementation of the vector*/ 
#include <iostream>

template <typename T>

class VectorImpl
{
    T* data;
    size_t size;
    size_t capacity;

    public:

    VectorImpl()
    :(nullptr),
    size(0),
    capacity(0){}

    ~VectorImpl()
    {
        delete[] data;
    }
    void push_back(const T& value)
    {
        if(size == capacity)
        {
            size_t newCap = (capacity==0) ? 1 : capacity*2;
            T* newData = new T[newCap];
            for(size_t i=0; i<size; i++)
            {
                newData[i] = data[i];
            }
            delete []data;
            data = newData;
            capacity = newCap;
        }
        data[size++] = value;
    }

    T& operator[](size_t index) const
    {
        return data[index];
    }

    size_t getSize()
    {
        return size;
    }

    size_t getCapacity()
    {
        return capacity;
    }
};

int main()
{
    VectorImpl<int> v;

    v.push_back(10);
    v.push_back(20);
    v.push_back(30);

    std::cout <<  "size: " << v.getSize() << std::endl;
    std::cout <<  "capacity: " << v.getCapacity() << std::endl;
    return 0;
}