#include <iostream>
#include <string>
using namespace std;

class PatientNode
{
public:
    string name;
    PatientNode* next;

    PatientNode(string name)
    {
        this->name = name;
        next = nullptr;
    }
};

// Waiting line of patients as a singly linked list ADT
class PatientList
{
    PatientNode* head;

public:
    PatientList()
    {
        head = nullptr;
    }

    ~PatientList()
    {
        while (head != nullptr)
        {
            PatientNode* temp = head;
            head = head->next;
            delete temp;
        }
    }

    // Adds a new patient to the end of the queue
    void addPatient(string name)
    {
        PatientNode* newNode = new PatientNode(name);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }
        PatientNode* current = head;
        while (current->next != nullptr)
            current = current->next;
        current->next = newNode;
    }

    // Removes a patient who cancelled
    bool removePatient(string name)
    {
        if (head == nullptr)
            return false;

        if (head->name == name)
        {
            PatientNode* temp = head;
            head = head->next;
            delete temp;
            return true;
        }

        PatientNode* current = head;
        while (current->next != nullptr && current->next->name != name)
            current = current->next;

        if (current->next == nullptr)
            return false;

        PatientNode* temp = current->next;
        current->next = temp->next;
        delete temp;
        return true;
    }

    // Displays the patients in order
    void display()
    {
        if (head == nullptr)
        {
            cout << "No patients are waiting." << endl;
            return;
        }
        int position = 1;
        PatientNode* current = head;
        while (current != nullptr)
        {
            cout << position << ". " << current->name << endl;
            current = current->next;
            position++;
        }
    }

    int countPatients()
    {
        int count = 0;
        PatientNode* current = head;
        while (current != nullptr)
        {
            count++;
            current = current->next;
        }
        return count;
    }
};

int main()
{
    PatientList patients;

    // Demonstration with sample data
    cout << "--- Demonstration with sample data ---" << endl;
    patients.addPatient("Ali");
    patients.addPatient("Sara");
    patients.addPatient("Usman");
    patients.addPatient("Hina");
    cout << "After adding Ali, Sara, Usman and Hina:" << endl;
    patients.display();
    cout << "Patients waiting: " << patients.countPatients() << endl;
    patients.removePatient("Usman");
    cout << "\nAfter Usman cancels:" << endl;
    patients.display();
    cout << "Patients waiting: " << patients.countPatients() << endl;
    cout << "--- End of demonstration ---" << endl;

    int choice;
    string name;
    do
    {
        cout << "\n1. Add a new patient";
        cout << "\n2. Remove a patient (cancelled)";
        cout << "\n3. Display patients";
        cout << "\n4. Count patients";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter patient name: ";
            cin.ignore();
            getline(cin, name);
            patients.addPatient(name);
            cout << name << " added." << endl;
            break;
        case 2:
            cout << "Enter patient name to remove: ";
            cin.ignore();
            getline(cin, name);
            if (patients.removePatient(name))
                cout << name << " removed." << endl;
            else
                cout << "Patient not found." << endl;
            break;
        case 3:
            patients.display();
            break;
        case 4:
            cout << "Patients waiting: " << patients.countPatients() << endl;
            break;
        case 5:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    } while (choice != 5);

    return 0;
}
