
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define array_size 5
#define SEND_RANK 0
#define RECV_RANK 1
#define TAG_RS 10
#define TAG_SUM 100
#define SUM_RANK 0
#define m 8


// mpicc first_example.c -o first_mpi_project
// mpirun -np 1 ./first_mpi_sh 

// void pointer_test_function(int *A, int *C){
//     // A[m] + B[m] = C[m]
//     for (int i = 0; i < array_size; i++){
//         *(C+i) = *(A+i) + *(B+i);
//     }
//     return;
// }

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the process
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    printf("world_rank %p  ", &world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];

    // status
    MPI_Status status;
    int arr[array_size] = {0, 1, 2 ,3, 4};  
    int n = sizeof(arr) / sizeof(arr[0]);

    // Declare pointer variable
    int (*ptr)[array_size];
    ptr = &arr;

    int i, *A, *B, S, R;
    A = (int*) malloc(array_size*sizeof(int));  //Số ô nhớ cần cấp để lưu cho m phần tử. sizeof(int) số byte int
    B = (int*) malloc(array_size*sizeof(int));
    for (i = 0; i < array_size; i++) {
        A[i] = (*ptr)[i];  // Dereference ptr to access elements of arr
    }

    // Chia mien tinh toan:
    int mien_tinh_toan = m/world_size;

    if (world_rank == SEND_RANK) {
        printf("Process %d: Sending data to process %d\n", world_rank, RECV_RANK);
        MPI_Send(A, array_size, MPI_INT, RECV_RANK, TAG_RS, MPI_COMM_WORLD);
        printf("\n");

        MPI_Recv(&R, 1, MPI_INT, RECV_RANK, TAG_SUM, MPI_COMM_WORLD, &status);
        printf("R LA: %d ", R);
    
    } else if (world_rank == RECV_RANK) {
        printf("Process %d: Received data back:\n", world_rank);
        MPI_Recv(B, array_size, MPI_INT, SEND_RANK, TAG_RS, MPI_COMM_WORLD, &status);
        printf("MANG B NHAN DUOC LA \n");
        for (i = 0; i < array_size; i++) {
            printf("%d ", B[i]);
        }
        printf("\n");
        S = 0 ;
        for (i = 0; i < array_size; i++) {
            // printf("%d ", B[i]);
            S = S+B[i];
        }
        printf("TINH SUM = %d ", S);
        printf("\n");

        MPI_Send(&S, 1, MPI_INT, SUM_RANK, TAG_SUM, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}