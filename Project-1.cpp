#include <iostream>
#include <ctime>
using namespace std;

int FiboR (int n) // array of size n
{if (n==0 || n==1)
return (n);
else return (FiboR (n-1) + FiboR(n-2));
}

int FiboNR (int n) // array of size n
{int F[max];
F[0]=0; F[1]=1;
for (int i =2; i <=n; i++)
{F[i] = F[i-1] + F[i-2];
}
return (F[n]);
}

int m[MAX_N]; // Array to store previously calculated Fibonacci numbers

int MODFibR(int n) {
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
  
    cout << "Fibonacci time analysis (recursive vs. non-recursive)\n";
    cout << "Integer | FiboR (seconds) | MODFibR (seconds) | FiboNR (seconds) | Fibo-value\n";
    cout << "-------------------------------------------------------------\n";

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

        cout << n << "      | "
             << timeFiboR << "       | "
             << timeMODFibR << "        | "
             << timeFiboNR << "         | "
             << MODFibR(n) << endl; // Print Fibonacci value from MODFibR
    }

    return 0;
}
