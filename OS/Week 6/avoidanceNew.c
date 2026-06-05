#include <stdio.h>

#define MAX 10

int n, m;
int allocation[MAX][MAX];
int max[MAX][MAX];
int need[MAX][MAX];
int available[MAX];

void calculateNeed()
{
    int i, j;

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

int safety()
{
    int work[MAX];
    int finish[MAX];
    int safeSeq[MAX];

    int i, j, count = 0;

    for(i = 0; i < m; i++)
        work[i] = available[i];

    for(i = 0; i < n; i++)
        finish[i] = 0;

    while(count < n)
    {
        int found = 0;

        for(i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    for(j = 0; j < m; j++)
                        work[j] += allocation[i][j];

                    safeSeq[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if(found == 0)
            break;
    }

    if(count == n)
    {
        printf("\nSystem is in SAFE state.\n");
        printf("Safe Sequence: ");

        for(i = 0; i < n; i++)
        {
            printf("P%d", safeSeq[i]);

            if(i != n - 1)
                printf(" -> ");
        }

        printf("\n");
        return 1;
    }
    else
    {
        printf("\nSystem is NOT in a safe state.\n");
        return 0;
    }
}

void resourceRequest()
{
    int p;
    int request[MAX];
    int i;

    printf("\nEnter Process Number (0-%d): ", n - 1);
    scanf("%d", &p);

    printf("Enter Request Vector:\n");

    for(i = 0; i < m; i++)
    {
        printf("Request[%d] = ", i);
        scanf("%d", &request[i]);
    }

    /* Step 1: Request <= Need */
    for(i = 0; i < m; i++)
    {
        if(request[i] > need[p][i])
        {
            printf("\nError! Process exceeded its maximum claim.\n");
            return;
        }
    }

    /* Step 2: Request <= Available */
    for(i = 0; i < m; i++)
    {
        if(request[i] > available[i])
        {
            printf("\nResources not available. Process must wait.\n");
            return;
        }
    }

    /* Step 3: Pretend allocation */
    for(i = 0; i < m; i++)
    {
        available[i] -= request[i];
        allocation[p][i] += request[i];
        need[p][i] -= request[i];
    }

    printf("\nChecking system safety after allocation...\n");

    /* Step 4: Run Safety Algorithm */
    if(safety())
    {
        printf("Request GRANTED.\n");
    }
    else
    {
        /* Restore old state */
        for(i = 0; i < m; i++)
        {
            available[i] += request[i];
            allocation[p][i] -= request[i];
            need[p][i] += request[i];
        }

        printf("Request DENIED. System would become unsafe.\n");
    }
}

int main()
{
    int i, j, choice;

    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    printf("Enter Number of Resource Types: ");
    scanf("%d", &m);

    printf("\nEnter Allocation Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("\nEnter Max Matrix:\n");
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++)
        {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter Available Vector:\n");
    for(i = 0; i < m; i++)
    {
        scanf("%d", &available[i]);
    }

    calculateNeed();

    do
    {
        printf("\n");
        printf("=================================\n");
        printf("      BANKER'S ALGORITHM\n");
        printf("=================================\n");
        printf("1. Safety Algorithm\n");
        printf("2. Resource Request Algorithm\n");
        printf("3. Exit\n");
        printf("Enter Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                safety();
                break;

            case 2:
                resourceRequest();
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid Choice!\n");
        }

    } while(choice != 3);

    return 0;
}
