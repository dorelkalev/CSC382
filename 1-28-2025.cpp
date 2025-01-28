int Find(int A[], int n, int x) 
{
for (int i=0; i<n; i++)
  if (x == A[i])
    return (i+1);

return (0);
}


int RecF (int n)
{
if (n==0 || n==1)
  return n;
else return (RecF(n-1) + RecF(n-2))
}


int NRec (int n)
{
int F(max);
F(0) = 0; F(1) = 1;
For (int i = 2; i<=n; i++)
F(i) = F(i-1) + F(i-2);
return F(n);
}

