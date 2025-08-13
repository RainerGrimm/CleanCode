// Fahrudin Halilovic

#include <iostream>


size_t calc1(size_t n1, size_t n2, size_t n3)
{
    return 2 * n1 * n2 + 2 * n1 * n3 + 2 * n2 * n3;
}

size_t calc2(size_t n1, size_t n2, size_t n3)
{
    return n1 * n2 * n3;
}


size_t calculateSurface(size_t width, size_t height, size_t depth)
{
    return 2 * width * height + 2 * width * depth + 2 * height * depth;
}

size_t calculateVolume(size_t width, size_t height, size_t depth)
{
    return width * height * depth;
}

int main()
{
    {
        constexpr size_t n1 = 2;
        constexpr size_t n2 = 3;
        constexpr size_t n3 = 5;
        std::cout << calc1(n1, n2, n3) << std::endl;
        std::cout << calc2(n1, n2, n3) << std::endl;
    }

    {
        constexpr size_t width = 2;
        constexpr size_t height = 3;
        constexpr size_t depth = 5;
        std::cout << calculateSurface(width, height, depth) << std::endl;
        std::cout << calculateVolume(width, height, depth) << std::endl;
    }

    return 0;
}