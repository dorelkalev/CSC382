#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int Insertion_Mod(int A[], int n) //in reality the elements to be sorted are indexed from
                                  //index 1 to index n
{
    int i, j, temp, comparisons = 0;
    A[0] = -32768; //smallest possible integer using 2 bytes integer representation

    for (i = 1; i <= n; i++) {
        j = i;
        while (A[j] < A[j - 1]) { //swap 
            comparisons++;
            temp = A[j];
            A[j] = A[j - 1];
            A[j - 1] = temp;
            j--;
        }
    }
  return comparisons;
}

int main() {
    srand(time(NULL));

    int sizes[] = {100, 500, 1000, 2500, 3000, 3500};
    int num_sizes = 6;
    int bound = 10000;
    double tot_number_steps;

  cout << "Input size   Calculated Average   Real Average" << endl;
    
    for (int i = 0; i < num_sizes; i++) {
        int n = sizes[i];
        tot_number_steps = 0;
        
        for (int j = 0; j < 100000; j++) {
            int A[n + 1];
            for (int k = 1; k <= n; k++) {
                A[k] = rand() % bound;
            }
            
            int comparisons = Insertion_Mod(A, n);
            tot_number_steps += comparisons;
        }
        
        double real_average = tot_number_steps / 100000;
        
        double calculated_average = (n * (n - 1)) / 4;

        cout << n << "           " << calculated_average << "              " << real_average << endl;
    }

    return 0;
}
