// Fahrudin Halilovic

#include <iostream>
#include <memory>
#include <string>

class Person {

public:
    Person(size_t a, std::string n)
    : age { a },
      name { std::move(n) }
      { }

    ~Person() 
    {
        std::cout << "~Person::Person" << std::endl;
    }

private:
    size_t age;
    std::string name;
};


int main()
{
    // only 3 instances of the class Person are created here
    auto p1 = new Person { 18, "Test1" };
    auto p2 = new Person { 19, "Test2" };
    // p3 will be automatically deallocated
    auto p3 = std::make_unique<Person>(20, "Test3");
    // p4 points to the same instance just like p2
    auto p4 = std::unique_ptr<Person>(p2);

    delete p1;

    // p4 acts like a wrapper for p2
    // thus deallocating p2 here will cause
    // a crash when trying to clean up p4
    // if the next would be commented out
    // then we should see output from
    // destructor 3 times for 3 instaces
    delete p2;
    return 0;
}
