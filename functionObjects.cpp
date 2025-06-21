#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using std::string;

bool lessLength(const string& f, const string& s) {       
    return f.length() < s.length();
}

class GreaterLength {                                    
 public:
    bool operator()(const string& f, const string& s) const {
        return f.length() > s.length();
    }
};

int main() {

    std::vector<string> myStrVec = {"523345", "4336893456", "7234", 
                                    "564", "199", "433", "2435345"};
                                         
    std::cout << '\n';

    std::cout << "Ascending by length with a function \n";
    std::sort(myStrVec.begin(), myStrVec.end(), lessLength);     
    for (const auto& str: myStrVec) std::cout << str << " ";  
    std::cout << "\n\n";

    std::cout << "Descending by length with a function object \n";
    std::sort(myStrVec.begin(), myStrVec.end(), GreaterLength()); 
    for (const auto& str: myStrVec) std::cout << str << " ";  
    std::cout << "\n\n";

    std::cout << "Ascending by length with a lambda \n";
    std::sort(myStrVec.begin(), myStrVec.end(),                  
              [](const string& f, const string& s){ 
		          return f.length() < s.length(); 
			  });
    for (const auto& str: myStrVec) std::cout << str << " ";  
    
    std::cout << "\n\n";

}
