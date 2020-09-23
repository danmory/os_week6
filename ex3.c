#include <stdio.h>
#include <stdlib.h>

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
void findTimes(int burstTimes[], int arrivalTimes[], int waitingTimes[], int completionTimes[], int turnaroundTimes[], int N, int quantum){
    int isDone[N]; // is current process terminated
    int remainingBurstTimes[N]; // remaining execution time of a process
    int time = arrivalTimes[0]; // time at the current moment
    int doneProcesses = 0; // how many processes are terminated

    for (int i = 0; i < N; ++i) {
        isDone[i] = 0;
        remainingBurstTimes[i] = burstTimes[i];
    }
    for (int i = 0; i < N; ++i) {
        completionTimes[i] = arrivalTimes[i];
    }

    int i = 0;
    while (1){
        /* New round */
        if (i == N){
            i = 0;
            continue;
        }
        /* If all processes are done then exit*/
        if (doneProcesses == N){
            break;
        }

        if (isDone[i] == 0) {
            /* If process is not arrived yet*/
            if (arrivalTimes[i] > time){
                i = 0;
                continue;
            }
            /* If process exists */
            if (remainingBurstTimes[i] <= quantum) {
                doneProcesses++;
                time += remainingBurstTimes[i];
                completionTimes[i] = time;
                remainingBurstTimes[i] = 0;
                isDone[i] = 1;
                i++;

            }else{
                remainingBurstTimes[i] -= quantum;
                time += quantum;
                completionTimes[i] = time;
                i++;
            }
        }else{
            i++;
        }
    }

    for (int j = 0; j < N; ++j) {
        turnaroundTimes[j] = completionTimes[j] - arrivalTimes[j];
        waitingTimes[j] = turnaroundTimes[j] - burstTimes[j];
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
    if (N == 0){
        exit(0);
    }
    int arrivalTimes[N];
    int burstTimes[N];
    for (int i = 0; i < N; ++i) {
        printf("#%d process arrival time: ", i);
        scanf("%d", &arrivalTimes[i]);
        printf("#%d process burst time: ", i);
        scanf("%d", &burstTimes[i]);
    }

    int quantum;
    printf("quantum: ");
    scanf("%d", &quantum);

    /* SORT PROCESSES BY ARRIVAL DATA */
    sort(arrivalTimes, burstTimes, N);

    /* TO FIND OUT: */
    int completionTimes[N];
    int turnaroundTimes[N];
    int waitingTimes[N];
    float avTurnaroundTime;
    float avWaitingTime;

    findTimes(burstTimes, arrivalTimes, waitingTimes, completionTimes, turnaroundTimes, N, quantum);

    avTurnaroundTime = findAverageValue(turnaroundTimes, N);
    avWaitingTime = findAverageValue(waitingTimes, N);

    print(completionTimes, turnaroundTimes, waitingTimes, avTurnaroundTime, avWaitingTime, N);

    return 0;
}
