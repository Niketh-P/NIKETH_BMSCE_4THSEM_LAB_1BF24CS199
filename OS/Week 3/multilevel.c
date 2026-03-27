#include <stdio.h>

#define MAX 100

typedef struct {
    int id;
    int at, bt, rt;
    int ct, wt, tat;
    int type; // 0 = system, 1 = user
} Process;

// Queue structure
typedef struct {
    int items[MAX];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(Queue *q) {
    return q->front == -1;
}

void enqueue(Queue *q, int value) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = value;
}

int dequeue(Queue *q) {
    if (isEmpty(q)) return -1;
    int val = q->items[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

int main() {
    int n, i, time = 0, completed = 0, index = 0;
    Process p[MAX], temp;

    Queue systemQ, userQ;
    initQueue(&systemQ);
    initQueue(&userQ);

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input
    for (i = 0; i < n; i++) {
        printf("\nProcess %d\n", i);
        p[i].id = i;

        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);

        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);

        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].rt = p[i].bt;
    }

    // Sort by arrival time (for scheduling only)
    for (i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].at > p[j].at) {
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int current = -1;

    while (completed < n) {

        // Add arrived processes to queues
        while (index < n && p[index].at <= time) {
            if (p[index].type == 0)
                enqueue(&systemQ, index);
            else
                enqueue(&userQ, index);
            index++;
        }

        // Preemption: system process interrupts user
        if (current != -1) {
            if (p[current].type == 1 && !isEmpty(&systemQ)) {
                enqueue(&userQ, current);
                current = -1;
            }
        }

        // Select next process
        if (current == -1) {
            if (!isEmpty(&systemQ))
                current = dequeue(&systemQ);
            else if (!isEmpty(&userQ))
                current = dequeue(&userQ);
            else {
                time++;
                continue;
            }
        }

        // Execute for 1 time unit
        p[current].rt--;
        time++;

        // Completion check
        if (p[current].rt == 0) {
            p[current].ct = time;
            p[current].tat = p[current].ct - p[current].at;
            p[current].wt = p[current].tat - p[current].bt;

            completed++;
            current = -1;
        }
    }

    // Print in ORIGINAL ID order
    float totalWT = 0, totalTAT = 0;

    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    for (int id = 0; id < n; id++) {
        for (i = 0; i < n; i++) {
            if (p[i].id == id) {
                printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
                       p[i].id,
                       (p[i].type == 0) ? "System" : "User",
                       p[i].at,
                       p[i].bt,
                       p[i].ct,
                       p[i].wt,
                       p[i].tat);

                totalWT += p[i].wt;
                totalTAT += p[i].tat;
            }
        }
    }

    printf("\nAverage Waiting Time: %.2f", totalWT / n);
    printf("\nAverage Turnaround Time: %.2f\n", totalTAT / n);

    return 0;
}
