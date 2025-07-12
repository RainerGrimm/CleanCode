// Fahrudin Halilovic

#include <iostream>
#include <cassert>

template <typename T>
class CustomStack {
public:
    CustomStack() = default;

    ~CustomStack() noexcept
    {
        curr_capacity = 0;
        curr_size = 0;
        delete[] data;
        data = nullptr;
    }

    CustomStack(const CustomStack& cs)
    {
        curr_capacity = curr_size = cs.curr_size;
        data = new T[curr_capacity];
        for(auto idx = 0u; idx < curr_size; ++idx) {
            data[idx] = cs.data[idx];
        }
    }

    CustomStack& operator=(const CustomStack& cs)
    {
        if ( this != &cs ) {
            delete[] data;
            curr_capacity = curr_size = cs.curr_size;
            data = new T[curr_capacity];
            for(auto idx = 0u; idx < curr_size; ++idx) {
                data[idx] = cs.data[idx];
            }
        }

        return *this;
    }

    CustomStack(CustomStack&& cs)
    {
        curr_capacity = curr_size = cs.curr_size;
        data = cs.data;
        cs.curr_capacity = cs.curr_size = 0;
        cs.data = nullptr;
    }


    CustomStack& operator=(CustomStack&& cs)
    {
        if ( this != &cs ) {
            curr_capacity = curr_size = cs.curr_size;
            data = cs.data;
            cs.curr_capacity = cs.curr_size = 0;
            cs.data = nullptr;
        }

        return *this;
    }

    void push(T&& element)
    {
        if ( curr_size < curr_capacity ) {
            data[curr_size] = std::forward<T>(element);
            ++curr_size;
        }
        else {
            T* newData = new T[curr_capacity + 1];
            for(auto idx = 0u; idx < curr_size; ++idx) {
                newData[idx] = std::move(data[idx]);
            }
            delete[] data;

            newData[curr_size] = std::forward<T>(element);
            data = newData;
            ++curr_capacity;
            ++curr_size;
        }
    }

    void pop()
    {
        if ( empty() ) {
            return;
        }

        --curr_size;
    }

    T& top()
    {
        if ( empty() ) {
            throw std::runtime_error { "Stack is empty!" };
        }

        return data[curr_size - 1];
    }

    size_t size()
    {
        return curr_size;
    }

    bool empty()
    {
        return size() == 0;
    }

private:
    size_t curr_capacity = 0;
    size_t curr_size = 0;
    T* data = nullptr;
};


int main()
{
    CustomStack<int> stackInt;
    stackInt.push(1);
    stackInt.push(2);
    stackInt.push(3);

    assert(stackInt.size() == 3u);

    CustomStack<int> stackIntCopy = stackInt;
    assert(stackIntCopy.size() == 3u);

    stackInt.pop();

    assert(stackInt.size() == 2u);
    assert(stackIntCopy.size() == 3u);

    CustomStack<int> stackIntMove = std::move(stackInt);

    assert(stackInt.size() == 0u);
    assert(stackIntMove.size() == 2u);

    stackInt = std::move(stackIntCopy);

    assert(stackInt.size() == 3u);
    assert(stackIntCopy.size() == 0u);

    bool exceptionThrown { false };
    
    try {
        stackInt.pop();
        stackInt.pop();
        stackInt.pop();
        assert(stackInt.size() == 0);
        stackInt.top();
    }
    catch(...) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);

    return 0;
}