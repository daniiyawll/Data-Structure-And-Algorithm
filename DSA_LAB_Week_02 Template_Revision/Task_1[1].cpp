#include <iostream>
using namespace std;

class Course
{
public:
    virtual int duration() = 0;
    virtual ~Course() {}
};

class OnlineCourse : public Course
{
    int weeks;
    int hoursPerWeek;
public:
    OnlineCourse(int weeks, int hoursPerWeek)
    {
        this->weeks = weeks;
        this->hoursPerWeek = hoursPerWeek;
    }
    int duration()
    {
        return weeks * hoursPerWeek;
    }
};

class OfflineCourse : public Course
{
    int months;
    int hoursPerDay;
public:
    OfflineCourse(int months, int hoursPerDay)
    {
        this->months = months;
        this->hoursPerDay = hoursPerDay;
    }
    int duration()
    {
        return months * 30 * hoursPerDay;
    }
};

int main()
{
    OnlineCourse online(8, 5);
    OfflineCourse offline(3, 2);

    Course* c1 = &online;
    Course* c2 = &offline;

    cout << "Online Course duration: " << c1->duration() << " hours" << endl;
    cout << "Offline Course duration: " << c2->duration() << " hours" << endl;
    return 0;
}
