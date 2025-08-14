// Pablo Camacho

#include <iostream>

int main()
{             
	
	int x = 10, y = 20; // Not a good practice; however you know both "x" and "y" are integers...
	
	int* var1, var2; // var2 is an "int" or a "pointer to int"? Let's suppose is a pointer...
	
	var1 = &x;
	
	var2 = &y; // COMPILATION ERROR! var2 is an integer; cannot content the address of "y"! (Comment to compile)
	
	std::cout << *var1 << '\n';
	
	std::cout << *var2 << '\n'; // The compiler will not arrive to process this line! (Comment to compile)
	
	// LESSON LEARNT: Due to putting several variables in one line, you missed the correct variable type.
	
	int a = 1, b = 2, c, d = 3; // You missed initializing variable "c"...!
	
	std::cout << "a = " << a << ", b = " << b << ", c = " << c << ", d = " << d << '\n';
	
	// Output: variable "c" will contain garbage...!
	
	// LESSON LEARNT: Due to putting several variables in one line, you missed initializations.
	
	return 0;
}