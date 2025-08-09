// Fahrudin Halilovic 

#include <iostream>
#include <memory>
#include <vector>

class Shape {
public:
    virtual double calculateArea() const = 0; // Pure virtual function
    virtual double calculatePerimeter() const = 0; // Another pure virtual function
    virtual ~Shape() = default; // Virtual destructor
};

class Square : public Shape {
public:
    Square(double s) : side { s } {}

    double calculateArea() const override {
        return side * side;
    }

    double calculatePerimeter() const override {
        return 4 * side;
    }

private:
    double side;
};

class Rectangle : public Shape {
public:
    Rectangle(double w, double h) : width { w }, height { h } {}

    double calculateArea() const override {
        return width * height;
    }

    double calculatePerimeter() const override {
        return 2 * (width + height);
    }

private:
    double width;
    double height;
};

constexpr double PI = 3.14159;

class Circle : public Shape {
public:
    Circle(double r) : radius { r } {}
    double calculateArea() const override {
        return PI * radius * radius;
    }
    double calculatePerimeter() const override {
        return 2 * PI * radius;
    }
private:
    double radius;
};

int main()
{
    std::vector<std::shared_ptr<Shape>> shapes;
    shapes.emplace_back(std::make_shared<Rectangle>(5, 10));
    shapes.emplace_back(std::make_shared<Circle>(7));
    shapes.emplace_back(std::make_shared<Square>(4));

    for ( const auto& shape : shapes ) {
        std::cout << "Area: " << shape->calculateArea() << std::endl;
        std::cout << "Perimeter: " << shape->calculatePerimeter() << std::endl;
    }

    return 0;
}
