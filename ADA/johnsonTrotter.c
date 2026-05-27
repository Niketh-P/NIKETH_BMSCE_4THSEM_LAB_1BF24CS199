#include <stdio.h>

#define LEFT -1
#define RIGHT 1

// Function to print permutation
void printPermutation(int p[], int n)
{
    int i;

    for(i = 0; i < n; i++)
        printf("%d ", p[i]);

    printf("\n");
}

// Function to find mobile element
int getMobile(int p[], int dir[], int n)
{
    int mobile = 0;
    int mobileIndex = -1;
    int i;

    for(i = 0; i < n; i++)
    {
        // Moving left
        if(dir[p[i] - 1] == LEFT && i != 0)
        {
            if(p[i] > p[i - 1] && p[i] > mobile)
            {
                mobile = p[i];
                mobileIndex = i;
            }
        }

        // Moving right
        if(dir[p[i] - 1] == RIGHT && i != n - 1)
        {
            if(p[i] > p[i + 1] && p[i] > mobile)
            {
                mobile = p[i];
                mobileIndex = i;
            }
        }
    }

    return mobileIndex;
}

// Function to generate permutations
void johnsonTrotter(int n)
{
    int p[n], dir[n];
    int i;

    // Initialize permutation and directions
    for(i = 0; i < n; i++)
    {
        p[i] = i + 1;
        dir[i] = LEFT;
    }

    printPermutation(p, n);

    while(1)
    {
        int mobileIndex = getMobile(p, dir, n);

        if(mobileIndex == -1)
            break;

        int mobile = p[mobileIndex];

        // Swap according to direction
        if(dir[mobile - 1] == LEFT)
        {
            int temp = p[mobileIndex];
            p[mobileIndex] = p[mobileIndex - 1];
            p[mobileIndex - 1] = temp;

            mobileIndex--;
        }
        else
        {
            int temp = p[mobileIndex];
            p[mobileIndex] = p[mobileIndex + 1];
            p[mobileIndex + 1] = temp;

            mobileIndex++;
        }

        // Reverse direction of elements greater than mobile
        for(i = 0; i < n; i++)
        {
            if(p[i] > mobile)
                dir[p[i] - 1] *= -1;
        }

        printPermutation(p, n);
    }
}

int main()
{
    int n;

    printf("Enter value of n: ");
    scanf("%d", &n);

    johnsonTrotter(n);

    return 0;
}
