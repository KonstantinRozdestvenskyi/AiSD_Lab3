#include<algorithm>
#include<fstream>
#include<iostream>
#include<time.h>
using namespace std;
const int N = 1000000;
int a[N];
fstream f1, f2, f3;
void make_test(int(&a)[N], int n) {
    for (int i = 0; i < n; i++) a[i] = rand() % 1000000;
}
void make_testBest(int(&a)[N], int n) {
    for (int i = 0; i < n; i++)
        a[i] = i + 1;
}

void selectionSort(int(&arrSort)[N], int size)
{
    int min, temp; // to find the minimum element and to exchange
    for (int i = 0; i < size - 1; i++)
    {
        min = i; // storing the index of the current element
        // we are looking for the minimum element to put in the place of the i-th
        for (int j = i + 1; j < size; j++)  // for the remaining elements after the i-th
        {
            if (arrSort[j] < arrSort[min]) // if the element is less than the minimum,
                min = j;       // remember its index in min
        }
        temp = arrSort[i];      // swapping the i-th and minimum elements
        arrSort[i] = arrSort[min];
        arrSort[min] = temp;
    }
}
void bubbleSort(int(&arrSort)[N], int size)
{
    // For all elements
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = (size - 1); j > i; j--) // for all elements after the ith
        {
            if (arrSort[j - 1] > arrSort[j]) // if the current element is smaller than the previous
            {
                int temp = arrSort[j - 1]; // swap them
                arrSort[j - 1] = arrSort[j];
                arrSort[j] = temp;
            }
        }
    }
}
int b[2 * N];
// Функция сортировки двухпутевым слиянием
void mergeSort(int(&a)[N], int l, int r) {
    if (r - l == 1) return;

    int m = (l + r) / 2;
    mergeSort(a, l, m);
    mergeSort(a, m, r);

    int left = l;
    int right = (l + r) / 2;

    for (int i = l; i < r; i++) {
        if (left == m) {
            b[i] = a[right++];
        }
        else if (right == r) {
            b[i] = a[left++];
        }
        else {
            if (a[right] < a[left]) b[i] = a[right++];
            else b[i] = a[left++];
        }
    }

    for (int i = l; i < r; i++) {
        a[i] = b[i];
    }


}
void quickSort(int(&a)[N], int l, int r) {
    if (l + 1 >= r) return;

    int pivot = a[r - 1];
    int left = l;

    for (int i = l; i < r; i++) {
        if (a[i] < pivot) {
            int t = a[i];
            a[i] = a[left];
            a[left++] = t;
        }
    }
    int t = a[r - 1];
    a[r - 1] = a[left];
    a[left] = t;
    quickSort(a, l, left);
    quickSort(a, left + 1, r);
}
void insertionSort(int(&arrSort)[N], int size)
{
    int temp, // temporary variable for storing the value of an element of the sorted array
        item; // index of the previous element
    for (int counter = 1; counter < size; counter++)
    {
        temp = arrSort[counter]; // initialize the temporary variable with the current value of the array element
        item = counter - 1; // we remember the index of the previous element of the array
        while (item >= 0 && arrSort[item] > temp) // as long as the index is not equal to 0 and the previous element of the array is larger than the current one
        {
            arrSort[item + 1] = arrSort[item]; // rearranging array elements
            arrSort[item] = temp;
            item--;
        }
    }
}
void shellSort(int(&arrSort)[N], int size) {
    int h = 1;
    while (h < size / 2) { //setting the sequence of distances
        h = 2 * h + 5;
    }
    while (h > 0) { //perform insertSort at the specified distances
        for (int i = 0; i < h; i++) {
            for (int j = i + h; j < size; j += h) {
                if (arrSort[j] < arrSort[j - h]) {
                    for (int k = j; k >= h; k -= h) {
                        if (arrSort[k] > arrSort[k - h]) break;
                        int t = arrSort[k];
                        arrSort[k] = arrSort[k - h];
                        arrSort[k - h] = t;
                    }
                }

            }
        }
        h /= 2;
    }
}
int sizes[21];
int sizes_sqr[100];
int main()//bubble_average - перезаписать, но график правильный
{
    int size = 100;
    for (int i = 0; i < 100; i++) {
        sizes_sqr[i] = size;
        size += 100;
    }
    sizes[0] = 10000;
    sizes[1] = 50000;
    int size1 = 100000;
    for (int i = 2; i < 21; i++) {
        sizes[i] = size1;
        size1 += 50000;
    }
    f1.open("shellSort_best.txt", ios::out);
    f2.open("shellSort_average.txt", ios::out);
    f3.open("shellSort_worst.txt", ios::out);
    srand(time(0));
    for (int i = 0; i < 21; i++) {

        int work_time = 0; // total time
        int best_time = 9999999;
        int worst_time = 0;
        int n = sizes[i]; // array size
        int tests = 100; // test amount

        for (int test = 1; test <= tests; test++) {
            make_test(a, n);

            int start = clock();
            shellSort(a, n);
            int end = clock();

            for (int i = 1; i < n; i++) {
                if (a[i] < a[i - 1]) cout << "Wrong test\n";

            }
            work_time += end - start;
            worst_time = max(worst_time, end - start);
            best_time = min(best_time, end - start);
            cout << "Test #" << test << " works for " << end - start << "ms.\n";
        }
        f1 << '(' << n << ';' << best_time << ')';
        f2 << '(' << n << ';' << work_time / tests << ')';
        f3 << '(' << n << ';' << worst_time << ')';
        cout << "\n\nBest case for " << n << " is " << best_time << "ms." << endl;
        cout << "Avarage case for " << n << " is " << work_time / tests << "ms." << endl;
        cout << "Worst case for " << n << " is " << worst_time << "ms.\n\n" << endl;
    }
}