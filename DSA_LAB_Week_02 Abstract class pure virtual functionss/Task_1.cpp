#include <iostream>
using namespace std;

class Shape
{
public:
    virtual double area() = 0;
    virtual ~Shape() {}
};

class Circle : public Shape
{
    double radius;
public:
    Circle(double radius)
    {
        this->radius = radius;
    }
    double area()
    {
        return 3.14159 * radius * radius;
    }
};

class Rectangle : public Shape
{
    double length;
    double width;
public:
    Rectangle(double length, double width)
    {
        this->length = length;
        this->width = width;
    }
    double area()
    {
        return length * width;
    }
};

int main()
{
    Circle circle(5);
    Rectangle rectangle(4, 6);

    Shape* s1 = &circle;
    Shape* s2 = &rectangle;

    cout << "Area of Circle: " << s1->area() << endl;
    cout << "Area of Rectangle: " << s2->area() << endl;
    return 0;
}
