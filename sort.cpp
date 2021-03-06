#include <stdlib.h>
#include <time.h>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

int recursion_depth_divide = 0;
int recursion_depth_CoC = 0;

const int MAX_SIZE = 10000000;

// Set this to true if you wish the arrays to be printed.
const bool OUTPUT_DATA = false;


void ReadInput(string& sortAlg, int& size);

void GenerateSortedData(int data[], int size);
void GenerateNearlySortedData(int data[], int size);
void GenerateReverselySortedData(int data[], int size);
void GenerateRandomData(int data[], int size);

void Sort(int data[], int size, string sortAlg, char* dataType);

void InsertionSort(int data[], int size);
void MergeSort(int data[], int lo, int hi);
void QuickSort(int data[], int lo, int hi);
void LibSort(int data[], int size);

void Swap(int &x, int &y);

bool IsSorted(int data[], int size);
void printData(int data[], int size, string title);


// Helper functions declarations
void Merge(int data[], int lo, int q, int hi);
int Partition(int data[], int lo, int hi);

int main(void)
{
    int recursion_depth_divide = 0;
    int recursion_depth_CoC = 0;
    int size;
    string sortAlg;
    ReadInput(sortAlg, size);

    int * data = new int[size];
    if( data == NULL)
    {
        cout << "\n Memory allocation error." << endl;
        exit(1);
    }

    GenerateSortedData(data, size);
    Sort(data, size, sortAlg,"Sorted Data");

    GenerateNearlySortedData(data, size);
    Sort(data, size, sortAlg,"Nearly Sorted Data");

    GenerateReverselySortedData(data, size);
    Sort(data, size, sortAlg,"Reversely Sorted Data");

    GenerateRandomData(data, size);
    Sort(data, size, sortAlg,"Random Data");

    cout << "\nProgram Completed Successfully." << endl;;

    delete [] data;

    return 0;
}
/********************************************************************/




void ReadInput(string& sortAlg, int& size)
{
    cout << "  I:\tInsertion Sort" << endl;
    cout << "  M:\tMergeSort" << endl;
    cout << "  Q:\tQuickSort" << endl;
    cout << "  L:\tLibSort" << endl;
    cout << "Enter sorting algorithm: ";
    cin >> sortAlg;
    string sortAlgName;


    if(sortAlg == "I")
        sortAlgName = "Insertion Sort";
    else if(sortAlg == "M"){
        recursion_depth_divide = 0;
        recursion_depth_CoC = 0;
        sortAlgName = "MergeSort";
    }
    else if(sortAlg == "Q"){
        recursion_depth_divide = 0;
        recursion_depth_CoC = 0;
        sortAlgName = "QuickSort";
    }
    else if(sortAlg == "L")
        sortAlgName = "LibSort";
    else {
        cout << "\nUnrecognized sorting algorithm Code: " << sortAlg << endl;
        exit(1);
    }

    cout << "Enter input size: ";
    cin >> size;

    cout << "\nSorting Algorithm: " << sortAlgName;
    cout << "\nInput Size = " << size << endl;
    cout << endl;

}
/******************************************************************************/




void GenerateSortedData(int data[], int size)
{
    int i;

    for(i=0; i<size; i++)
        data[i] = i * 3 + 5;
}
/*****************************************************************************/



void GenerateNearlySortedData(int data[], int size)
{
    int i;

    GenerateSortedData(data, size);

    for(i=0; i<size; i++)
        if(i % 10 == 0)
            if(i+1 < size)
                data[i] = data[i+1] + 7;
}
/*****************************************************************************/



void GenerateReverselySortedData(int data[], int size)
{
    int i;

    for(i = 0; i < size; i++)
        data[i] = (size-i) * 2 + 3;
}
/*****************************************************************************/



void GenerateRandomData(int data[], int size)
{
    int i;

    for(i = 0; i < size; i++)
        data[i] = rand();
}
/*****************************************************************************/


