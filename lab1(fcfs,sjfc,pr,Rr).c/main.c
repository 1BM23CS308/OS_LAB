#include <stdio.h>

struct Process {
    int id, at, bt, ct, tat, wt, pt, rt, done;
};

void calculateTimes(struct Process p[], int n) {
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
    }
}

void printTable(struct Process p[], int n) {
    float totalTAT = 0, totalWT = 0;
    printf("\nPID  AT  BT  CT  TAT  WT\n");
    for (int i = 0; i < n; i++) {
        totalTAT += p[i].tat;
        totalWT += p[i].wt;
        printf("%3d  %2d  %2d  %2d   %2d   %2d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    printf("Average TAT = %.2f\n", totalTAT / n);
    printf("Average WT  = %.2f\n", totalWT / n);
}

void fcfs(struct Process p[], int n) {
    printf("\n--- FCFS Scheduling ---\n");
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (p[i].at > p[j].at) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }

    int time = 0;
    for (int i = 0; i < n; i++) {
        if (time < p[i].at)
            time = p[i].at;
        time += p[i].bt;
        p[i].ct = time;
    }

    calculateTimes(p, n);
    printTable(p, n);
}

void sjf(struct Process p[], int n) {
    printf("\n--- SJF (Non-Preemptive) ---\n");
    int time = 0, done = 0;

    while (done < n) {
        int idx = -1, minBT = 1e9;
        for (int i = 0; i < n; i++)
            if (!p[i].done && p[i].at <= time && p[i].bt < minBT) {
                minBT = p[i].bt;
                idx = i;
            }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].done = 1;
        done++;
    }

    calculateTimes(p, n);
    printTable(p, n);
}

void priority(struct Process p[], int n) {
    printf("\n--- Priority Scheduling (Non-Preemptive) ---\n");
    int time = 0, done = 0;

    while (done < n) {
        int idx = -1, minPrio = 1e9;
        for (int i = 0; i < n; i++)
            if (!p[i].done && p[i].at <= time && p[i].pt < minPrio) {
                minPrio = p[i].pt;
                idx = i;
            }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].bt;
        p[idx].ct = time;
        p[idx].done = 1;
        done++;
    }

    calculateTimes(p, n);
    printTable(p, n);
}

void roundRobin(struct Process p[], int n, int q) {
    printf("\n--- Round Robin (Time Quantum = %d) ---\n", q);
    int time = 0, done = 0;
    for (int i = 0; i < n; i++) {
        p[i].rt = p[i].bt;
        p[i].done = 0;
    }

    while (done < n) {
        int flag = 0;
        for (int i = 0; i < n; i++) {
            if (p[i].rt > 0 && p[i].at <= time) {
                flag = 1;
                if (p[i].rt > q) {
                    time += q;
                    p[i].rt -= q;
                } else {
                    time += p[i].rt;
                    p[i].ct = time;
                    p[i].rt = 0;
                    p[i].done = 1;
                    done++;
                }
            }
        }
        if (!flag) time++;
    }

    calculateTimes(p, n);
    printTable(p, n);
}

void reset(struct Process p[], struct Process backup[], int n) {
    for (int i = 0; i < n; i++) {
        p[i] = backup[i];
        p[i].done = 0;
    }
}

int main() {
    int n, q;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n], backup[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("Process %d:\n", p[i].id);
        printf("  Arrival Time: "); scanf("%d", &p[i].at);
        printf("  Burst Time  : "); scanf("%d", &p[i].bt);
        printf("  Priority    : "); scanf("%d", &p[i].pt);
        p[i].done = 0;
        backup[i] = p[i];  // Backup for reuse
    }

    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d", &q);

    fcfs(p, n);
    reset(p, backup, n);

    sjf(p, n);
    reset(p, backup, n);

    priority(p, n);
    reset(p, backup, n);

    roundRobin(p, n, q);

    return 0;
}
