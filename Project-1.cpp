#include <iostream>
using namespace std;

int FiboR ( int n) // array of size n
{ if (n==0 || n==1)
return (n);
else return (FiboR (n-1) + FiboR(n-2));
}



int main() {



return 0;
}