void Sort(int data[], int size, string sortAlg, char* dataType)
{

    cout << endl << dataType << ":";


    if (OUTPUT_DATA)
        printData(data, size, "Data before sorting:");



    // Sorting is about to begin ... start the timer!
    clock_t start = clock();


    if(sortAlg == "I")
        InsertionSort(data, size);
    else if(sortAlg == "M")
        MergeSort(data, 0, size-1);
    else if(sortAlg == "Q")
        QuickSort(data, 0, size-1);
    else if(sortAlg == "L")
        LibSort(data, size);
    else
    {
        cout << "Invalid sorting algorithm!" << endl;
        exit(1);
    }

    // Sorting has finished ... stop the timer!
    clock_t end = clock();
    double elapsed = (((double) (end - start)) / CLOCKS_PER_SEC) * 1000;



    if (OUTPUT_DATA)
        printData(data, size, "Data after sorting:");


    if (IsSorted(data, size))
    {
        cout << "\nCorrectly sorted " << size << " elements in " << elapsed << "ms";
    }
    else
        cout << "ERROR!: INCORRECT SORTING!" << endl;
    cout << "\n-------------------------------------------------------------\n";
}
/*****************************************************************************/




bool IsSorted(int data[], int size)
{
    int i;

    for(i=0; i<(size-1); i++)
    {
        if(data[i] > data[i+1])
            return false;
    }
    return true;
}
/*****************************************************************************/




void InsertionSort(int data[], int size)
{
    //Write your code here
    int temp = 0, i, j=0;
    for (i = 0; i <= size - 1; i++){
        temp = data[i];
        for(j = i-1; j >= 0; j--){
            if(data[j] > temp){
                data[j+1] = data[j];
            }
            else{
                break;
            }
        }
        data[j+1] = temp;
    }
}
/*****************************************************************************/




void MergeSort(int data[], int lo, int hi)
{
    //Write your code here
    //You may create other functions if needed
    if (lo == hi){
        return;
    }
    int q = (lo + hi)/2;
    MergeSort(data, lo, q);
    MergeSort(data, q + 1, hi);
    Merge(data, lo, q, hi);
}

void Merge(int data[], int lo, int q, int hi) {
    int n1, n2;
    n1 = q - lo + 1;
    n2 = hi - q;

    int L[n1 + 1], R[n2 + 1];

    int Large = max(L[n1 + 1], R[n2 + 1]) + 1;

    for(int i = 0; i < n1; i++){
        L[i] = data[lo + i - 1];
    }
    for(int j = 0; j < n2; j++){
        R[j] = data[q + j];
    }

    L[n1 + 1] = Large;
    R[n2 + 1] = Large;

    int i = 1, j = 1;
    for(int k = lo; k < hi; k++){
        if(L[i] <= R[j]){
            data[k] = L[i];
            i++;
        }
        else{
            data[k] = R[j];
            j++;
        }
    }

}


void QuickSort(int data[], int lo, int hi)
{
    if(lo >= hi){
        return;
    }
    int q = Partition(data, lo, hi);
    QuickSort(data, lo, q-1);
    QuickSort(data, q+1, hi);
}

int Partition(int data[], int lo, int hi){
    int x = data[hi];                      // PIVOT
    int i = lo - 1;

    for(int j = lo; j<= hi - 1; j++){
        if(data[j] <= x){
            Swap(data[j], data[i+1]);
            i++;
        }
    }
    Swap(data[hi], data[i+1]);
    return i+1;
}
/*****************************************************************************/



void LibSort(int data[], int size)
{
    sort(data, size + data);
}
/*****************************************************************************/




void Swap(int &x, int &y)
{
    int temp = x;
    x = y;
    y = temp;
}
/*****************************************************************************/




void printData(int data[], int size, string title) {
    int i;

    cout << endl << title << endl;
    for(i=0; i<size; i++)
    {
        cout << data[i] << " ";
        if(i%10 == 9 && size > 10)
            cout << endl;
    }
}
