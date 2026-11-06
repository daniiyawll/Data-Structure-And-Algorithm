#include <iostream>
#include <string>
using namespace std;

// Priority: 1 = Research, 2 = Assignment, 3 = Casual reading (default)
string priorityName(int priority)
{
    if (priority == 1)
        return "Research";
    if (priority == 2)
        return "Assignment";
    return "Casual reading";
}

class StudentNode
{
public:
    string name;
    int priority;
    StudentNode* next;

    StudentNode(string name, int priority)
    {
        this->name = name;
        this->priority = priority;
        next = nullptr;
    }
};

// Reservation list of one book (singly linked list ADT).
// Students with a smaller priority number are placed nearer the front;
// students with the same priority stay in the order they joined.
class ReservationList
{
    StudentNode* head;

public:
    ReservationList()
    {
        head = nullptr;
    }

    ~ReservationList()
    {
        while (head != nullptr)
        {
            StudentNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Adds a student according to the priority (default is casual reading)
    void addStudent(string name, int priority = 3)
    {
        StudentNode* newNode = new StudentNode(name, priority);
        if (head == nullptr || priority < head->priority)
        {
            newNode->next = head;
            head = newNode;
            return;
        }
        StudentNode* current = head;
        while (current->next != nullptr && current->next->priority <= priority)
            current = current->next;
        newNode->next = current->next;
        current->next = newNode;
    }

    // Removes a student who cancelled
    bool removeStudent(string name)
    {
        if (head == nullptr)
            return false;

        if (head->name == name)
        {
            StudentNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        StudentNode* current = head;
        while (current->next != nullptr && current->next->name != name)
            current = current->next;

        if (current->next == nullptr)
            return false;

        StudentNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        return true;
    }

    // Updates the priority of a student and moves them to the right place
    bool updatePriority(string name, int newPriority)
    {
        if (!removeStudent(name))
            return false;
        addStudent(name, newPriority);
        return true;
    }

    // Removes the student at the front when the book is returned
    bool serveFront(string& name)
    {
        if (head == nullptr)
            return false;
        StudentNode* temp = head;
        name = temp->name;
        head = head->next;
        delete temp;
        return true;
    }

    void display()
    {
        if (head == nullptr)
        {
            cout << "No reservations." << endl;
            return;
        }
        int position = 1;
        StudentNode* current = head;
        while (current != nullptr)
        {
            cout << position << ". " << current->name
                 << " (" << priorityName(current->priority) << ")" << endl;
            current = current->next;
            position++;
        }
    }

    int countStudents()
    {
        int count = 0;
        StudentNode* current = head;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }
};

const int BOOKS = 3;

int main()
{
    string titles[BOOKS] = {"Data Structures", "Operating Systems", "Database Systems"};
    ReservationList books[BOOKS];

    // Demonstration with sample data (two books, multiple students)
    cout << "--- Demonstration with sample data ---" << endl;
    books[0].addStudent("Ali", 3);
    books[0].addStudent("Sara", 1);
    books[0].addStudent("Usman", 2);
    books[0].addStudent("Hina");
    books[1].addStudent("Bilal", 2);
    books[1].addStudent("Zara", 3);

    cout << "Reservations for " << titles[0] << ":" << endl;
    books[0].display();
    cout << "Reservations for " << titles[1] << ":" << endl;
    books[1].display();

    cout << "\nHina changes her priority to Research:" << endl;
    books[0].updatePriority("Hina", 1);
    books[0].display();

    cout << "\nUsman cancels his reservation:" << endl;
    books[0].removeStudent("Usman");
    books[0].display();
    cout << "Students waiting: " << books[0].countStudents() << endl;

    string served;
    books[0].serveFront(served);
    cout << "\nBook returned - " << served << " gets \"" << titles[0] << "\":" << endl;
    books[0].display();
    cout << "--- End of demonstration ---" << endl;

    int choice, book, priority;
    string name;
    do
    {
        cout << "\n1. Add a student to a reservation list";
        cout << "\n2. Cancel a reservation";
        cout << "\n3. Update a student's priority";
        cout << "\n4. Display reservation list of a book";
        cout << "\n5. Count students in a reservation list";
        cout << "\n6. Book returned (serve the first student)";
        cout << "\n7. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 7)
        {
            cout << "Invalid choice." << endl;
            continue;
        }
        if (choice == 7)
        {
            cout << "Exiting..." << endl;
            break;
        }

        cout << "Select a book:" << endl;
        for (int i = 0; i < BOOKS; i++)
            cout << "  " << i + 1 << ". " << titles[i] << endl;
        cout << "Enter book number: ";
        cin >> book;
        if (book < 1 || book > BOOKS)
        {
            cout << "Invalid book." << endl;
            continue;
        }
        book--;

        switch (choice)
        {
        case 1:
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter priority (1 = Research, 2 = Assignment, 3 = Casual reading): ";
            cin >> priority;
            if (priority < 1 || priority > 3)
                priority = 3;
            books[book].addStudent(name, priority);
            cout << name << " added." << endl;
            break;
        case 2:
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            if (books[book].removeStudent(name))
                cout << "Reservation cancelled." << endl;
            else
                cout << "Student not found." << endl;
            break;
        case 3:
            cout << "Enter student name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter new priority (1 = Research, 2 = Assignment, 3 = Casual reading): ";
            cin >> priority;
            if (priority < 1 || priority > 3)
                priority = 3;
            if (books[book].updatePriority(name, priority))
                cout << "Priority updated." << endl;
            else
                cout << "Student not found." << endl;
            break;
        case 4:
            cout << "Reservations for " << titles[book] << ":" << endl;
            books[book].display();
            break;
        case 5:
            cout << "Students waiting: " << books[book].countStudents() << endl;
            break;
        case 6:
            if (books[book].serveFront(name))
                cout << name << " can now borrow \"" << titles[book] << "\"." << endl;
            else
                cout << "No reservations for this book." << endl;
            break;
        }
    } while (true);

    return 0;
}
