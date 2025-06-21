// readAndPrint.cpp

#include <iostream>

void read_and_print() {  
    int x;
    std::cin >> x;
    // check for errors
    std::cout << x << '\n';
}

int read(std::istream& is) { 
    int x;
    is >> x;
    // check for errors
    return x;
}

void print(std::ostream& os, int x) {
    os << x << '\n';
}

int main() {

    read_and_print();
    
    auto res = read(std::cin);
    print(std::cout, res);

}
