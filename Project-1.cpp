#include <iostream>
#include <ctime>
#include <iomanip>
#include <cmath>
#define MAX_N 100 

using namespace std;

int FiboR (int n) // array of size n
{if (n==0 || n==1)
return (n);
else return (FiboR (n-1) + FiboR(n-2));
}

int FiboNR (int n) // array of size n
{int F[MAX_N];
F[0]=0; 
F[1]=1;
for (int i =2; i <=n; i++)
{F[i] = F[i-1] + F[i-2];
}
return (F[n]);
}

int m[MAX_N]; // array to store previously calculated Fibonacci numbers

int MODFibR (int n) // array of size n
{
    if (n == 0 || n == 1) {
        return n;
    }
    if (m[n] != -1) {
        return m[n];
    }
    m[n] = MODFibR(n - 1) + MODFibR(n - 2);
    return m[n];
}

int main() {
    fill(begin(m), end(m), -1);
  
    int n_values[] = {1, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60};
  
    cout << "Fibonacci time analysis (recursive vs. non-recursive)" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << left << setw(10) << "Integer" 
         << setw(20) << "FiboR (seconds)" 
         << setw(20) << "MODFibR" 
         << setw(20) << "FiboNR (seconds)" 
         << "Fibo-value" << endl;
    cout << "------------------------------------------------------------" << endl;

    for (int n : n_values) {
        clock_t start = clock();
        FiboR(n);
        clock_t end = clock();
        double timeFiboR = double(end - start) / CLOCKS_PER_SEC;

        start = clock();
        MODFibR(n);
        end = clock();
        double timeMODFibR = double(end - start) / CLOCKS_PER_SEC;

        start = clock();
        FiboNR(n);
        end = clock();
        double timeFiboNR = double(end - start) / CLOCKS_PER_SEC;

        cout << left << setw(10) << n 
             << setw(20) << fixed << setprecision(4) 
             << setw(20) << fixed << setprecision(4) 
             << setw(20) << fixed << setprecision(4)
             << MODFibR(n) << endl;
    }

    return 0;
}
