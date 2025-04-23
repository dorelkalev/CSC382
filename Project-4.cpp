#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;

class NoMem {};
class OutOfBounds {};

template <class T>
class MinHeap {
public:
    MinHeap(int MSize) {
        MaxSize = MSize;
        heap = new T[MaxSize + 1];
        Size = 0;
    }
    ~MinHeap() { delete[] heap; }
    MinHeap<T>& Insert(T& x);
    MinHeap<T>& Delete(T& x);    
    int Size;

private:
    int MaxSize;
    T *heap;
};

template <class T>
MinHeap<T>& MinHeap<T>::Insert(T& x) {
    if (Size == MaxSize)
        throw NoMem();
    else {
        int i = ++Size;
        while (i != 1 && x < heap[i / 2]) {
            heap[i] = heap[i / 2];
            i /= 2;
        }
        heap[i] = x;
        return *this;
    }
}

template <class T>
MinHeap<T>& MinHeap<T>::Delete(T& x) {
    if (Size == 0) throw OutOfBounds();
    x = heap[1];
    T y = heap[Size--];
    int vacant = 1;
    int child = 2;
    while (child <= Size) {
        if (child < Size && heap[child] > heap[child + 1]) 
            child++;
        if (y <= heap[child]) break;
        heap[vacant] = heap[child];
        vacant = child;
        child *= 2;
    }
    heap[vacant] = y;
    return *this;
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void insertionSort(int A[], int n) {
    for (int i = 1; i < n; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
        }
        A[j + 1] = key;
    }
}

void merge(int A[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int *L = new int[n1], *R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = A[low + i];
    for (int j = 0; j < n2; j++)
        R[j] = A[mid + 1 + j];

    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        A[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        A[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int A[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low) / 2;
        mergeSort(A, low, mid);
        mergeSort(A, mid + 1, high);
        merge(A, low, mid, high);
    }
}

int main() {
    srand(time(0));

    vector<int> input_sizes;
    input_sizes.push_back(1000);
    input_sizes.push_back(10000);
    input_sizes.push_back(25000);
    input_sizes.push_back(50000);
    input_sizes.push_back(150000);
    input_sizes.push_back(250000);

    cout << left 
         << setw(15) << "Input Length" 
         << setw(20) << "Heap Sort (seconds)" 
         << setw(25) << "Insertion Sort (seconds)" 
         << setw(20) << "Merge Sort (seconds)" 
         << setw(15) << "Best time" 
         << endl;

    for (size_t i = 0; i < input_sizes.size(); i++) {  
        int N = input_sizes[i];

        int* original = new int[N];
        for (int j = 0; j < N; j++) {
            original[j] = rand();
        }

        int* arr_heap = new int[N];
        int* arr_insertion = new int[N];
        int* arr_merge = new int[N];

        copy(original, original + N, arr_heap);
        copy(original, original + N, arr_insertion);
        copy(original, original + N, arr_merge);

        double heap_time, insertion_time, merge_time;

        clock_t start = clock();
        heapSort(arr_heap, N);
        clock_t end = clock();
        heap_time = double(end - start) / CLOCKS_PER_SEC;

        start = clock();
        insertionSort(arr_insertion, N);
        end = clock();
        insertion_time = double(end - start) / CLOCKS_PER_SEC;

        start = clock();
        mergeSort(arr_merge, 0, N - 1);
        end = clock();
        merge_time = double(end - start) / CLOCKS_PER_SEC;

        string best_time = "Heap";
        double min_time = heap_time;

        if (insertion_time < min_time) {
            min_time = insertion_time;
            best_time = "Insertion";
        }
        if (merge_time < min_time) {
            min_time = merge_time;
            best_time = "Merge";
        }

        cout << left << setw(15) << N 
             << setw(20) << fixed << setprecision(2) << heap_time 
             << setw(25) << insertion_time 
             << setw(20) << merge_time 
             << setw(15) << best_time 
             << endl;

        delete[] original;
        delete[] arr_heap;
        delete[] arr_insertion;
        delete[] arr_merge;
    }

    return 0;
}
