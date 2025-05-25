#include <stdio.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int weight;       // Share of CPU time
    int remaining_share; // Remaining share for current round
    int total_executed;
} Task;

int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

// Calculate LCM of weights to determine a scheduling round
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

void proportional_schedule(Task tasks[], int n, int total_time) {
    // Calculate LCM of all task weights to determine one scheduling cycle
    int round = tasks[0].weight;
    for (int i = 1; i < n; i++) {
        round = lcm(round, tasks[i].weight);
    }

    // Calculate how many times each task should run per round
    for (int i = 0; i < n; i++) {
        tasks[i].remaining_share = (round / tasks[i].weight);
        tasks[i].total_executed = 0;
    }

    printf("Proportional Scheduling (Total Time = %d):\n", total_time);
    for (int t = 0; t < total_time; t++) {
        int executed = 0;

        // Search for task with remaining share to execute
        for (int i = 0; i < n; i++) {
            if (tasks[i].remaining_share > 0) {
                printf("Time %d: Executing Task %d\n", t, tasks[i].id);
                tasks[i].remaining_share--;
                tasks[i].total_executed++;
                executed = 1;
                break;
            }
        }

        // If all shares are used, reset for the next round
        if (!executed) {
            for (int i = 0; i < n; i++) {
                tasks[i].remaining_share = (round / tasks[i].weight);
            }
            t--; // Retry same time step
        }
    }

    // Summary
    printf("\nExecution Summary:\n");
    for (int i = 0; i < n; i++) {
        printf("Task %d executed %d times\n", tasks[i].id, tasks[i].total_executed);
    }
}

int main() {
    Task tasks[MAX_TASKS] = {
        {1, 1, 0, 0},  // Task 1: weight 1
        {2, 2, 0, 0},  // Task 2: weight 2
        {3, 1, 0, 0}   // Task 3: weight 1
    };

    int num_tasks = 3;
    int total_time = 20;

    proportional_schedule(tasks, num_tasks, total_time);

    return 0;
}
