#include <stdio.h>
#include <stdlib.h>

#define MAX_TASKS 10

typedef struct {
    int id;
    int CT;             // Computation Time
    int RT;             // Remaining Time
    int period;         // Period (defines priority)
    int next_release;   // Next release time
    int deadline;       // Relative deadline
} Task;

// Sort tasks by shortest period (RMS priority)
void sort_by_priority(Task tasks[], int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n - i; j++) {
            if (tasks[j].period > tasks[j + 1].period || 
                (tasks[j].period == tasks[j + 1].period && tasks[j].id > tasks[j + 1].id)) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }
}

void RMS(Task tasks[], int n, int totaltime) {
    for (int t = 0; t < totaltime; t++) {
        // Release new instances of tasks if needed
        for (int i = 0; i < n; i++) {
            if (t == tasks[i].next_release) {
                if (tasks[i].RT > 0) {
                    printf("Time %d: Task %d missed deadline!\n", t, tasks[i].id);
                }
                tasks[i].RT = tasks[i].CT;
                tasks[i].next_release += tasks[i].period;
                printf("Time %d: Task %d released (Next release at %d)\n", t, tasks[i].id, tasks[i].next_release);
            }
        }

        // Sort tasks by priority (shortest period first)
        sort_by_priority(tasks, n);

        // Execute the highest-priority ready task
        int executed = 0;
        for (int i = 0; i < n; i++) {
            if (tasks[i].RT > 0) {
                printf("Time %d: Executing Task %d\n", t, tasks[i].id);
                tasks[i].RT--;
                executed = 1;

                if (tasks[i].RT == 0) {
                    printf("Time %d: Task %d completed\n", t + 1, tasks[i].id);
                }
                break;
            }
        }

        if (!executed) {
            printf("Time %d: CPU Idle\n", t);
        }
    }
}

int main() {
    // Define periodic tasks: {id, CT, RT, period, next_release, deadline}
    Task tasks[MAX_TASKS] = {
        {1, 2, 0, 5, 0, 5},  // Task 1: CT=2, Period=5
        {2, 1, 0, 3, 0, 3},  // Task 2: CT=1, Period=3
        {3, 1, 0, 7, 0, 7}   // Task 3: CT=1, Period=7
    };

    int numTasks = 3;
    int totalTime = 20;

    RMS(tasks, numTasks, totalTime);

    return 0;
}
