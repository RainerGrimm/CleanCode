// Pablo Camacho 

// Ask yourself: "Can I be more local?" If affirmative, then, do it!

#include <iostream>
#include <map>
#include <string>

// Global variable "myMap1":
std::map<int, std::string> myMap1; // Do you really need this global variable "myMap1"...?

int main()
{
	// Local variable "myMap2":
	std::map<int, std::string> myMap2; // ... maybe, this local variable "MyMap2" is enough!
	
	auto result1 = myMap2.insert({1, "hello1"}); // Do you really need this variable "result1" here...?
	
	if(result1.second)
	{
	    std::cout << "Successful insertion! (Result1 example)" << '\n';
	}
	else
	{
	    std::cout << "The program failed to insert the [key - value] (Result1 example)" << '\n';
	}
	
	// Warning! The previous variable "result1" still exists here! Do you really need this behaviour?
	
	// Instead, the next variable "result2" might be enough for your purpose!
	
	// "result2" is created and destroyed in the conditional scope:
	
	if(auto result2 = myMap2.insert({2, "hello2"}); result2.second)
	{
	    std::cout << "Successful insertion! (Result2 example)" << '\n';
	    
	} // The variable "result2" has been destroyed!
	else 
	{
	    std::cout << "The program failed to insert the [key - value] (Result2 example)" << '\n';
	}
	
	// Note: "result1" still exists here!
	
	return 0;
	
}