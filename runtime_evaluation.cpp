// Fahrudin Halilovic

#include <iostream>
#include <array>
#include <cassert>

constexpr size_t MAX_NUMBER = 100'005;
using Sieve = std::array<bool, MAX_NUMBER>;

size_t squareRoot(size_t input)
{
    auto res = 1u;

    while ( res * res <= input ) {
        ++res;
    }

    return res;
}

Sieve generateSieve()
{
    Sieve sieve { };

    sieve[0] = sieve[1] = true;

    const auto upper_limit = squareRoot(MAX_NUMBER);
    for( auto i = 2u; i <= upper_limit; ++i ) {
        if ( !sieve[i] ) {
            for( auto j = i * 2; j < MAX_NUMBER; j += i ) {
                sieve[j] = true;
            }
        }
    }

    return sieve;
}

bool primesCheck(const std::array<size_t, 10>& numbers)
{
    const auto sieve = generateSieve();

    auto res = true;
    for( const auto& num : numbers ) {
        res &= !sieve[num];
    }

    return res;
}

int main()
{
    std::array<size_t, 10> numbers { };

    for( auto idx = 0u; idx < 10; ++idx ) {
        std::cin >> numbers[idx];
    }

    // runtime checks for input
    assert(primesCheck(numbers));

    return 0;
}