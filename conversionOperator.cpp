#include <iostream>
#include <string>

struct MyHouse{
    MyHouse() = default;
    MyHouse(const std::string& fam): family(fam){}
	
    operator bool(){ return !family.empty(); }              
	
    std::string family = "";
};

void needInt(int i){
    std::cout << "int: " << i << '\n';
}

int main(){
	
    std::cout << std::boolalpha << '\n';
	
    MyHouse firstHouse;
    if (!firstHouse){                                        
        std::cout << "The firstHouse is still empty." << '\n';
    };
	
    MyHouse secondHouse("grimm");                               
    if (secondHouse){
        std::cout << "Family grimm lives in secondHouse." << '\n';
    }
	
	std::cout << '\n';
	
	needInt(firstHouse);
	needInt(secondHouse);
    
    std::cout << "2 * (firstHouse + secondHouse): " << 2 * (firstHouse + secondHouse) << '\n';
	
	std::cout << '\n';
	
}
