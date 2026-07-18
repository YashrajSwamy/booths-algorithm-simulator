#include <stdio.h>

void binary(int num, int bit[], int n)
{
    for (int i = 0; i < n; i++)
    {
        bit[i] = (num >> i) & 1;
    }
}
int nBin(int n)
{
    if (n >= -8 && n <= 7)
        return 4;
    if (n >= -16 && n <= 15)
        return 5;
    if (n >= -32 && n <= 31)
        return 6;
}
void display(int a[],int n)
{
    for (int i = n - 1; i >= 0; i--)
        printf("%d", a[i]);
}

void rightShift(int A[], int Q[], int Qn, int n)
{
    Qn = Q[0];
    for (int i = 1; i < n; i++) Q[i - 1] = Q[i];
    Q[n - 1] = A[0];
    for (int i = 1; i < n; i++) A[i - 1] = A[i];
    display(A,n);
    printf("   ");
    display(Q,n);
    printf("      %d", Qn);
}
int main()
{
    // Accepting Two Numbers
    int a = 0, b = 0;
    printf("Enter The First Number: ");
    scanf("%d", &a);
    printf("Enter The Second Number: ");
    scanf("%d", &b);
    // Decimal -> binary
    int aN = nBin(a), bN = nBin(b);
    int n = aN > bN ? aN : bN;
    int c = n;
    int M[n], Q[n], A[n], minusM[n];
    int Qn = 0;
    binary(a, M, n);
    binary(b, Q, n);
    // Initialize A
    for(int i = 0; i < n; i++)
        A[i] = 0;
    // Initialize Q
    for(int i = n - 1; i >= 0; i--)
        Q[i] = Q[i];
    // Find -M

    printf("\nM in Binary: ");
    display(M,n);
    printf(" | ");
    printf("Q in Binary: ");
    display(Q,n);
    printf("\n\n");
    printf("Count   A      Q      Qn-1     Action\n");
    while(c)
    {
        if (Q[0]==0 && Qn==0 || Q[0]==1 && Qn==1)
        {
            printf(" %d     ",c);
            rightShift(A, Q, Qn, n);
            printf("    Right Shift");
        }
        break;
    }
}