#include<stdio.h>

int max[10][10], allocation[10][10], need[10][10];
int avail[10];
int np = 5; // Number of processes
int nr = 3; // Number of resources

// Function to read matrix data (Allocation or Max)
void readMatrix(int matrix[10][10]){
    for(int i = 0; i < np; i++){
        for(int j = 0; j < nr; j++){
            scanf("%d", &matrix[i][j]); // Fix: Should be matrix[i][j]
        }
    }
}

// Function to display the matrix
void displayMatrix(int matrix[10][10]){
    for(int i = 0; i < np; i++){
        printf("\nP%d ", i); // For process labeling
        for(int j = 0; j < nr; j++){
            printf("%d ", matrix[i][j]);
        }
    }
    printf("\n");
}

// Function to calculate the need matrix
void calculate_need(){
    for(int i = 0; i < np; i++){
        for(int j = 0; j < nr; j++){
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function implementing Banker's Algorithm
void banker(){
    int k = 0;
    int safe_seq[10], finish[10], flag = 0;

    // Initialize all processes as incomplete
    for(int i = 0; i < np; i++){
        finish[i] = 0;
    }

    for(int i = 0; i < np; i++){
        flag = 0;
        if(finish[i] == 0){ // Process i is incomplete
            for(int j = 0; j < nr; j++){
                if(need[i][j] > avail[j]){ // Need exceeds available resources
                    flag = 1; // Process cannot proceed
                    break;
                }
            }
            if(flag == 0){ // Process i can proceed
                finish[i] = 1; // Mark process as complete
                safe_seq[k] = i; // Add process to the safe sequence
                k++; 
                for(int j = 0; j < nr; j++){
                    avail[j] += allocation[i][j]; // Release resources
                }
                i = -1; // Restart checking from the first process
            }
        }
    }

    // Check if all processes are completed
    flag = 0;
    for(int i = 0; i < np; i++){
        if(finish[i] == 0){
            flag = 1;
            printf("\nThe system is in deadlock!\n");
            break;
        }
    }

    if(flag == 0){
        printf("\nThe system is in a safe state!\nSafe sequence is ==> ");
        for(int i = 0; i < k; i++){
            printf("P%d ", safe_seq[i]);
        }
        printf("\n");
    }
}

int main(){
    // Read input
    printf("\nEnter initial allocation matrix:\n");
    readMatrix(allocation);
    
    printf("\nEnter Max requirement matrix:\n");
    readMatrix(max);

    printf("\nEnter available resources:\n");
    for(int i = 0; i < nr; i++)
        scanf("%d", &avail[i]);

    // Display entered data
    printf("\n****** Entered Data ******\n");
    printf("\nInitial allocation matrix:");
    displayMatrix(allocation);
    printf("\nMaximum requirement matrix:");
    displayMatrix(max);
    printf("\nAvailable resources:\n");
    for(int i = 0; i < nr; i++)
        printf("%d ", avail[i]);

    // Calculate and display need matrix
    calculate_need();
    printf("\n\nNeed matrix:");
    displayMatrix(need);

    banker();
    
    printf("\n");
    return 0;
}

