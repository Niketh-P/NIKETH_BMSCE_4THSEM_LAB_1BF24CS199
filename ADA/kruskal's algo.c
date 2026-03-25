#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX 20

struct Edge {
    int src, dest, weight;
};

struct subset {
    int parent, rank;
};

int find(struct subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

void Union(struct subset subsets[], int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
        subsets[rootX].parent = rootY;
    else if (subsets[rootX].rank > subsets[rootY].rank)
        subsets[rootY].parent = rootX;
    else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

int compare(const void* a, const void* b) {
    return ((struct Edge*)a)->weight - ((struct Edge*)b)->weight;
}

void kruskalMST(struct Edge edges[], int V, int E) {
    struct Edge result[MAX];
    int e = 0;

    qsort(edges, E, sizeof(edges[0]), compare);

    struct subset subsets[MAX];
    for (int i = 0; i < V; i++) {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    int i = 0;
    while (e < V - 1 && i < E) {
        struct Edge next = edges[i++];

        int x = find(subsets, next.src);
        int y = find(subsets, next.dest);

        if (x != y) {
            result[e++] = next;
            Union(subsets, x, y);
        }
    }

    int total = 0;
    printf("\nMST using Kruskal:\n");
    for (i = 0; i < e; i++) {
        printf("%d - %d = %d\n", result[i].src, result[i].dest, result[i].weight);
        total += result[i].weight;
    }
    printf("Total cost = %d\n", total);
}

int main() {
    int V, E;
    struct Edge edges[MAX];
    clock_t start, end;

    printf("Enter vertices: ");
    scanf("%d", &V);

    printf("Enter edges: ");
    scanf("%d", &E);

    printf("Enter edges (src dest weight):\n");
    for (int i = 0; i < E; i++) {
        scanf("%d %d %d",    &edges[i].src, &edges[i].dest, &edges[i].weight);
    }

    start = clock();
    kruskalMST(edges, V, E);
    end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", time_taken);

    return 0;
}
