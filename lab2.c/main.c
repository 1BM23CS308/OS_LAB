#include <stdio.h>

typedef struct {
    int pid, at, bt, wt, tat, type;
} P;

void fcfs(P p[], int n) {
    int t = 0;
    for(int i=0; i<n; i++) {
        if(p[i].at > t) t = p[i].at;
        p[i].wt = t - p[i].at;
        t += p[i].bt;
        p[i].tat = p[i].wt + p[i].bt;
    }
}

int main() {
    int n, sys=0, usr=0;
    printf("No. of processes: "); scanf("%d", &n);
    P s[n], u[n], temp;

    for(int i=0; i<n; i++) {
        printf("P%d: arrival burst type(1=system,2=user): ", i+1);
        scanf("%d%d%d", &temp.at, &temp.bt, &temp.type);
        temp.pid = i+1;
        if(temp.type == 1) s[sys++] = temp;
        else u[usr++] = temp;
    }

    fcfs(s, sys);
    fcfs(u, usr);

    printf("\nPID Type Arrival Burst Waiting Turnaround\n");
    for(int i=0; i<sys; i++)
        printf("%d System %d %d %d %d\n", s[i].pid, s[i].at, s[i].bt, s[i].wt, s[i].tat);
    for(int i=0; i<usr; i++)
        printf("%d User %d %d %d %d\n", u[i].pid, u[i].at, u[i].bt, u[i].wt, u[i].tat);

    return 0;
}
