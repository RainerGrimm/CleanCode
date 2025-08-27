// Fahrudin Halilovic

#include <cstddef>
#include <array>

constexpr size_t MAX_NUMBER = 100'005;
using Sieve = std::array<bool, MAX_NUMBER>;

constexpr size_t squareRoot(size_t input)
{
    auto res = 1u;

    while ( res * res <= input) {
        ++res;
    }

    return res;
}

constexpr Sieve generateSieve()
{
    Sieve sieve { };

    sieve[0] = sieve[1] = true;

    constexpr auto upper_limit = squareRoot(MAX_NUMBER);
    for(auto i = 2u; i <= upper_limit; ++i) {
        if ( !sieve[i] ) {
            for(auto j = i * 2; j < MAX_NUMBER; j += i) {
                sieve[j] = true;
            }
        }
    }

    return sieve;
}

constexpr bool primesCheck()
{
    constexpr std::array<size_t, 10> primes {
        2, 10061, 20047, 30011, 40009, 50021, 60017, 70001, 80021, 90001
    };

    constexpr auto sieve = generateSieve();

    auto allPrimes = true;
    for(const auto& p : primes) {
        allPrimes &= !sieve[p];
    }

    return allPrimes;
}


int main()
{
    // compile-time check can be done
    static_assert(primesCheck());
    return 0;
}