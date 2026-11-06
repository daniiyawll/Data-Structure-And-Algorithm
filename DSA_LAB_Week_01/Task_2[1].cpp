#include <iostream>
#include <string>
using namespace std;

template <typename T, int N>
void selectionSort(T (&A)[N])
{
    for (int I = 0; I < N - 1; I++)
    {
        int SmallSub = I;
        for (int J = I + 1; J < N; J++)
        {
            if (A[J] < A[SmallSub])
            {
                SmallSub = J;
            }
        }
        T temp = A[I];
        A[I] = A[SmallSub];
        A[SmallSub] = temp;
    }
}

template <typename T, int N>
void printArray(T (&A)[N])
{
    for (int i = 0; i < N; i++)
    {
        cout << A[i] << " ";
    }
    cout << endl;
}

int main() {
    // Test with an integer array of size 5
    int intArray[5] = {64, 25, 12, 22, 11};
    cout << "Original integer array: ";
    printArray(intArray);
    selectionSort(intArray);
    cout << "Sorted integer array: ";
    printArray(intArray);

    // Test with a string array of size 4
    string stringArray[4] = {"apple", "orange", "banana", "grape"};
    cout << "\nOriginal string array: ";
    printArray(stringArray);
    selectionSort(stringArray);
    cout << "Sorted string array: ";
    printArray(stringArray);

    return 0;
}
