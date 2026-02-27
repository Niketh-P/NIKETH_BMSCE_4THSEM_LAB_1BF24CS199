#include <stdio.h>

int main() {
    int rows, cols, i, j, sum;

    printf("Enter number of rows and columns: ");
    scanf("%d %d", &rows, &cols);
    
    int matrix[rows][cols];
    printf("Enter elements of the matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    printf("\nRow Sums:\n");
    for (i = 0; i < rows; i++) {
        sum = 0;
        for (j = 0; j < cols; j++) {
            sum += matrix[i][j];
        }
        printf("Sum of Row %d = %d\n", i + 1, sum);
    }
    printf("\nColumn Sums:\n");
    for (j = 0; j < cols; j++) {
        sum = 0;
        for (i = 0; i < rows; i++) {
            sum += matrix[i][j];
        }
        printf("Sum of Column %d = %d\n", j + 1, sum);
    }

    return 0;
}