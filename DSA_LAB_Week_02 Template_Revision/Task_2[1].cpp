#include <iostream>
using namespace std;

class Employee
{
public:
    virtual double calculateSalary() = 0;
    virtual ~Employee() {}
};

class FullTimeEmployee : public Employee
{
    double fixedSalary;
public:
    FullTimeEmployee() { fixedSalary = 0; }
    void setDetails(double fixedSalary)
    {
        this->fixedSalary = fixedSalary;
    }
    double calculateSalary()
    {
        return fixedSalary;
    }
};

class PartTimeEmployee : public Employee
{
    double hoursWorked;
    double hourlyRate;
public:
    PartTimeEmployee() { hoursWorked = 0; hourlyRate = 0; }
    void setDetails(double hoursWorked, double hourlyRate)
    {
        this->hoursWorked = hoursWorked;
        this->hourlyRate = hourlyRate;
    }
    double calculateSalary()
    {
        return hoursWorked * hourlyRate;
    }
};

int main()
{
    FullTimeEmployee fullTime;
    PartTimeEmployee partTime;

    fullTime.setDetails(50000);
    partTime.setDetails(80, 300);

    Employee* e1 = &fullTime;
    Employee* e2 = &partTime;

    cout << "Full-time employee salary: " << e1->calculateSalary() << endl;
    cout << "Part-time employee salary: " << e2->calculateSalary() << endl;
    return 0;
}
