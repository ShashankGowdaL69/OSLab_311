#include <stdio.h>

typedef struct Process{
    int id,AT,BT,CT,TAT,WT;
}Process;

void sorted(Process p[], int n) {
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

void print_process_data(Process p[], int n) {
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

void FCFS(Process p[], int n) {
    int time = 0;
    for (int i = 0; i < n; i++) {
        // Wait if the CPU is idle
        if (time < p[i].AT) {
            time = p[i].AT;
        }
        time += p[i].BT;
        p[i].CT = time;
        p[i].TAT = p[i].CT - p[i].AT;
        p[i].WT = p[i].TAT - p[i].BT;
    }
}


int main() {
    int n;
    printf("\nEnter number of processes: ");
    scanf("%d",&n);
    Process p[n];
    for(int i=0;i<n;i++){
        printf("\nProcess %d AT and BT : ",i+1);
        p[i].id=i+1;
        scanf("%d %d",&p[i].AT,&p[i].BT);
    }
    sorted(p,n);
    FCFS(p,n);
    print_process_data(p,n);
}
