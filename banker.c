#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define NUMBER_OF_PROCESSES 5
#define NUMBER_OF_RESOURCES 4

/*
We use the banker’s algorithm to determine whether or not a state is a safe state, and therefore, whether or not to
grant the resource requests of the processes.
Use 2D arrays to represent the matrices and a 1D array for the vector. For example:
#define NUMBER_OF_PROCESSES 5
#define NUMBER_OF_RESOURCES 4
int available[NUMBER_OF_RESOURCES]; // the available amount of each resource
int claim[NUMBER_OF_ PROCESSES][NUMBER_OF_RESOURCES]; // the claim of each process
int allocation[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES]; //allocation per process
int need[NUMBER_OF_ PROCESSES][NUMBER_OF_RESOURCES]; //C – A
Processes request resources from the system. The Operating System (OS) will grant a request only if it leaves the
system in a safe state. A request that leaves the system in an unsafe state will be denied.
Input text files are provided, where each file contains, in this order, the claim matrix, the allocation matrix, and the
available vector.
Output to screen: the claim matrix, allocation matrix, C – A matrix, available vector, the updates made to the available
matrix, and whether or not the state is safe. If it is a safe state, output a possible sequence; if it is not a safe state,
output the list of processes that cannot run. Sample output is shown on the next page – the layout of the output must
match. Include screenshots for each input text file.
*/

int available[NUMBER_OF_RESOURCES]; // the available amount of each resource
int claim[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES]; // the claim of each process
int allocation[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES]; //allocation per process
int need[NUMBER_OF_PROCESSES][NUMBER_OF_RESOURCES]; //C – A

void parser()
{
    FILE* fp1;
    fp1 = fopen("inp3.txt", "r");
    char str[200];
    char* rch;
    int temp;
    int temp_col;
    int line = 0;
    while (fgets(str, sizeof(str), fp1) != NULL)    // gets each line in fp1
    {
        // keeps track of which col to store value in
        temp_col = 0;
        rch = strtok(str, " ");                         // rch is element after spliting by " "
        while (rch != NULL){
            temp = atoi(rch);                           // temp value is rch converted to int
            if(line >= 0 && line <= 4){                 // if line is within 1-5 line store in claim matrix
                claim[line][temp_col] = temp;
                //printf("%d ", claim[line][temp_col]);
            }
            else if(line >= 6 && line <= 10){   
                allocation[line-6][temp_col] = temp;    // if line is within 7-11 line store in allocation matrix
                //printf("%d ", allocation[line-6][temp_col]);
            }
            else if(line == 12){
                available[temp_col] = temp;             // if line is 12 store in claim matrix
                //printf("%d ", available[temp_col]);
            }
            temp_col++;                                 // update col tracker
            rch = strtok(NULL, " ");                    // update rch pointer to go to next element
        }
        //printf("\n");
        line++;
    }

}
void needs_matrix()
{
    // Matrix Operations to Evaluate C-A
    //printf("C - A Matrix: \n");
    for(int i = 0; i < NUMBER_OF_PROCESSES; i++){
        for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
            need[i][j] = claim[i][j] - allocation[i][j];
            //printf("%d ", need[i][j]);
        }
        //printf("\n");
    }
}

void print_matrixes()
{
    for(int i = 0; i < NUMBER_OF_PROCESSES; i++){
        for(int j = 0; j < NUMBER_OF_RESOURCES+8; j++){
            if(j==0){
                printf("P%d ", i);
                printf("%d ", claim[i][j]);
            }
            else if (j<4){
                printf("%d ", claim[i][j]);
            }
            else if (j==4){
                printf("     P%d ", i);
                printf("%d ", allocation[i][j-4]);
            }
            else if (j>4&&j<8){
                printf("%d ", allocation[i][j-4]);
            }
            else if (j==8){
                printf("         P%d ", i);
                printf("%d ", need[i][j-8]);
            }
            else{
                printf("%d ", need[i][j-8]);
            }
        }
        printf("\n");
    }
    printf("\nAvailable\n");
    printf("A B C D\n");
    printf("%d %d %d %d\n", available[0], available[1], available[2], available[3]);
}
void safe_sequence()
{
    // Determine if initial state is a safe state. Use an algorithm to compare Available vector and Needs vector
    int processes_ran = 0;
    int flags[5] = {0,0,0,0,0};
    int safe_seq[5] = {0,0,0,0,0};
    int safe_ind = 0;
    int restart = 0;
    printf("\n");
    while(processes_ran != 5){
    printf("Available ");
    printf("%d %d %d %d\n", available[0], available[1], available[2], available[3]);
        for(int i = 0; i < NUMBER_OF_PROCESSES; i++){
            for(int j = 0; j < NUMBER_OF_RESOURCES; j++){
                if(flags[i] == 1){      // check if process has ran before
                    break;
                }
                if(available[j] >= need[i][j]){
                    if(j==3){
                        flags[i] = 1;   // mark off the process as it has ran
                        safe_seq[safe_ind] = i; // add to safe sequence
                        safe_ind = safe_ind + 1; // update safe_ind
                        processes_ran = processes_ran + 1; // add to processes ran
                        // loop through to print process ran and add to available
                        printf("P%d runs ", i);
                        for(int k = 0; k < NUMBER_OF_RESOURCES; k++){
                            printf("%d ", allocation[i][k]);
                            available[k] = available[k] + allocation[i][k];
                        }
                        printf("\n");
                        restart = 1;
                        break;          // restart process check
                    }
                }
                else{
                    if(j==3&&i==4){     // check if a process cannot run
                        printf("The initial state is not a safe state, the processes that cannot run are: ");
                        for(int k = 0; k<5; k++){
                            if(flags[k]==0){
                                printf("P%d ", k);
                            }
                        }
                        printf("\n");
                        return;
                    }
                    break; // process cannot run
                }
            }
            if(restart == 1){
                restart = 0;
                break;
            }
        }
    }
    printf("Available ");
    printf("%d %d %d %d\n", available[0], available[1], available[2], available[3]);
    printf("\n");
    printf("Yes, the initial state is a safe state. Safe sequence: ");
    for(int i = 0; i < 5; i++){
        printf("P%d ", safe_seq[i]);
    }
    printf("\n");
}   

int main ()
{
    // Possibly loop through and print each row for matrix
    printf("Claim           Allocation          C - A\n");
    printf("   A B C D         A B C D             A B C D\n");
    parser();
    needs_matrix();
    print_matrixes();
    safe_sequence();
    return 0;
}