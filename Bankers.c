#include <stdio.h>
#include <stdbool.h>

int main() {
    int n, m, i, j, k;

    // n = Number of processes, m = Number of resource types
    printf("Enter number of processes: ");
    scanf("%d", &n);
    printf("Enter number of resource types: ");
    scanf("%d", &m);

    int alloc[n][m], max[n][m], avail[m], need[n][m];

    printf("Enter Allocation Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max Matrix:\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);

    printf("Enter Available Resources:\n");
    for (i = 0; i < m; i++)
        scanf("%d", &avail[i]);

    // Calculating Need Matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Safety Algorithm
    int finish[n], safeSeq[n], ind = 0;
    for (k = 0; k < n; k++) {
        finish[k] = 0;
    }

    int work[m];
    for (i = 0; i < m; i++) {
        work[i] = avail[i];
    }

    for (k = 0; k < n; k++) {
        for (i = 0; i < n; i++) {
            if (finish[i] == 0) {
                int flag = 0;
                for (j = 0; j < m; j++) {
                    if (need[i][j] > work[j]) {
                        flag = 1;
                        break;
                    }
                }

                if (flag == 0) {
                    safeSeq[ind++] = i;
                    for (int y = 0; y < m; y++)
                        work[y] += alloc[i][y];
                    finish[i] = 1;
                }
            }
        }
    }

    // Check if all processes are finished
    bool deadlock = false;
    for(i = 0; i < n; i++) {
        if(finish[i] == 0) {
            deadlock = true;
            break;
        }
    }

    if (deadlock) {
        printf("\nSystem is in DEADLOCK. The above sequence is not possible.\n");
    } else {
        printf("\nSystem is in a SAFE STATE.\nSafe Sequence: ");
        for (i = 0; i < n - 1; i++)
            printf(" P%d ->", safeSeq[i]);
        printf(" P%d\n", safeSeq[n - 1]);
    }

    return 0;
}
