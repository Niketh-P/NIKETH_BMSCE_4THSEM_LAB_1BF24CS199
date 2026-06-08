#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function to merge two sorted arrays into arr
void merge(int leftArr[], int n1, int rightArr[], int n2, int arr[])
{
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2)
    {
        if (leftArr[i] <= rightArr[j])
            arr[k++] = leftArr[i++];
        else
            arr[k++] = rightArr[j++];
    }

    // Copy remaining elements of leftArr
    while (i < n1)
        arr[k++] = leftArr[i++];

    // Copy remaining elements of rightArr
    while (j < n2)
        arr[k++] = rightArr[j++];
}

// Merge Sort function
void mergeSort(int arr[], int n)
{
    // Base case
    if (n <= 1)
        return;

    int mid = n / 2;

    // Create left and right subarrays
    int left[mid];
    int right[n - mid];

    // Copy elements into left subarray
    for (int i = 0; i < mid; i++)
        left[i] = arr[i];

    // Copy elements into right subarray
    for (int i = mid; i < n; i++)
        right[i - mid] = arr[i];

    // Recursively sort left and right halves
    mergeSort(left, mid);
    mergeSort(right, n - mid);

    // Merge sorted halves back into arr
    merge(left, mid, right, n - mid, arr);
}

// Print array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int main()
{
    clock_t start, end;
    double t;

    int m = 10;
    int arr[m];

    srand(time(0));

    // Generate random numbers
    for (int i = 0; i < m; i++)
        arr[i] = rand() % 100;

    printf("Original Array:\n");
    printArray(arr, m);

    start = clock();

    mergeSort(arr, m);

    end = clock();

    t = (double)(end - start) / CLOCKS_PER_SEC;

    printf("\nSorted Array:\n");
    printArray(arr, m);

    printf("\nTime Taken = %f seconds\n", t);

    return 0;
}
