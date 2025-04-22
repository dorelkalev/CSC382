#include <iostream>
#include <cstdlib>
#include <chrono>
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
    x = heap[1];  // root has the smallest key
    T y = heap[Size--]; // last element
    int vacant = 1;
    int child = 2; // left child
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
    using namespace std::chrono;

    srand(time(0));

    vector<int> input_sizes = {1000, 10000, 25000, 50000, 150000, 250000};

    cout << "Input Length\tHeap Sort (seconds)\tInsertion Sort (seconds)\tMerge Sort (seconds)\tBest time" << endl;

    for (int N : input_sizes) {
        int* original = new int[N];
        for (int i = 0; i < N; i++) {
            original[i] = rand();
        }

        int* arr_heap = new int[N];
        int* arr_insertion = new int[N];
        int* arr_merge = new int[N];

        copy(original, original + N, arr_heap);
        copy(original, original + N, arr_insertion);
        copy(original, original + N, arr_merge);

        double heap_time, insertion_time, merge_time;

        auto start = high_resolution_clock::now();
        heapSort(arr_heap, N);
        auto end = high_resolution_clock::now();
        heap_time = duration<double>(end - start).count();

        start = high_resolution_clock::now();
        insertionSort(arr_insertion, N);
        end = high_resolution_clock::now();
        insertion_time = duration<double>(end - start).count();

        start = high_resolution_clock::now();
        mergeSort(arr_merge, 0, N - 1);
        end = high_resolution_clock::now();
        merge_time = duration<double>(end - start).count();

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

        cout << N << "\t\t"
             << fixed << setprecision(2) << heap_time << "\t\t\t"
             << fixed << setprecision(2) << insertion_time << "\t\t\t"
             << fixed << setprecision(2) << merge_time << "\t\t"
             << best_time << endl;

        delete[] original;
        delete[] arr_heap;
        delete[] arr_insertion;
        delete[] arr_merge;
    }

    return 0;
}
