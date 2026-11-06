#include <iostream>
using namespace std;

template <typename Type>
class List
{
protected:
    Type* arr;
    int maxSize;
    int currentSize;

public:
    List(int maxSize = 10, int currentSize = 0)
    {
        this->maxSize = maxSize;
        this->currentSize = currentSize;
        arr = new Type[maxSize];
    }

    List(const List& other)
    {
        maxSize = other.maxSize;
        currentSize = other.currentSize;
        arr = new Type[maxSize];
        for (int i = 0; i < currentSize; i++)
            arr[i] = other.arr[i];
    }

    virtual ~List()
    {
        delete[] arr;
    }

    virtual void addElementAtFirstIndex(Type) = 0;
    virtual void addElementAtLastIndex(Type) = 0;
    virtual Type removeElementFromEnd() = 0;
    virtual void removeElementFromStart() = 0;
};

template <typename Type>
class MyList : public List<Type>
{
public:
    MyList(int maxSize = 10, int currentSize = 0) : List<Type>(maxSize, currentSize) {}

    MyList(const MyList& other) : List<Type>(other) {}

    ~MyList() {}

    bool empty()
    {
        return this->currentSize == 0;
    }

    bool full()
    {
        return this->currentSize == this->maxSize;
    }

    int size()
    {
        return this->currentSize;
    }

    void addElementAtFirstIndex(Type value)
    {
        if (full())
        {
            cout << "List is full." << endl;
            return;
        }
        for (int i = this->currentSize; i > 0; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[0] = value;
        this->currentSize++;
    }

    void addElementAtLastIndex(Type value)
    {
        if (full())
        {
            cout << "List is full." << endl;
            return;
        }
        this->arr[this->currentSize] = value;
        this->currentSize++;
    }

    Type removeElementFromEnd()
    {
        if (empty())
        {
            cout << "List is empty." << endl;
            return Type();
        }
        this->currentSize--;
        return this->arr[this->currentSize];
    }

    void removeElementFromStart()
    {
        if (empty())
        {
            cout << "List is empty." << endl;
            return;
        }
        for (int i = 0; i < this->currentSize - 1; i++)
            this->arr[i] = this->arr[i + 1];
        this->currentSize--;
    }

    bool insertAt(int index, Type value)
    {
        if (full() || index < 0 || index > this->currentSize)
            return false;
        for (int i = this->currentSize; i > index; i--)
            this->arr[i] = this->arr[i - 1];
        this->arr[index] = value;
        this->currentSize++;
        return true;
    }

    Type last()
    {
        if (empty())
        {
            cout << "List is empty." << endl;
            return Type();
        }
        return this->arr[this->currentSize - 1];
    }

    bool search(Type value)
    {
        for (int i = 0; i < this->currentSize; i++)
            if (this->arr[i] == value)
                return true;
        return false;
    }

    void display()
    {
        if (empty())
        {
            cout << "List is empty." << endl;
            return;
        }
        for (int i = 0; i < this->currentSize; i++)
            cout << this->arr[i] << " ";
        cout << endl;
    }
};

template <typename Type>
class CustomList : public MyList<Type>
{
    bool isPrime(int n)
    {
        if (n < 2)
            return false;
        for (int i = 2; i * i <= n; i++)
            if (n % i == 0)
                return false;
        return true;
    }

    void rotatePartRight(int start, int end, int r)
    {
        int len = end - start;
        if (len <= 1)
            return;
        r = r % len;
        for (int k = 0; k < r; k++)
        {
            Type lastValue = this->arr[end - 1];
            for (int i = end - 1; i > start; i--)
                this->arr[i] = this->arr[i - 1];
            this->arr[start] = lastValue;
        }
    }

    void rotatePartLeft(int start, int end, int r)
    {
        int len = end - start;
        if (len <= 1)
            return;
        r = r % len;
        for (int k = 0; k < r; k++)
        {
            Type firstValue = this->arr[start];
            for (int i = start; i < end - 1; i++)
                this->arr[i] = this->arr[i + 1];
            this->arr[end - 1] = firstValue;
        }
    }

public:
    CustomList(int maxSize = 10, int currentSize = 0) : MyList<Type>(maxSize, currentSize) {}

    CustomList(const CustomList& other) : MyList<Type>(other) {}

    ~CustomList() {}

    Type sum_ofPrime()
    {
        Type sum = 0;
        for (int i = 0; i < this->currentSize; i++)
            if (isPrime((int)this->arr[i]))
                sum = sum + this->arr[i];
        return sum;
    }

    // returns -1 if there is no second maximum even number
    Type secondMaxEven()
    {
        bool foundFirst = false, foundSecond = false;
        Type first = 0, second = 0;
        for (int i = 0; i < this->currentSize; i++)
        {
            Type v = this->arr[i];
            if ((int)v % 2 != 0)
                continue;
            if (!foundFirst || v > first)
            {
                if (foundFirst)
                {
                    second = first;
                    foundSecond = true;
                }
                first = v;
                foundFirst = true;
            }
            else if (v < first && (!foundSecond || v > second))
            {
                second = v;
                foundSecond = true;
            }
        }
        return foundSecond ? second : -1;
    }

