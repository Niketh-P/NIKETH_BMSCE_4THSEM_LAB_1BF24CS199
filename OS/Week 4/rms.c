#include <stdio.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int period;      
    int burst_time;
    int remaining_time;
} Task;

int main() {
    Task tasks[MAX_TASKS];
    int num_tasks, sim_time;

    printf("--- Rate-Monotonic Scheduling (RMS) Simulation ---\n");
    printf("Enter number of tasks (max %d): ", MAX_TASKS);
    scanf("%d", &num_tasks);

    for (int i = 0; i < num_tasks; i++) {
        tasks[i].id = i + 1;
        printf("Enter Period and CPU Burst for Task %d: ", tasks[i].id);
        scanf("%d %d", &tasks[i].period, &tasks[i].burst_time);
        tasks[i].remaining_time = 0; // Starts at 0, refreshed at arrival
    }

    printf("Enter total simulation time: ");
    scanf("%d", &sim_time);

    printf("\n--- Execution Timeline ---\n");
    int current_task = -1;

    for (int time = 0; time < sim_time; time++) {
        // 1. Check for new arrivals (start of a new period)
        for (int i = 0; i < num_tasks; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].burst_time;
            }
        }

        // 2. Find the highest priority ready task (shortest period)
        int selected_task = -1;
        int shortest_period = 999999;

        for (int i = 0; i < num_tasks; i++) {
            if (tasks[i].remaining_time > 0 && tasks[i].period < shortest_period) {
                shortest_period = tasks[i].period;
                selected_task = i;
            }
        }

        // 3. Execute the task
        if (selected_task != -1) {
            if (current_task != selected_task) {
                printf("[Time %3d] CPU switched to Task %d\n", time, tasks[selected_task].id);
                current_task = selected_task;
            }
            tasks[selected_task].remaining_time--;
        } else {
            if (current_task != -1) {
                printf("[Time %3d] CPU is IDLE\n", time);
                current_task = -1;
            }
        }
    }
    printf("[Time %3d] Simulation Ended.\n", sim_time);

    return 0;
}
