#include <iostream>

int main() {

    const int j = 3; // j is declared const
    std::cout << j << '\n';
    
    int* pj = const_cast<int*>(&j);
    *pj = 4;      // undefined behavior
    std::cout << j << '\n';
 
}
