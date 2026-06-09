#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Swap function
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Hoare Partition
int hoarePartition(int A[], int l, int r)
{
    int p = A[l];      // First element as pivot
    int i = l;
    int j = r + 1;

    while (1)
    {
        // Move i right
        do
        {
            i++;
        } while (i <= r && A[i] < p);

        // Move j left
        do
        {
            j--;
        } while (A[j] > p);

        if (i >= j)
            break;

        swap(&A[i], &A[j]);
    }

    swap(&A[l], &A[j]);

    return j;
}

// Quick Sort
void quickSort(int A[], int l, int r)
{
    if (l < r)
    {
        int s = hoarePartition(A, l, r);

        quickSort(A, l, s - 1);
        quickSort(A, s + 1, r);
    }
}

// Print array
void printArray(int A[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", A[i]);

    printf("\n");
}

int main()
{
    int n;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int A[n];

    srand(time(0));

    // Generate random numbers
    for (int i = 0; i < n; i++)
        A[i] = rand() % 10000;

    printf("\nOriginal Array:\n");
    printArray(A, n);

    clock_t start = clock();

    quickSort(A, 0, n - 1);

    clock_t end = clock();

    printf("\nSorted Array:\n");
    printArray(A, n);

    double time_taken =
        ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\nTime Taken = %f seconds\n", time_taken);

    return 0;
}