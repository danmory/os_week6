#include <stdio.h>

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}


void sort(int arr1[], int arr2[], int N){
    for (int i = 0; i < N - 1; i++) {
        for (int j = 0; j < N - i - 1; j++) {
            if (arr1[j] > arr1[j + 1]) {
                swap(&arr1[j], &arr1[j + 1]);
                swap(&arr2[j], &arr2[j + 1]);
            }
        }
    }
}

/* FINDING WAITING, COMPLETION AND TURNAROUND TIMES */
void findTimes(int burstTimes[], int arrivalTimes[], int waitingTimes[], int completionTimes[], int turnaroundTimes[], int N){
    waitingTimes[0] = 0;
    completionTimes[0] = burstTimes[0];
    turnaroundTimes[0] = burstTimes[0];
    for (int i = 1; i < N; ++i) {
        waitingTimes[i] = completionTimes[i-1] - arrivalTimes[i];
        completionTimes[i] = completionTimes[i-1] + burstTimes[i];
        turnaroundTimes[i] = completionTimes[i] - arrivalTimes[i];
    }
}

/* AVERAGE VALUES */
float findAverageValue(int arr[], int N){
    int totalValue = 0;
    for (int i = 0; i < N; ++i) {
        totalValue += arr[i];
    }
    return (float)totalValue/N;
}

/* PRINT TABLE WITH RESULTS */
void print(int completionTimes[], int turnaroundTimes[], int waitingTimes[], float avTurnaroundTime, float avWaitingTime, int N){
    printf("id\t\tct\t\ttat\t\twt\n");
    for (int i = 0; i < N; ++i) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", i, completionTimes[i], turnaroundTimes[i], waitingTimes[i]);
    }

    printf("Average turnaround time: %f \n", avTurnaroundTime);
    printf("Average waiting time: %f \n", avWaitingTime);
}

int main() {
    /* GETTING INPUT DATA*/
    int N;
    printf("Number of processes: ");
    scanf("%d", &N);
    printf("\n");
    int arrivalTimes[N];
    int burstTimes[N];
    for (int i = 0; i < N; ++i) {
        printf("#%d process arrival time: ", i);
        scanf("%d", &arrivalTimes[i]);
        printf("#%d process burst time: ", i);
        scanf("%d", &burstTimes[i]);
    }

    /* SORT PROCESSES BY ARRIVAL DATA */
    sort(arrivalTimes, burstTimes, N);

    /* TO FIND OUT: */
    int completionTimes[N];
    int turnaroundTimes[N];
    int waitingTimes[N];
    float avTurnaroundTime;
    float avWaitingTime;

    findTimes(burstTimes, arrivalTimes, waitingTimes, completionTimes, turnaroundTimes, N);

    avTurnaroundTime = findAverageValue(turnaroundTimes, N);
    avWaitingTime = findAverageValue(waitingTimes, N);

    print(completionTimes, turnaroundTimes, waitingTimes, avTurnaroundTime, avWaitingTime, N);

    return 0;
}
