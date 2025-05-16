#include <stdio.h>
#include <stdlib.h>

#define N 10
#define T 30

typedef struct {
    int id, et, p, d, rt, nt, w;
} Task;

void reset(Task t[], int n) {
    for (int i = 0; i < n; i++) t[i].rt = t[i].nt = 0;
}

int main() {
    Task t[N];
    int n;
    printf("Tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        t[i].id = i + 1;
        printf("T%d ET P W: ", t[i].id);
        scanf("%d%d%d", &t[i].et, &t[i].p, &t[i].w);
        t[i].d = t[i].p;
    }

    printf("\n-- RMS --\n");
    reset(t, n);
    for (int time = 0; time < T; time++) {
        for (int i = 0; i < n; i++)
            if (time >= t[i].nt && t[i].rt == 0) t[i].rt = t[i].et;

        int sel = -1;
        for (int i = 0; i < n; i++)
            if (t[i].rt > 0 && (sel == -1 || t[i].p < t[sel].p))
                sel = i;

        if (sel != -1) {
            printf("T%2d: T%d\n", time, t[sel].id);
            t[sel].rt--;
            if (t[sel].rt == 0) t[sel].nt += t[sel].p;
        } else printf("T%2d: Idle\n", time);
    }


    printf("\n-- EDF --\n");
    reset(t, n);
    for (int time = 0; time < T; time++) {
        for (int i = 0; i < n; i++)
            if (time >= t[i].nt && t[i].rt == 0) {
                t[i].rt = t[i].et;
                t[i].d = time + t[i].p;
            }

        int sel = -1;
        for (int i = 0; i < n; i++)
            if (t[i].rt > 0 && (sel == -1 || t[i].d < t[sel].d))
                sel = i;

        if (sel != -1) {
            printf("T%2d: T%d\n", time, t[sel].id);
            t[sel].rt--;
            if (t[sel].rt == 0) t[sel].nt += t[sel].p;
        } else printf("T%2d: Idle\n", time);
    }

    printf("\n-- PS --\n");
    reset(t, n);
    int q[N];
    for (int time = 0; time < T; time++) {
        for (int i = 0; i < n; i++)
            if (time >= t[i].nt && t[i].rt == 0) {
                t[i].rt = t[i].et;
                q[i] = t[i].w;
            }

        int sel = -1;
        for (int i = 0; i < n; i++)
            if (t[i].rt > 0 && q[i] > 0) {
                sel = i;
                break;
            }

        if (sel != -1) {
            printf("T%2d: T%d\n", time, t[sel].id);
            t[sel].rt--; q[sel]--;
            if (t[sel].rt == 0) t[sel].nt += t[sel].p;
        } else printf("T%2d: Idle\n", time);
    }

    return 0;
}
