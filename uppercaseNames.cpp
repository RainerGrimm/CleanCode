// Pablo Camacho 

#include <iostream>

// #define SUMMER 0   // This is fine: we normally use UPPERCASES for macros
                      // This variable has been commented out to avoid conflicts with enum!

int main()
{             
	enum Seasons{ SPRING, SUMMER, AUTUMN, WINTER }; 
    //                    -----> Warning! We already have a macro called SUMMER!
	
	Seasons currentSeason = Seasons::SUMMER;
	
	switch(currentSeason)
	{
		case SPRING : std::cout << "We are in Spring. Value: " << Seasons::SPRING << '\n'; break; // 0
		case SUMMER : std::cout << "We are in Summer. Value: " << Seasons::SUMMER << '\n'; break; // 1
		case AUTUMN : std::cout << "We are in Autumn. Value: " << Seasons::AUTUMN << '\n'; break; // 2
		case WINTER : std::cout << "We are in Winter. Value: " << Seasons::WINTER << '\n'; break; // 3
	}
	
	return 0;
}