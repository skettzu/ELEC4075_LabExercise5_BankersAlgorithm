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
    fp1 = fopen("inp1.txt", "r");
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

void safe_sequence(){
    // Determine if initial state is a safe state. Use an algorithm to compare Available vector and Needs vector
}

int main ()
{
    // Possibly loop through and print each row for matrix
    printf("Claim           Allocation          C - A\n");
    printf("A B C D         A B C D             A B C D\n");
    parser();
    needs_matrix();
    return 0;
}