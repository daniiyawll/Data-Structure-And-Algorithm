#include <iostream>
#include <string>
using namespace std;

template <typename T>
void selectionSort(T* A, int N)
{
    for (int I = 0; I < N - 1; I++)
    {
        int SmallSub = I;
        for (int J = I + 1; J < N; J++)
            if (A[J] < A[SmallSub])
                SmallSub = J;
        T temp = A[I];
        A[I] = A[SmallSub];
        A[SmallSub] = temp;
    }
}

template <typename T, typename K>
int linearSearch(T* A, int N, K Value)
{
    for (int I = 0; I < N; I++)
        if (A[I] == Value)
            return I;
    return -1;
}

class Publication
{
public:
    virtual void display() const = 0;
    virtual ~Publication() {}
};

class Book : public Publication
{
    string title;
    string author;
    int pages;
public:
    Book() { title = ""; author = ""; pages = 0; }
    Book(string title, string author, int pages)
    {
        this->title = title;
        this->author = author;
        this->pages = pages;
    }
    void display() const
    {
        cout << "Book: " << title << " by " << author << ", " << pages << " pages" << endl;
    }
    bool operator<(const Book& other) const { return pages < other.pages; }
    bool operator==(const string& key) const { return title == key; }
};

class Newspaper : public Publication
{
    string name;
    string date;
    string edition;
public:
    Newspaper() { name = ""; date = ""; edition = ""; }
    Newspaper(string name, string date, string edition)
    {
        this->name = name;
        this->date = date;
        this->edition = edition;
    }
    void display() const
    {
        cout << "Newspaper: " << name << ", " << date << ", " << edition << endl;
    }
    bool operator<(const Newspaper& other) const { return edition < other.edition; }
    bool operator==(const string& key) const { return name == key; }
};

class Library
{
    static const int MAX = 100;
    Book books[MAX];
    Newspaper newspapers[MAX];
    int bookCount;
    int newspaperCount;
public:
    Library() { bookCount = 0; newspaperCount = 0; }

    void addBook(const Book& b)
    {
        if (bookCount < MAX) books[bookCount++] = b;
    }
    void addNewspaper(const Newspaper& n)
    {
        if (newspaperCount < MAX) newspapers[newspaperCount++] = n;
    }
    void displayCollection() const
    {
        for (int i = 0; i < bookCount; i++) books[i].display();
        for (int i = 0; i < newspaperCount; i++) newspapers[i].display();
    }
    void sortBooksByPages() { selectionSort(books, bookCount); }
    void sortNewspapersByEdition() { selectionSort(newspapers, newspaperCount); }

    Book* searchBookByTitle(string title)
    {
        int index = linearSearch(books, bookCount, title);
        return (index == -1) ? 0 : &books[index];
    }
    Newspaper* searchNewspaperByName(string name)
    {
        int index = linearSearch(newspapers, newspaperCount, name);
        return (index == -1) ? 0 : &newspapers[index];
    }
};

int main() {
    // Create book objects
    Book book1("The Catcher in the Rye", "J.D. Salinger", 277);
    Book book2("To Kill a Mockingbird", "Harper Lee", 324);

    // Create newspaper objects
    Newspaper newspaper1("Washington Post", "2024-10-13", "Morning Edition");
    Newspaper newspaper2("The Times", "2024-10-12", "Weekend Edition");

    // Create a library object
    Library library;

    // Add books and newspapers to the library
    library.addBook(book1);
    library.addBook(book2);
    library.addNewspaper(newspaper1);
    library.addNewspaper(newspaper2);

    // Display the entire collection
    cout << "Before Sorting:\n";
    library.displayCollection();

    // Sort books by pages and newspapers by edition
    library.sortBooksByPages();
    library.sortNewspapersByEdition();
    cout << "\nAfter Sorting:\n";
    library.displayCollection();

    // Search for a book by title
    Book* foundBook = library.searchBookByTitle("The Catcher in the Rye");
    if (foundBook) {
        cout << "\nFound Book:\n";
        foundBook->display();
    } else {
        cout << "\nBook not found.\n";
    }

    // Search for a newspaper by name
    Newspaper* foundNewspaper = library.searchNewspaperByName("The Times");
    if (foundNewspaper) {
        cout << "\nFound Newspaper:\n";
        foundNewspaper->display();
    } else {
        cout << "\nNewspaper not found.\n";
    }

    return 0;
}
