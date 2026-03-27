#include <stdio.h>
#define MAX 100

typedef struct{
    int pid;
    int arrival;
    int burst;
    int remaining;
    int completion;
    int waiting;
    int turnaround;
} Process;

int main(){
    int n, tq;
    Process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for(int i = 0; i < n; i++){
        printf("\nProcess %d\n", i + 1);

        printf("PID: ");
        scanf("%d", &p[i].pid);

        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival);

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        p[i].remaining = p[i].burst; // initialize
    }

    printf("\nEnter Time Quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    int queue[MAX], front = 0, rear = 0;
    int visited[MAX] = {0};

    // Push first arriving process
    for(int i = 0; i < n; i++){
        if(p[i].arrival <= time){
            queue[rear++] = i;
            visited[i] = 1;
        }
    }

    while(completed < n){
        if(front == rear){
            time++;
            for(int i = 0; i < n; i++){
                if(p[i].arrival <= time && !visited[i]){
                    queue[rear++] = i;
                    visited[i] = 1;
                }
            }
            continue;
        }

        int idx = queue[front++];

        int exec_time = (p[idx].remaining > tq) ? tq : p[idx].remaining;

        p[idx].remaining -= exec_time;
        time += exec_time;

        // Add newly arrived processes
        for(int i = 0; i < n; i++){
            if(p[i].arrival <= time && !visited[i]){
                queue[rear++] = i;
                visited[i] = 1;
            }
        }

        if(p[idx].remaining > 0){
            queue[rear++] = idx; // reinsert
        } else {
            p[idx].completion = time;
            p[idx].turnaround = p[idx].completion - p[idx].arrival;
            p[idx].waiting = p[idx].turnaround - p[idx].burst;

            printf("Process %d completed at time %d\n", p[idx].pid, time);
            completed++;
        }
    }

    // Output
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].arrival,
               p[i].burst,
               p[i].completion,
               p[i].turnaround,
               p[i].waiting);
    }

    return 0;
}
