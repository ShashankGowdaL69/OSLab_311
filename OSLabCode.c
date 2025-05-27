#include <stdio.h>

int main() {
    int n, i, j;
    int pid[20], bt[20], at[20], wt[20], tat[20], ct[20];
    int completed = 0, t = 0, min, index;
    int done[20] = {0};

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        pid[i] = i + 1;
        printf("Enter arrival time for P%d: ", pid[i]);
        scanf("%d", &at[i]);
        printf("Enter burst time for P%d: ", pid[i]);
        scanf("%d", &bt[i]);
    }

    printf("\nGantt Chart:\n|");
    while(completed < n) {
        min = 9999;
        index = -1;
        for(i = 0; i < n; i++) {
            if(at[i] <= t && done[i] == 0 && bt[i] < min) {
                min = bt[i];
                index = i;
            }
        }
        if(index != -1) {
            wt[index] = t - at[index];
            t += bt[index];
            tat[index] = wt[index] + bt[index];
            ct[index] = t;
            done[index] = 1;
            completed++;
            printf(" P%d |", pid[index]);
        } else {
            t++;
        }
    }

    printf("\n0");
    for(i = 0; i < n; i++) {
        if(ct[i] != 0) {
            printf("   %d", ct[i]);
        }
    }

    printf("\n\nProcess\tAT\tBT\tWT\tTAT\tCT\n");
    for(i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], wt[i], tat[i], ct[i]);
    }

    return 0;
}
