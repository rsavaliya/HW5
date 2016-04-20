#include <iostream>
#include <fstream>

using namespace std;

void bubbleSort (int A[], int n);
void insertionSort (int A[], int n);
int partition(int A[], int low, int high);
void quickSort (int A[], int low, int high);
void shellSort (int A[], int n);
void merge (int A[], int low, int high, int mid);
void mergeSort (int A[], int low, int high);
void sort (string file);
void readFile (string file, int A[]);

int mCompare = 0, mSwap = 0, qCompare = 0, qSwap = 0; // to keep track of swaps and compares in merge and quick sort

int main()
{
    sort("Random.txt");
    sort("FewUnique.txt");
    sort("NearlySorted.txt");
    sort("Reversed.txt");
    
    return 0;
}

void bubbleSort (int A[], int n) // n is the number of ints in the array
{
    int i, j, temp, swap = 0, compare = 0;
    for (i = 0; i < n; ++i)
        for (j = 0; j < n - i - 1; ++j)
        {
            compare++; // add a count to compare because this is where it gets compared
            if (A[j] > A[j+1]) // if your current int is greater than the next int in the array switch it
            {
                temp = A[j];
                A[j] = A[j+1];
                A[j=1] = temp;
                swap++; // add a count to swap
            }
        }
    cout << "Bubble sort number of exchanges: " << swap << endl;
    cout << "Bubble sort number of comparisons: " << compare << endl;
}

void insertionSort (int A[], int n) // n is the number of ints in the array
{
    int i, j, element, swap = 0, compare = 0;
    for (i = 0; i<n; i++)
    {
        element = A[i]; // set the element to the int at the current index
        j = i; // set j to the current index we are at in the array
        while ((j>0) && (A[j-1] > element)) // function does not work if j and i are 0, also checks if the int below is greater than what we have if its true, we move down one
        {
            A[j] = A[j-1];
            j = j-1;
            compare++; // add a count to compare
            swap++; // add a count to swap
        }
        A[j] = element; // set the place we ended at to be the element
        compare++; // add count to swap
    }
    cout << "Insertion sort number of exchanges: " << swap << endl;
    cout << "Insertion sort number of comparisons: " << compare << endl;
}

int partition(int A[], int low, int high)
{
    int pivot, i, j, temp;
    pivot = A[low]; // set pivot to the int at low
    j = low;
    for(i = low + 1; i <= high; i++)
    {
        qCompare++; // increase count of compare
        if (A[i] <= pivot) // this is a swap function
        {
            temp = A[i];
            A[i] = A[j];
            A[j] = temp;
            qSwap++; // increase count of swap
        }
    }
    A[low] = A[j]; // set the int at low to equal the int at index j
    A[j] = pivot; // set the int at index j equal to the pivot int
    qSwap++;
    return j;
}

void quickSort (int A[], int low, int high)
{
    int j;
    if (low < high)
    {
        j = partition(A, low, high);
        quickSort(A, low, j-1); // recursive function that does the quick sort up to the partition
        quickSort(A, j+1, high); // recursive function that does the quick sort above the partition
    }
}

void shellSort (int A[], int n) // n is the number of ints in the array
{
    int temp, gap, i, swap = 0, compare = 0;
    int swapped;
    gap = n/2; // we want the gap to be halfway through
    do // do once and keep going as long as half the gap is greater than 1
    {
        do // do once and keep going as long as swapped is 1
        {
            swapped = 0; // set swapper to 0
            for (i=0; i < n-gap; i++)
            {
                compare++; // add a count to compare
                if (A[i] > A[i+gap]) // if its true swap the values and set swapped to 1
                {
                    temp = A[i];
                    A[i] = A[i + gap];
                    A[i + gap] = temp;
                    swapped = 1;
                    swap++; // increase count of swap
                }
            }
        } while (swapped == 1);
    } while ((gap = gap/2) >= 1);
    cout << "Shell sort number of exchanges: " << swap << endl;
    cout << "Shell sort number of comparisons: " << compare << endl;
}

void merge (int A[], int low, int high, int mid)
{
    int i, j, k, C[10000];
    i = low;
    j = mid + 1;
    k = 0;
    while (( i <= mid) && (j <=high)) // as long as i is at most the mid, and j is at most the high
    {
        mCompare++; // add to compare count
        if (A[i] < A[j]) // if A at i is less than A at j add the int of A at i=1 to C at k
        {
            C[k] = A[i++];
            mSwap++; // add to swap count
        }
        else
        {
            C[k] = A[j++]; // otherwise add A at j=1 to C at k
            mSwap++; // add to swap count
        }
        k++;
    }
    while (i <= mid) // as long as i is less than mid, keep adding A at i to C at k
    {
        C[k++] = A[i++];
        mSwap++; // add to swap count
    }
    while (j <= high) // as long as j is less than high, keep adding A at j to C at k
    {
        C[k++] = A[j++];
        mSwap++; // add to swap count
    }
    for (i = low, j = 0; i <= high; i++, j++) // set A at i to C at i, making it so the original array is similar to array created for the merge sort
    {
        A[i] = C[j];
    }
}

void mergeSort (int A[], int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low+high)/2; // find mid of high and low
        mergeSort(A, low, mid); // recursive function that sorts up to the mid
        mergeSort(A, mid+1, high); //recursive function that sorts above the mid
        merge(A, low, high, mid); // the function for merge
    }
}

void readFile (string file, int A[])
{
    ifstream in;
    in.open(file);
    for (int i = 0; i < 10000; i++) // for loop to go through each number in the doc and put it into the array
    {
        in >> A[i];
    }
    in.clear();
    in.close();
}

void sort (string file)
{
    cout << "Sorting for file: " << file << endl;
    
    int A[10000];
    readFile(file, A);
    bubbleSort(A, 10000);
    
    readFile(file, A);
    insertionSort(A, 10000);
    
    readFile(file, A);
    shellSort(A, 10000);
    
    readFile(file, A);
    mergeSort(A, 0, 9999);
    cout << "Merge sort number of exchanges: " << mSwap << endl;
    cout << "Merge sort number of comparisons: " << mCompare << endl;
    mSwap = 0;
    mCompare = 0;
    
    readFile(file, A);
    quickSort(A, 0, 9999);
    cout << "Quick sort number of exchanges: " << qSwap << endl;
    cout << "Quick sort number of comparisons: " << qCompare << endl;
    qSwap = 0;
    qCompare = 0;
    
    cout << endl;

}