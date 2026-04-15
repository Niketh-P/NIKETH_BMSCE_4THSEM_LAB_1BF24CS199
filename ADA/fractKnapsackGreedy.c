#include <stdio.h>
#include <stdlib.h>

// Structure to represent an item in the set S
typedef struct {
    int id;         // Item identifier
    double b;       // Benefit (b_i)
    double w;       // Weight (w_i)
    double v;       // Value per unit weight (v_i = b_i / w_i)
    double x;       // Amount of weight taken (x_i)
} Item;

// Comparator function to sort items by v_i in descending order
int compare(const void *a, const void *b) {
    Item *item1 = (Item *)a;
    Item *item2 = (Item *)b;
    // Sort descending
    if (item1->v < item2->v) return 1;
    else if (item1->v > item2->v) return -1;
    else return 0;
}

// Function to implement the fractional knapsack algorithm
void fractionalKnapsack(Item items[], int n, double W) {
    double w = 0.0;             // Total weight currently in knapsack (w)
    double total_benefit = 0.0; // Total benefit achieved

    // Step 1: Initialize x_i = 0 and calculate v_i = b_i / w_i
    for (int i = 0; i < n; i++) {
        items[i].x = 0.0;
        items[i].v = items[i].b / items[i].w;
    }

    // Step 2: Sort items descending by v_i
    // (This mimics repeatedly removing the item with the highest v_i)
    qsort(items, n, sizeof(Item), compare);

    // Step 3: while w < W
    for (int i = 0; i < n; i++) {
        if (w < W) {
            // x_i <- min{w_i, W - w}
            double remaining_capacity = W - w;
            if (items[i].w <= remaining_capacity) {
                items[i].x = items[i].w; // Take the whole item
            } else {
                items[i].x = remaining_capacity; // Take a fraction of the item
            }

            // w <- w + x_i
            w += items[i].x;

            // Calculate the benefit gained from the amount x_i taken
            total_benefit += items[i].x * items[i].v;
        } else {
            break; // The knapsack is completely full
        }
    }

    // --- Output the Results ---
    printf("\nMaximum benefit achievable: %.2f\n", total_benefit);
    printf("Distribution of items taken:\n");
    printf("--------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        if (items[i].x > 0) {
            printf("Item %d: taken %.2f weight units out of %.2f (Benefit added: %.2f)\n",
                   items[i].id, items[i].x, items[i].w, items[i].x * items[i].v);
        }
    }
}

int main() {
    int n;
    double max_W;

    // Get the number of items
    printf("Enter the number of items: ");
    scanf("%d", &n);

    // Get the maximum capacity of the knapsack
    printf("Enter the maximum knapsack capacity (W): ");
    scanf("%lf", &max_W);

    // Dynamically allocate memory for the items based on user input n
    Item *items = (Item *)malloc(n * sizeof(Item));
    if (items == NULL) {
        printf("Memory allocation failed!\n");
        return 1;
    }

    // Get the benefit and weight for each item
    for (int i = 0; i < n; i++) {
        items[i].id = i + 1; // Assign an ID from 1 to n
        printf("Enter benefit and weight for Item %d (separated by space): ", i + 1);
        scanf("%lf %lf", &items[i].b, &items[i].w);

        // Initialize placeholders
        items[i].v = 0.0;
        items[i].x = 0.0;
    }

    printf("\nTotal Knapsack Capacity (W): %.2f\n", max_W);

    // Call the algorithm
    fractionalKnapsack(items, n, max_W);

    // Free the dynamically allocated memory
    free(items);

    return 0;
}
