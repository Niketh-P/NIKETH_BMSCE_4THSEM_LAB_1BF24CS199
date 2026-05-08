#include <stdio.h>

#define MAX 10

int main() {
    int n, m, i, j, k, choice;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    int alloc[MAX][MAX], max[MAX][MAX], need[MAX][MAX];
    int request[MAX][MAX], avail[MAX];
    int finish[MAX], safe[MAX];

    // Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++)
            scanf("%d",&alloc[i][j]);

    // Max Matrix
    printf("\nEnter Max Matrix:\n");
    for(i=0;i<n;i++)
        for(j=0;j<m;j++) {
            scanf("%d",&max[i][j]);
            need[i][j] = max[i][j] - alloc[i][j];
        }

    printf("\nEnter Available Resources:\n");
    for(i=0;i<m;i++)
        scanf("%d",&avail[i]);

    // Menu
    printf("\n1. Safety Algorithm");
    printf("\n2. Deadlock Detection");
    printf("\nEnter choice: ");
    scanf("%d",&choice);

    // ================= SAFETY ALGORITHM =================
    if(choice == 1) {

        for(i=0;i<n;i++)
            finish[i] = 0;

        int count = 0;

        while(count < n) {
            int found = 0;

            for(i=0;i<n;i++) {

                if(!finish[i]) {

                    for(j=0;j<m;j++)
                        if(need[i][j] > avail[j])
                            break;

                    if(j == m) {

                        for(k=0;k<m;k++)
                            avail[k] += alloc[i][k];

                        safe[count++] = i;
                        finish[i] = 1;
                        found = 1;
                    }
                }
            }

            if(!found) {
                printf("\nSystem is NOT Safe\n");
                return 0;
            }
        }

        printf("\nSystem is SAFE\nSafe Sequence: ");

        for(i=0;i<n;i++)
            printf("P%d ", safe[i]);
    }

    // ================= DEADLOCK DETECTION =================
    else if(choice == 2) {

        printf("\nEnter Request Matrix:\n");

        for(i=0;i<n;i++)
            for(j=0;j<m;j++)
                scanf("%d",&request[i][j]);

        for(i=0;i<n;i++) {
            finish[i] = 1;

            for(j=0;j<m;j++)
                if(alloc[i][j] != 0)
                    finish[i] = 0;
        }

        int found;

        do {
            found = 0;

            for(i=0;i<n;i++) {

                if(!finish[i]) {

                    for(j=0;j<m;j++)
                        if(request[i][j] > avail[j])
                            break;

                    if(j == m) {

                        for(k=0;k<m;k++)
                            avail[k] += alloc[i][k];

                        finish[i] = 1;
                        found = 1;
                    }
                }
            }

        } while(found);

        found = 0;

        printf("\nProcesses in Deadlock:\n");

        for(i=0;i<n;i++) {
            if(!finish[i]) {
                printf("P%d ", i);
                found = 1;
            }
        }

        if(!found)
            printf("No Deadlock Detected");
    }

    else
        printf("\nInvalid Choice");

    return 0;
}
