#include <stdio.h>

int board[20][20];
int N;

// Function to print the board
void printBoard()
{
    int i, j;

    printf("\nSolution:\n");

    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

// Function to check whether queen can be placed
int isSafe(int row, int col)
{
    int i, j;

    // Check column
    for(i = 0; i < row; i++)
    {
        if(board[i][col] == 1)
            return 0;
    }

    // Check left diagonal
    for(i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--)
    {
        if(board[i][j] == 1)
            return 0;
    }

    // Check right diagonal
    for(i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++)
    {
        if(board[i][j] == 1)
            return 0;
    }

    return 1;
}

// Function to solve N-Queens
int solveNQueens(int row)
{
    int col;

    // All queens are placed
    if(row == N)
    {
        printBoard();
        return 1;
    }

    for(col = 0; col < N; col++)
    {
        if(isSafe(row, col))
        {
            board[row][col] = 1;

            if(solveNQueens(row + 1))
                return 1;

            // Backtracking
            board[row][col] = 0;
        }
    }

    return 0;
}

int main()
{
    int i, j;

    printf("Enter number of queens: ");
    scanf("%d", &N);

    // Initialize board with 0
    for(i = 0; i < N; i++)
    {
        for(j = 0; j < N; j++)
        {
            board[i][j] = 0;
        }
    }

    if(solveNQueens(0) == 0)
        printf("Solution does not exist");

    return 0;
}
