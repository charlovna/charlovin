#include <iostream>
using namespace std;

int main() {
    int array1[10], array2[10], merged[20];
    int size1, size2, totalSize = 0;
    char ch;

    cout << "Enter number of elements for array 1 (max 10): ";
    while (true) {
        if (cin >> size1 && size1 > 0 && size1 <= 10) {
            break;
        } else {
            cout << "Invalid input! No characters allowed, please try again.\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }

    cout << "Enter " << size1 << " elements for array 1: ";
    for (int i = 0; i < size1; i++) {
        cin >> array1[i];
    }

    cout << "Enter number of elements for array 2 (max 10): ";
    while (true) {
        if (cin >> size2 && size2 > 0 && size2 <= 10) {
            break;
        } else {
            cout << "Invalid input! No characters allowed, please try again.\n";
            cin.clear();
            while (cin.get() != '\n');
        }
    }

    cout << "Enter " << size2 << " elements for array 2: ";
    for (int i = 0; i < size2; i++) {
        cin >> array2[i];
    }

    for (int i = 0; i < size1; i++) {
        merged[totalSize++] = array1[i];
    }
    for (int i = 0; i < size2; i++) {
        merged[totalSize++] = array2[i];
    }

    for (int i = 0; i < totalSize; i++) {
        for (int j = i + 1; j < totalSize; j++) {
            if (merged[i] < merged[j]) {
                int temp = merged[i];
                merged[i] = merged[j];
                merged[j] = temp;
            }
        }
    }

    cout << "Merged array in descending order: ";
    for (int i = 0; i < totalSize; i++) {
        cout << merged[i] << " ";
    }
    cout << endl;

    return 0;
}
