#include <stdio.h>

int main() {
    int n, i, done = 0;
    int bt[10], wt[10], rt[10];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for(i = 0; i < n; i++) {
        printf("Enter burst time and weight for P%d: ", i+1);
        scanf("%d %d", &bt[i], &wt[i]);
        rt[i] = bt[i];
    }

    printf("\nExecution Order:\n");

    while(done < n) {
        for(i = 0; i < n; i++) {
            if(rt[i] > 0) {
                int slice = wt[i];

                if(rt[i] < slice)
                    slice = rt[i];

                printf("P%d ", i+1);

                rt[i] -= slice;

                if(rt[i] == 0)
                    done++;
            }
        }
    }

    return 0;
}
