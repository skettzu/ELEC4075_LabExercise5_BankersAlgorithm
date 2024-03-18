#include <stdio.h>
#include <stdlib.h>
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

void needs_matrix()
{
    // Matrix Operations to Evaluate C-A
}

int main ()
{
    return 0;
}