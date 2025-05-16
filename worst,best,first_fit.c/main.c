#include <stdio.h>

#define MAX_BLOCKS 10
#define MAX_PROCESSES 5

void allocateMemory(int blockSize[], int m, int processSize[], int n, int option) {
    int allocation[n];
    for (int i = 0; i < n; i++) allocation[i] = -1;

    for (int i = 0; i < n; i++) {
        int selectedIdx = -1;
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (option == 1 || (option == 2 && blockSize[j] < blockSize[selectedIdx]) || (option == 3 && blockSize[j] > blockSize[selectedIdx])) {
                    selectedIdx = j;
                }
            }
        }
        if (selectedIdx != -1) {
            allocation[i] = selectedIdx;
            blockSize[selectedIdx] -= processSize[i];
        }
    }

    const char *method = (option == 1) ? "First-fit" : (option == 2) ? "Best-fit" : "Worst-fit";
    printf("\n%s Memory Allocation\n", method);
    printf("Process No.\tProcess Size\tBlock No.\tBlock Size\n");
    for (int i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("%d\t\t%d\t\t%d\t\t%d\n", i + 1, processSize[i], allocation[i] + 1, blockSize[allocation[i]]);
        else
            printf("%d\t\t%d\t\tNot Allocated\n", i + 1, processSize[i]);
    }
}

int main() {
    int blockSize[MAX_BLOCKS] = {100, 500, 200, 300, 600};
    int processSize[MAX_PROCESSES] = {212, 417, 112, 426};
    int m = 5, n = 4;

    allocateMemory(blockSize, m, processSize, n, 1);
    allocateMemory(blockSize, m, processSize, n, 2);
    allocateMemory(blockSize, m, processSize, n, 3);
    return 0;
}

