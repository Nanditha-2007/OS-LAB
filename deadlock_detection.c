#include <stdio.h>

int main() {
    int n, m, i, j, k;

    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], request[n][m], avail[m], finish[n];

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("\nEnter Request Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &request[i][j]);

    printf("\nEnter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Step 1: Initialize Finish array
    // If a process has 0 allocation in all resources, it's considered finished
    for (i = 0; i < n; i++) {
        int count = 0;
        for (j = 0; j < m; j++) {
            if (alloc[i][j] == 0) count++;
        }
        if (count == m) finish[i] = 1;
        else finish[i] = 0;
    }

    // Step 2: Detection Algorithm
    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int can_proceed = 1;
                for (j = 0; j < m; j++) {
                    if (request[i][j] > avail[j]) {
                        can_proceed = 0;
                        break;
                    }
                }

                if (can_proceed) {
                    for (j = 0; j < m; j++)
                        avail[j] += alloc[i][j];
                    finish[i] = 1;
                }
            }
        }
    }

    // Step 3: Check for unfinished processes
    int deadlocked[n], d_count = 0;
    for (i = 0; i < n; i++) {
        if (finish[i] == 0) {
            deadlocked[d_count++] = i;
        }
    }

    if (d_count > 0) {
        printf("\nSystem is in DEADLOCK!\nDeadlocked processes: ");
        for (i = 0; i < d_count; i++)
            printf("P%d ", deadlocked[i]);
        printf("\n");
    } else {
        printf("\nNo Deadlock Detected. System is safe.\n");
    }

    return 0;
}
