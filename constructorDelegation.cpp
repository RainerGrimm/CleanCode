// constructorDelegation.cpp

#include <cmath>
#include <iostream>

class Degree{
public:
  explicit Degree(int deg){
    degree = deg%360;
    if (degree < 0) degree += 360;
  }
  
  Degree(): Degree(0){}

  explicit Degree(double deg):Degree(static_cast<int>(ceil(deg))) {}

  int getDegree() const { return degree; }

private:
  int degree;
};

int main(){

  std::cout << '\n';

  Degree degree10(10);
  Degree degree45(45);
  Degree degreeMinus315(-315);
  Degree degree405(405);
  Degree degree;
  Degree degree44(44.45);

  std::cout << "Degree(10): " << degree10.getDegree() << '\n';
  std::cout << "Degree(45): " << degree45.getDegree() << '\n';
  std::cout << "Degree(-315): " << degreeMinus315.getDegree() << '\n';
  std::cout << "Degree(405): " << degree405.getDegree() << '\n';
  std::cout << "Degree(): " << degree.getDegree() << '\n';
  std::cout << "Degree(44.45): " << degree44.getDegree() << '\n';

  std::cout << '\n';

}

