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

// An action is either a typed character ('T') or a deleted character ('D')
struct Action
{
    char type;
    char ch;
};

class TextEditor
{
    string text;
    myStack<Action> undoStack;
    myStack<Action> redoStack;

    void clearRedo()
    {
        while (!redoStack.isEmpty())
            redoStack.pop();
    }

public:
    TextEditor() : undoStack(100), redoStack(100) {}

    void typeChar(char c)
    {
        text += c;
        Action a = {'T', c};
        undoStack.push(a);
        clearRedo();
    }

    void deleteChar()
    {
        if (text.empty())
        {
            cout << "Nothing to delete." << endl;
            return;
        }
        char c = text[text.length() - 1];
        text.erase(text.length() - 1);
        Action a = {'D', c};
        undoStack.push(a);
        clearRedo();
    }

    void undo()
    {
        if (undoStack.isEmpty())
        {
            cout << "Nothing to undo." << endl;
            return;
        }
        Action a = undoStack.pop();
        if (a.type == 'T')
            text.erase(text.length() - 1);   // undo typing: remove the character
        else
            text += a.ch;                    // undo deleting: put the character back
        redoStack.push(a);
    }

    void redo()
    {
        if (redoStack.isEmpty())
        {
            cout << "Nothing to redo." << endl;
            return;
        }
        Action a = redoStack.pop();
        if (a.type == 'T')
            text += a.ch;
        else
            text.erase(text.length() - 1);
        undoStack.push(a);
    }

    void show() const
    {
        cout << "Current text: \"" << text << "\"" << endl;
    }
};

int main()
{
    TextEditor editor;
    int choice;
    string input;
    do
    {
        cout << "\n1. Type text";
        cout << "\n2. Delete last character";
        cout << "\n3. Undo";
        cout << "\n4. Redo";
        cout << "\n5. Show text";
        cout << "\n0. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Enter text to type: ";
            cin.ignore();
            getline(cin, input);
            for (int i = 0; i < (int)input.length(); i++)
                editor.typeChar(input[i]);
            editor.show();
            break;
        case 2:
            editor.deleteChar();
            editor.show();
            break;
        case 3:
            editor.undo();
            editor.show();
            break;
        case 4:
            editor.redo();
            editor.show();
            break;
        case 5:
            editor.show();
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
