#include <iostream>
using namespace std;

inline void swapNums(int &x, int &y) {
    int temp = x; 
    x = y; 
    y = temp;
}

void doSelectionSort(int a[], int len) {
    for (int i = 0; i < len - 1; i++) {
        int minPos = i;
        for (int j = i + 1; j < len; j++) {
            if (a[j] < a[minPos]) minPos = j;
        }
        if (minPos != i) swapNums(a[i], a[minPos]);
    }
}

void combine(int a[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int *leftArr = new int[n1], *rightArr = new int[n2];

    for (int i = 0; i < n1; i++) leftArr[i] = a[l + i];
    for (int j = 0; j < n2; j++) rightArr[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) a[k++] = leftArr[i++];
        else a[k++] = rightArr[j++];
    }
    while (i < n1) a[k++] = leftArr[i++];
    while (j < n2) a[k++] = rightArr[j++];

    delete[] leftArr;
    delete[] rightArr;
}

void doMergeSort(int a[], int l, int r) {
    if (l < r) {
        int mid = (l + r) / 2;
        doMergeSort(a, l, mid);
        doMergeSort(a, mid + 1, r);
        combine(a, l, mid, r);
    }
}

int simpleSearch(int a[], int len, int val) {
    for (int i = 0; i < len; i++) {
        if (a[i] == val) return i;
    }
    return -1;
}

int fastSearch(int a[], int len, int val) {
    int low = 0, high = len - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (a[mid] == val) return mid;
        else if (a[mid] < val) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void show(int a[], int len) {
    for (int i = 0; i < len; i++) cout << a[i] << " ";
    cout << endl;
}

int main() {
    int size;
    cout << "How many numbers? ";
    cin >> size;

    if (size <= 0) {
        cout << "Size must be positive!" << endl;
        return 0;
    }

    int *data = new int[size];
    cout << "Enter values: ";
    for (int i = 0; i < size; i++) cin >> data[i];

    bool sorted = false;
    int option;

    while (true) {
        cout << endl << "--- MAIN MENU ---" << endl;
        cout << "1) Selection Sort" << endl;
        cout << "2) Merge Sort" << endl;
        cout << "3) Linear Search" << endl;
        cout << "4) Binary Search" << endl;
        cout << "5) Quit" << endl;
        cout << "Your choice: ";
        cin >> option;

        if (option == 1) {
            doSelectionSort(data, size);
            sorted = true;
            cout << "Sorted with Selection Sort: ";
            show(data, size);
        } 
        else if (option == 2) {
            doMergeSort(data, 0, size - 1);
            sorted = true;
            cout << "Sorted with Merge Sort: ";
            show(data, size);
        } 
        else if (option == 3) {
            int target;
            cout << "Enter number to find (linear): ";
            cin >> target;
            int pos = simpleSearch(data, size, target);
            if (pos >= 0) cout << "Found at index " << pos << endl;
            else cout << "Not found." << endl;
        } 
        else if (option == 4) {
            if (!sorted) {
                cout << "Array must be sorted. Sorting with merge sort..." << endl;
                doMergeSort(data, 0, size - 1);
                sorted = true;
            }
            int target;
            cout << "Enter number to find (binary): ";
            cin >> target;
            int pos = fastSearch(data, size, target);
            if (pos >= 0) cout << "Found at index " << pos << endl;
            else cout << "Not found." << endl;
        } 
        else if (option == 5) {
            cout << "Goodbye!" << endl;
            break;
        } 
        else {
            cout << "Invalid input, try again." << endl;
        }
    }

    delete[] data;
    return 0;
}
