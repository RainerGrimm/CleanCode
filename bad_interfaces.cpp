// Fahrudin Halilovic

#include <iostream>

double calculateArea(double x, double y, double a, double b)
{
    return (a - x) * (y - b);
}

struct Point
{
    double x;
    double y;
};

double calculateArea(Point top_left, Point bottom_right)
{
    return (bottom_right.x - top_left.x) * (top_left.y - bottom_right.y);
}

struct Rectangle
{
    Point top_left;
    Point bottom_right;

    double calculateArea() const
    {
        return (bottom_right.x - top_left.x) * (top_left.y - bottom_right.y);
    }
};

int main()
{
    std::cout << "Area: " << calculateArea(0, 10, 5, 0) << std::endl;
    Point top_left = {0, 10};
    Point bottom_right = {5, 0};
    std::cout << "Area: " << calculateArea(top_left, bottom_right) << std::endl;
    Rectangle rect = {{0, 10}, {5, 0}};
    std::cout << "Area: " << rect.calculateArea() << std::endl;
    return 0;
}