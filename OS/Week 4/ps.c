#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int tickets;
    int execution_count; // Tracks how many times it won
} Task;

int main() {
    Task tasks[MAX_TASKS];
    int num_tasks, total_draws;
    int total_tickets = 0;

    srand(time(NULL)); // Seed random number generator

    printf("--- Proportional Share (Lottery) Scheduling ---\n");
    printf("Enter number of tasks (max %d): ", MAX_TASKS);
    scanf("%d", &num_tasks);

    for (int i = 0; i < num_tasks; i++) {
        tasks[i].id = i + 1;
        printf("Enter number of lottery tickets for Task %d: ", tasks[i].id);
        scanf("%d", &tasks[i].tickets);
        tasks[i].execution_count = 0;
        total_tickets += tasks[i].tickets;
    }

    printf("Enter number of lottery draws to simulate: ");
    scanf("%d", &total_draws);

    printf("\nRunning %d lottery draws with a pool of %d tickets...\n\n", total_draws, total_tickets);

    // Simulate the draws
    for (int d = 0; d < total_draws; d++) {
        int winning_ticket = rand() % total_tickets;
        int ticket_counter = 0;

        for (int i = 0; i < num_tasks; i++) {
            ticket_counter += tasks[i].tickets;
            if (winning_ticket < ticket_counter) {
                tasks[i].execution_count++;
                break; // Task won, move to next draw
            }
        }
    }

    // Output final distribution
    printf("--- Final CPU Time Allocation Results ---\n");
    for (int i = 0; i < num_tasks; i++) {
        double percentage = ((double)tasks[i].execution_count / total_draws) * 100.0;
        printf("Task %d:\n", tasks[i].id);
        printf("  - Tickets Held: %d (Target: %.2f%%)\n", tasks[i].tickets, ((double)tasks[i].tickets / total_tickets) * 100.0);
        printf("  - Times Executed: %d (Actual: %.2f%%)\n", tasks[i].execution_count, percentage);
    }

    return 0;
}
