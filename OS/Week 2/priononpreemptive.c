#include <stdio.h>

int main()
{
    int n, i, j, time = 0, completed = 0;
    int at[20], bt[20], pri[20];
    int ct[20], tat[20], wt[20], rt[20];
    int visited[20];
    int highest;

    float avg_wt = 0, avg_tat = 0, avg_rt = 0;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++)
    {
        printf("\nProcess P%d\n", i+1);

        printf("Arrival Time: ");
        scanf("%d", &at[i]);

        printf("Burst Time: ");
        scanf("%d", &bt[i]);

        printf("Priority (lower number = higher priority): ");
        scanf("%d", &pri[i]);

        visited[i] = 0;
    }

    while(completed < n)
    {
        highest = -1;

        for(i = 0; i < n; i++)
        {
            if(at[i] <= time && visited[i] == 0)
            {
                if(highest == -1 || pri[i] < pri[highest])
                {
                    highest = i;
                }
            }
        }

        if(highest == -1)
        {
            time++;
            continue;
        }

        rt[highest] = time - at[highest];
        time += bt[highest];

        ct[highest] = time;
        tat[highest] = ct[highest] - at[highest];
        wt[highest] = tat[highest] - bt[highest];

        avg_wt += wt[highest];
        avg_tat += tat[highest];
        avg_rt += rt[highest];

        visited[highest] = 1;
        completed++;
    }

    printf("\nProcess\tAT\tBT\tPri\tCT\tTAT\tWT\tRT\n");

    for(i = 0; i < n; i++)
    {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               i+1, at[i], bt[i], pri[i],
               ct[i], tat[i], wt[i], rt[i]);
    }

    printf("\nAverage Waiting Time = %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time = %.2f", avg_tat/n);
    printf("\nAverage Response Time = %.2f\n", avg_rt/n);

    return 0;
}
