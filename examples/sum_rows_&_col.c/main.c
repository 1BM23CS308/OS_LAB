#include <stdio.h>

int main() {
    int a[10][10], m, n, i, j;

    printf("Enter number of rows and columns: ");
    scanf("%d%d", &m, &n);

    printf("Enter matrix elements:\n");
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &a[i][j]);

    for(i = 0; i < m; i++) {
        int rowSum = 0;
        for(j = 0; j < n; j++)
            rowSum += a[i][j];
        printf("Sum of row %d = %d\n", i + 1, rowSum);
    }

    for(j = 0; j < n; j++) {
        int colSum = 0;
        for(i = 0; i < m; i++)
            colSum += a[i][j];
        printf("Sum of column %d = %d\n", j + 1, colSum);
    }
    return 0;
}
