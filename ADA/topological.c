#include <stdio.h>

#define MAX 20

int queue[MAX], front = -1, rear = -1;

void enqueue(int item)
{
    if(rear == MAX - 1)
        return;

    if(front == -1)
        front = 0;

    queue[++rear] = item;
}

int dequeue()
{
    if(front == -1 || front > rear)
        return -1;

    return queue[front++];
}

int main()
{
    int n, i, j;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    int graph[MAX][MAX];
    int indegree[MAX] = {0};

    printf("Enter adjacency matrix:\n");

    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);

            if(graph[i][j] == 1)
                indegree[j]++;
        }
    }

    // Insert vertices with indegree 0 into queue
    for(i = 0; i < n; i++)
    {
        if(indegree[i] == 0)
            enqueue(i);
    }

    printf("Topological Order:\n");

    while(front <= rear)
    {
        int u = dequeue();

        printf("%d ", u);

        for(j = 0; j < n; j++)
        {
            if(graph[u][j] == 1)
            {
                indegree[j]--;

                if(indegree[j] == 0)
                    enqueue(j);
            }
        }
    }

    return 0;
}
