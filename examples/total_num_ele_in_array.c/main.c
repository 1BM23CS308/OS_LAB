#include <stdio.h>

int main() {
    int a[100], n, i, j, count = 0;
    int visited[100] = {0};

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for(i = 0; i < n; i++) {
        if(visited[i]) continue;
        int freq = 1;
        for(j = i + 1; j < n; j++) {
            if(a[i] == a[j]) {
                freq++;
                visited[j] = 1;
            }
        }
        if(freq > 1)
            count++;
    }

    printf("Total number of duplicate elements = %d\n", count);
    return 0;
}
