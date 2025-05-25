#include <stdio.h>
#include <stdlib.h>

struct Process {
    int id, AT, BT, TAT, WT, RT, CT;
};

void sorted(struct Process p[], int n) {
    int i, j;
    for (i = 1; i < n; i++) {
        for (j = 0; j < n - i; j++) { 
            if (p[j].AT > p[j + 1].AT || (p[j].AT == p[j + 1].AT && p[j].id > p[j + 1].id)) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}


void print_process_data(struct Process p[], int n) {
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].AT, p[i].BT, p[i].CT, p[i].TAT, p[i].WT);
    }

    int ttat = 0, twt = 0;
    for (int i = 0; i < n; i++) {
        ttat += p[i].TAT;
        twt += p[i].WT;
    }

    double avg_tat = (double)ttat / n;
    double avg_wt = (double)twt / n;

    printf("Average Turn-around time: %lf\n", avg_tat);
    printf("Average Waiting time: %lf\n", avg_wt);
}

void SJF(struct Process p[], int n) {
    int time = 0, completed = 0;
    int remainingBT[n];
    
   
    for (int i = 0; i < n; i++) {
        remainingBT[i] = p[i].BT;
    }

    
    while (completed < n) {
        int minBTindex = -1;
        int minBT = 999; 

        for (int i = 0; i < n; i++) {
            if (p[i].AT <= time && remainingBT[i] > 0 && remainingBT[i] < minBT) {
                minBT = remainingBT[i];
                minBTindex = i;
            }
        }

        if (minBTindex != -1) {
            remainingBT[minBTindex]--;
            time ++;
            if (remainingBT[minBTindex] == 0)
            {
                p[minBTindex].CT = time;
                p[minBTindex].TAT = p[minBTindex].CT - p[minBTindex].AT;
                p[minBTindex].WT = p[minBTindex].TAT - p[minBTindex].BT;
                completed++;
            }
        } else {
            time++; 
        }
    }
}

int main() {
    int n;
    printf("Enter Number of Processes: ");
    scanf("%d", &n);

    struct Process p[n];

    
    for (int i = 0; i < n; i++) {
        printf("Enter Process %d Arrival Time (AT) and Burst Time (BT): ", i + 1);
        p[i].id = i + 1; 
        scanf("%d %d", &p[i].AT, &p[i].BT);
    }

    sorted(p, n);  
    SJF(p, n);    
    print_process_data(p, n); 

    return 0;
}