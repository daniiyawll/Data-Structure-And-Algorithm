#include <iostream>
#include <string>
using namespace std;

template <typename T, int N>
int linearSearch(T (&A)[N], T Value)
{
    for (int I = 0; I < N; I++)
    {
        if (A[I] == Value)
        {
            return I;
        }
    }
    return -1;
}

template <typename T>
void printSearchResult(int index, T key)
{
    if (index != -1)
        cout << "Element " << key << " found at index " << index << endl;
    else
        cout << "Element " << key << " not found" << endl;
}

int main() {
    // Test with an integer array of size 5
    int intArray[5] = {64, 25, 12, 22, 11};
    int intKey = 12;
    int intIndex = linearSearch(intArray, intKey);
    printSearchResult(intIndex, intKey);

    // Test with a float array of size 4
    float floatArray[4] = {3.14, 2.71, 1.62, 0.57};
    float floatKey = 1.62;
    int floatIndex = linearSearch(floatArray, floatKey);
    printSearchResult(floatIndex, floatKey);

    // Test with a string array of size 4
    string stringArray[4] = {"apple", "orange", "banana", "grape"};
    string stringKey = "banana";
    int stringIndex = linearSearch(stringArray, stringKey);
    printSearchResult(stringIndex, stringKey);

    return 0;
}
