#include <stdio.h>

// Function to find GCD
int gcd(int a, int b) {
    while(b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find LCM
int lcm(int a, int b) {
    return (a * b) / gcd(a, b);
}

int main() {
    int n;
    int burst[10], period[10], deadline[10];
    int remaining[10], next_arrival[10];
    int time_limit;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nTask %d\n", i + 1);

        printf("Burst Time: ");
        scanf("%d", &burst[i]);

        printf("Deadline: ");
        scanf("%d", &deadline[i]);

        printf("Period: ");
        scanf("%d", &period[i]);

        remaining[i] = burst[i];
        next_arrival[i] = 0;
    }

    // 🔥 Calculate LCM of all periods
    time_limit = period[0];
    for (int i = 1; i < n; i++) {
        time_limit = lcm(time_limit, period[i]);
    }

    printf("\nSimulation Time (LCM) = %d\n", time_limit);
    printf("\n--- Earliest Deadline First ---\n");

    for (int t = 0; t < time_limit; t++) {
        int selected = -1;

        for (int i = 0; i < n; i++) {
            if (t >= next_arrival[i] && remaining[i] > 0) {
                if (selected == -1 || deadline[i] < deadline[selected]) {
                    selected = i;
                }
            }
        }

        if (selected != -1) {
            printf("Time %d: Task %d\n", t, selected + 1);
            remaining[selected]--;

            if (remaining[selected] == 0) {
                next_arrival[selected] += period[selected];

                // ✔ Correct absolute deadline update
                deadline[selected] = next_arrival[selected] + period[selected];

                remaining[selected] = burst[selected];
            }
        } else {
            printf("Time %d: Idle\n", t);
        }
    }

    return 0;
}
