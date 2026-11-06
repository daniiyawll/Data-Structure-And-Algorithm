#include <iostream>
#include <string>
using namespace std;

template <typename T>
class AbstractStack
{
public:
    virtual void push(T value) = 0;
    virtual T pop() = 0;
    virtual T top() const = 0;
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;
    virtual ~AbstractStack() {}
};

template <typename T>
class myStack : public AbstractStack<T>
{
protected:
    T* arr;
    int maxSize;
    int topIndex;

public:
    myStack(int size = 10)
    {
        maxSize = size;
        topIndex = -1;
        arr = new T[maxSize];
    }

    ~myStack()
    {
        delete[] arr;
    }

    // Adds an element on top of the stack
    void push(T value)
    {
        if (isFull())
        {
            cout << "Stack is full." << endl;
            return;
        }
        arr[++topIndex] = value;
    }

    // Removes and returns the top element
    T pop()
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return T();
        }
        return arr[topIndex--];
    }

    // Returns the top element without removing it
    T top() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return T();
        }
        return arr[topIndex];
    }

    bool isEmpty() const
    {
        return topIndex == -1;
    }

    bool isFull() const
    {
        return topIndex == maxSize - 1;
    }

    // Prints all elements from top to bottom
    void display() const
    {
        if (isEmpty())
        {
            cout << "Stack is empty." << endl;
            return;
        }
        for (int i = topIndex; i >= 0; i--)
            cout << arr[i] << " ";
        cout << endl;
    }
};

class myCarStack : public myStack<string>
{
public:
    myCarStack(int size = 8) : myStack<string>(size) {}

    int totalCars() const
    {
        return topIndex + 1;
    }

    // Checks if a car number is present in the parking lot
    bool search(string carNumber) const
    {
        for (int i = 0; i <= topIndex; i++)
            if (arr[i] == carNumber)
                return true;
        return false;
    }

    // Parks a new car (push)
    void parkCar(string carNumber)
    {
        if (isFull())
        {
            cout << "Parking lot is full." << endl;
            return;
        }
        if (search(carNumber))
        {
            cout << "This car is already parked." << endl;
            return;
        }
        push(carNumber);
        cout << "Car " << carNumber << " parked." << endl;
    }

    // Removes a car by number using a temporary stack for the cars above it
    void removeCar(string carNumber)
    {
        if (!search(carNumber))
        {
            cout << "Car " << carNumber << " is not in the parking lot." << endl;
            return;
        }

        myStack<string> temp(8);

        // move cars on top of the desired car to the temporary stack
        while (top() != carNumber)
            temp.push(pop());

        // take out the desired car
        pop();

        // put back the temporarily removed cars
        while (!temp.isEmpty())
            push(temp.pop());

        cout << "Car " << carNumber << " removed." << endl;
    }

    void showCars() const
    {
        if (isEmpty())
        {
            cout << "Parking lot is empty." << endl;
            return;
        }
        cout << "Cars parked (last arrived first): ";
        display();
    }
};

int main()
{
    myCarStack lot(8);

    int choice;
    string carNumber;
    do
    {
        cout << "\n1. Park a new car";
        cout << "\n2. Remove a car by car number";
        cout << "\n3. View cars currently parked";
        cout << "\n4. Total cars parked";
        cout << "\n5. Search for a car";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter car number: ";
            cin >> carNumber;
            lot.parkCar(carNumber);
            break;
        case 2:
            cout << "Enter car number to remove: ";
            cin >> carNumber;
            lot.removeCar(carNumber);
            break;
        case 3:
            lot.showCars();
            break;
        case 4:
            cout << "Total cars parked: " << lot.totalCars() << endl;
            break;
        case 5:
            cout << "Enter car number to search: ";
            cin >> carNumber;
            if (lot.search(carNumber))
                cout << "Car " << carNumber << " is present in the parking lot." << endl;
            else
                cout << "Car " << carNumber << " is not present in the parking lot." << endl;
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
