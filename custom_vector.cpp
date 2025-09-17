// Fahrudin Halilovic 

#include <iostream>

template <typename T>
class CustomVector
{
public:
    CustomVector() = default;

    // strong exception guarantee
    CustomVector(const CustomVector<T>& vec)
    : size { vec.size }
    {
        data = new T[size];
        for( auto idx = 0u; idx < size; ++idx ) {
            data[idx] = vec.data[idx];
        }
    }

    // no-throw guarantee
    CustomVector(CustomVector&& vec) noexcept
    {
        std::swap(size, vec.size);
        std::swap(data, vec.data);
    }

    // strong exception guarantee
    CustomVector& operator=(const CustomVector& vec)
    {
        auto temp = vec;

        std::swap(size, temp.size);
        std::swap(data, temp.data);

        return *this;
    }

    // no-throw guarantee
    CustomVector& operator=(CustomVector&& vec) noexcept
    {
        if ( this == &vec ) {
            return *this;
        }

        delete[] data;
        data = nullptr;
        size = 0;

        std::swap(size, vec.size);
        std::swap(data, vec.data);

        return *this;
    }

    // no-throw guarantee
    size_t getSize() const noexcept
    {
        return size;
    }

    // strong exception guarantee
    void push_back(T&& item)
    {
        T* newData = new T[size + 1];
        for( auto idx = 0u; idx < size; ++idx ) {
            newData[idx] = std::move(data[idx]);
        }

        newData[size] = std::move(item);
        
        ++size;

        delete[] data;
        data = newData;
        newData = nullptr;
    }

    // strong exception guarantee
    T& operator[](size_t idx)
    {
        if ( idx >= size ) {
            throw std::runtime_error { "Index out of range!" };
        }

        return data[idx];
    }

    // no-throw guarantee
    ~CustomVector() noexcept
    {
        delete[] data;
        data = nullptr;
        size = 0u;
    }

private:
    size_t size { 0u };
    T* data { nullptr };
};


CustomVector<int> createTestVector()
{
    CustomVector<int> test { };
    test.push_back(1);
    test.push_back(2);
    test.push_back(3);
    return test;
}

int main()
{
    CustomVector<int> first { };

    first.push_back(1);
    first.push_back(2);

    std::cout << first.getSize() << std::endl;

    first = std::move(first);

    std::cout << first.getSize() << std::endl;

    auto second = createTestVector();
    std::cout << second.getSize() << std::endl;
    std::cout << second[2] << std::endl;

    second = first;

    auto third { second };
    std::cout << third.getSize() << std::endl;

    third = third;
    std::cout << third.getSize() << std::endl;

    return 0;
}
