#include <iostream>

template <typename T>

class UniquePtrImp
{
    private:
    T* data;

    public:
    UniquePtrImp(T* val= nullptr)
    : data(val)
    {}

    ~UniquePtrImp()
    {
        std::cout << "Destructor UniquePtrImp() called " << std::endl;
        delete data;
    }

    T& operator*()
    {
        return *data;
    }

    T* operator->()
    {
        return data;
    }

};

int main()
{
    UniquePtrImp<int> ptr (new int(10));
    std::cout << "*ptr: " << *ptr << std::endl;
    return 0;
}