    // returns -1 if there is no second minimum odd number
    Type secondMinOdd()
    {
        bool foundFirst = false, foundSecond = false;
        Type first = 0, second = 0;
        for (int i = 0; i < this->currentSize; i++)
        {
            Type v = this->arr[i];
            if ((int)v % 2 == 0)
                continue;
            if (!foundFirst || v < first)
            {
                if (foundFirst)
                {
                    second = first;
                    foundSecond = true;
                }
                first = v;
                foundFirst = true;
            }
            else if (v > first && (!foundSecond || v < second))
            {
                second = v;
                foundSecond = true;
            }
        }
        return foundSecond ? second : -1;
    }

    void printDuplicates()
    {
        bool any = false;
        for (int i = 0; i < this->currentSize; i++)
        {
            bool alreadyPrinted = false;
            for (int j = 0; j < i; j++)
                if (this->arr[j] == this->arr[i])
                    alreadyPrinted = true;
            if (alreadyPrinted)
                continue;

            int count = 0;
            for (int j = 0; j < this->currentSize; j++)
                if (this->arr[j] == this->arr[i])
                    count++;
            if (count > 1)
            {
                cout << this->arr[i] << " ";
                any = true;
            }
        }
        if (!any)
            cout << "No duplicates found.";
        cout << endl;
    }

    void rotateClockwaise(int r)
    {
        int mid = this->currentSize / 2;
        rotatePartRight(0, mid, r);
        rotatePartRight(mid, this->currentSize, r);
    }

    void rotateanitclockwaise(int rt)
    {
        int mid = this->currentSize / 2;
        rotatePartLeft(0, mid, rt);
        rotatePartLeft(mid, this->currentSize, rt);
    }
};

int main()
{
    int maxSize;
    cout << "Enter maximum size of the list: ";
    cin >> maxSize;
    CustomList<int> list(maxSize);

    int choice, value, index, result;
    do
    {
        cout << "\n1. Add element at first index";
        cout << "\n2. Add element at last index";
        cout << "\n3. Remove element from end";
        cout << "\n4. Remove element from start";
        cout << "\n5. Insert at index";
        cout << "\n6. Search";
        cout << "\n7. Last element";
        cout << "\n8. Size";
        cout << "\n9. Is empty?";
        cout << "\n10. Is full?";
        cout << "\n11. Display list";
        cout << "\n12. Sum of prime numbers";
        cout << "\n13. Second maximum even";
        cout << "\n14. Second minimum odd";
        cout << "\n15. Print duplicates";
        cout << "\n16. Rotate clockwise";
        cout << "\n17. Rotate anti-clockwise";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter value: ";
            cin >> value;
            list.addElementAtFirstIndex(value);
            break;
        case 2:
            cout << "Enter value: ";
            cin >> value;
            list.addElementAtLastIndex(value);
            break;
        case 3:
            if (!list.empty())
                cout << "Removed: " << list.removeElementFromEnd() << endl;
            else
                cout << "List is empty." << endl;
            break;
        case 4:
            list.removeElementFromStart();
            break;
        case 5:
            cout << "Enter index and value: ";
            cin >> index >> value;
            if (list.insertAt(index, value))
                cout << "Value inserted." << endl;
            else
                cout << "Invalid index or list is full." << endl;
            break;
        case 6:
            cout << "Enter value to search: ";
            cin >> value;
            cout << (list.search(value) ? "Found" : "Not found") << endl;
            break;
        case 7:
            if (!list.empty())
                cout << "Last element: " << list.last() << endl;
            else
                cout << "List is empty." << endl;
            break;
        case 8:
            cout << "Size: " << list.size() << endl;
            break;
        case 9:
            cout << (list.empty() ? "Yes, list is empty" : "No, list is not empty") << endl;
            break;
        case 10:
            cout << (list.full() ? "Yes, list is full" : "No, list is not full") << endl;
            break;
        case 11:
            list.display();
            break;
        case 12:
            cout << "Sum of primes: " << list.sum_ofPrime() << endl;
            break;
        case 13:
            result = list.secondMaxEven();
            if (result == -1)
                cout << "No second maximum even number." << endl;
            else
                cout << "Second maximum even: " << result << endl;
            break;
        case 14:
            result = list.secondMinOdd();
            if (result == -1)
                cout << "No second minimum odd number." << endl;
            else
                cout << "Second minimum odd: " << result << endl;
            break;
        case 15:
            cout << "Duplicates: ";
            list.printDuplicates();
            break;
        case 16:
            cout << "Enter number of rotations: ";
            cin >> value;
            list.rotateClockwaise(value);
            list.display();
            break;
        case 17:
            cout << "Enter number of rotations: ";
            cin >> value;
            list.rotateanitclockwaise(value);
            list.display();
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
