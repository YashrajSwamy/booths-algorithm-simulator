#include <stdio.h>

int nBin(int n)
{
    if (n >= -8 && n <= 7)
        return 4;
    if (n >= -16 && n <= 15)
        return 5;
    if (n >= -32 && n <= 31)
        return 6;
}

void convBin(int num, int bit[], int n)
{
    for (int i = 0; i < n; i++)
    {
        bit[i] = (num >> i) & 1;
    }
}

void findMinusM(int M[],int minusM[],int n)
{
    //1s Complement
    for(int i = 0;i<n;i++) minusM[i] = !M[i];

    //2s Complement = 1s Complement + 1
    int c = 1;
    for(int i = 0;i<n;i++)
    {
        int sum = minusM[i] + c;
        minusM[i] = sum%2;
        c = sum/2;
    }
}

void display(int a[],int n)
{
    for (int i = n - 1; i >= 0; i--)
        printf("%d", a[i]);
}

void addBin(int A[], int M[],int n)
{
    int c = 0;
    for(int i = 0;i<n;i++)
    {
        int sum =  A[i]+M[i]+c;
        A[i] = sum%2;
        c = sum/2;
    }
}

void rightShift(int A[], int Q[], int *Qn, int n)
{
    *Qn = Q[0];
    for (int i = 1; i < n; i++) Q[i - 1] = Q[i];
    Q[n - 1] = A[0];
    int s = A[n-1];
    for (int i = 1; i < n; i++) A[i - 1] = A[i];
    A[n-1] = s;
}

void checkCondition(int c, int A[], int Q[], int M[], int minusM[],int *Qn, int n)
{
    if(c==n)
        {
            printf(" %d     ",c);
            display(A,n);
            printf("   ");
            display(Q,n);
            printf("      %d", *Qn);
            printf("    Initialize\n");
        }
        else if (Q[0]==0 && *Qn==0 || Q[0]==1 && *Qn==1)
        {
            rightShift(A, Q, Qn, n);
            printf(" %d     ",c);
            display(A,n);
            printf("   ");
            display(Q,n);
            printf("      %d", *Qn);
            printf("    Right Shift\n");
        }
        else if(Q[0]==1 && *Qn==0)
        {
            printf(" %d     ",c);
            // A<- A-M => A<- A+(-M)
            addBin(A,minusM,n);
            //Right Shift
            display(A,n);
            printf("   ");
            display(Q,n);
            printf("      %d", *Qn);
            printf("      A <- A-M\n");
            rightShift(A, Q, Qn, n);
            printf("       ");
            display(A,n);
            printf("   ");
            display(Q,n);
            printf("      %d", *Qn);
            printf("    Right Shift\n");
        }
        else if(Q[0]==0 && *Qn==1)
        {
            printf(" %d     ",c);
            // A<- A+M
            addBin(A,M,n);
            //Right Shift
            display(A,n);
            printf("   ");
            display(Q,n);
            printf("      %d", *Qn);
            printf("      A <- A+M\n");
            rightShift(A, Q, Qn, n);
            printf("       ");
            display(A,n);
            printf("   ");
            display(Q,n);
            printf("      %d", *Qn);
            printf("    Right Shift\n");
        }
        else
            printf("Error");
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
    int M[n], Q[n], A[n], minusM[n];
    int Qn = 0;
    convBin(a, M, n);
    convBin(b, Q, n);
    // Initialize A
    for(int i = 0; i < n; i++)
        A[i] = 0;
    // Initialize Q
    for(int i = n - 1; i >= 0; i--)
        Q[i] = Q[i];
    // Find -M 1s comp then 2s
    findMinusM(M,minusM,n);
    
    //Displaying
    printf("\nM in Binary: ");
    display(M,n);
    printf(" | ");
    printf("Q in Binary: ");
    display(Q,n);
    printf(" | ");
    printf("-M in Binary: ");
    display(minusM,n);
    printf("\n\n");

    //Table
    printf("Count   A      Q      Qn-1     Action\n");
    for(int i = n;i>=0;i--)
        checkCondition(i,A,Q,M,minusM,&Qn,n);
}