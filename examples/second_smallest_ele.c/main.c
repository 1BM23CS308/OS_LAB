#include <stdio.h>
#include <limits.h>

int main() {
    int a[100], n, i;
    int smallest = INT_MAX, secondSmallest = INT_MAX;

    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter elements:\n");
    for(i = 0; i < n; i++)
        scanf("%d", &a[i]);

    for(i = 0; i < n; i++) {
        if(a[i] < smallest) {
            secondSmallest = smallest;
            smallest = a[i];
        } else if(a[i] < secondSmallest && a[i] != smallest) {
            secondSmallest = a[i];
        }
    }

    if(secondSmallest == INT_MAX)
        printf("No second smallest element.\n");
    else
        printf("Second smallest element is %d\n", secondSmallest);
    return 0;
}
