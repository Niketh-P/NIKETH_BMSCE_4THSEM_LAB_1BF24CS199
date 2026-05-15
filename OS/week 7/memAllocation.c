#include <stdio.h>

int main()
{
    int memory[50], process[50];
    int m, n;
    int i, j;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);

    printf("Enter sizes of %d memory blocks:\n", m);
    for(i = 0; i < m; i++)
        scanf("%d", &memory[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter sizes of %d processes:\n", n);
    for(i = 0; i < n; i++)
        scanf("%d", &process[i]);

    // ---------------- FIRST FIT ----------------
    printf("\n--- First Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    int blockFF[50];
    for(i = 0; i < m; i++)
        blockFF[i] = memory[i];

    for(i = 0; i < n; i++)
    {
        int allocated = 0;

        for(j = 0; j < m; j++)
        {
            if(blockFF[j] >= process[i])
            {
                printf("%d\t\t%d\t\t%d\n", i + 1, process[i], j + 1);
                blockFF[j] -= process[i];
                allocated = 1;
                break;
            }
        }

        if(!allocated)
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, process[i]);
    }

    // ---------------- BEST FIT ----------------
    printf("\n--- Best Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    int blockBF[50];
    for(i = 0; i < m; i++)
        blockBF[i] = memory[i];

    for(i = 0; i < n; i++)
    {
        int best = -1;

        for(j = 0; j < m; j++)
        {
            if(blockBF[j] >= process[i])
            {
                if(best == -1 || blockBF[j] < blockBF[best])
                    best = j;
            }
        }

        if(best != -1)
        {
            printf("%d\t\t%d\t\t%d\n", i + 1, process[i], best + 1);
            blockBF[best] -= process[i];
        }
        else
        {
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, process[i]);
        }
    }

    // ---------------- WORST FIT ----------------
    printf("\n--- Worst Fit ---\n");
    printf("Process No.\tProcess Size\tBlock No.\n");

    int blockWF[50];
    for(i = 0; i < m; i++)
        blockWF[i] = memory[i];

    for(i = 0; i < n; i++)
    {
        int worst = -1;

        for(j = 0; j < m; j++)
        {
            if(blockWF[j] >= process[i])
            {
                if(worst == -1 || blockWF[j] > blockWF[worst])
                    worst = j;
            }
        }

        if(worst != -1)
        {
            printf("%d\t\t%d\t\t%d\n", i + 1, process[i], worst + 1);
            blockWF[worst] -= process[i];
        }
        else
        {
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, process[i]);
        }
    }

    return 0;
}
