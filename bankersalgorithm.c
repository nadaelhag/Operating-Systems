#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>

int max[100][100], sequence[100], a[100], need[100][100], e[100];
int C[100][100];
int n, m;
bool isFinished[100];

void intialize();
void isSafe();
void request();

int main() {
    int i, j;
    intialize();
    isSafe(n, m);
    request();
    return 0;
}

void intialize() {
    int i, j;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    
    printf("Enter the number of instances: ");
    for (j = 0; j < m; j++) {
        scanf("%d", &e[j]);
    }
    
    printf("Enter the available resources: ");
    for (j = 0; j < m; j++) {
        scanf("%d", &a[j]);
    }
    
    printf("Enter the allocation matrix:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &C[i][j]);
    
    printf("Enter the maximum need matrix:\n");

    for (i = 0; i < n; i++){
        for (j = 0; j < m; j++)
            scanf("%d", &max[i][j]);
    }
    
    //calculate need matrix
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            need[i][j] = max[i][j] - C[i][j];
        }
    }
}

void isSafe(int n, int m) {
    int i, j, work[100], count = 0;
    for (i = 0; i < m; i++)
        work[i] = a[i];
    for (i = 0; i < 100; i++)
        isFinished[i] = false;
    while (count < n) {
        bool canAllot = false;
        for (i = 0; i < n; i++) {
            if (isFinished[i] == false) {
                for (j = 0; j < m; j++) {
                    if (work[j] < need[i][j]) {
                        break;
                    }
                }
                if (j == m) {
                    for (j = 0; j < m; j++) {
                        work[j] += C[i][j];
                    }
                    sequence[count++] = i;
                    isFinished[i] = true;
                    canAllot = true;
                }
            }
        }
        if (canAllot == false) {
            printf("System is not in safe state\n");
            return;
        }
    }

    printf("System is in safe state\n");

    printf("Safe process sequence: ");
    for (i = 0; i < n; i++)
        printf("P%d ", sequence[i]);
    printf("\n");
}

void request() {
    int c, R[100][100], i, j;
    printf("\n");
    printf("Do you want make an additional request for any of the process ? (1=Yes|0=No) ");
    
    scanf("%d", &c);
    
    printf("\n");
    if (c == 1) {
        printf("Enter the request matrix:\n");
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                scanf("%d", &R[i][j]);
            }
        }
        
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                if (R[i][j] > need[i][j]) {
                    if(R[i][j] > C[i][j]){
                        printf("Error- Request is greater than maximum need or allocation\n");
                        exit(0);
                    }
                }
            }
        }
        
        for (i = 0; i < n; i++) {
            for (j = 0; j < m; j++) {
                a[j] -= R[i][j];
                C[i][j] += R[i][j];
                need[i][j] -= R[i][j];
            }
        }
        
        isSafe(n, m);
    } 
    else {
        exit(0);
    }
}
