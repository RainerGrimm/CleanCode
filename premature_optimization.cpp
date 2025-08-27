// Fahrudin Halilovic

#include <string>
#include <algorithm>
#include <cassert>

int main()
{
    std::string test { "test" };

    {
        // option 1: stick with the standard and apply std::reverse
        std::reverse(std::begin(test), std::end(test));
        assert(test == "tset");
    }

    {
        // option 2: try to make some optimizations and manually swap characters
        for ( auto idx = 0u; idx < test.size() / 2; ++idx ) {
            std::swap(test[idx], test[test.size() - idx - 1]);
        }
        assert(test == "test");
    }

    return 0;
}
