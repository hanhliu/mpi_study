
#include <stdio.h>
#include <mpi.h>
#include <stdlib.h>

#define m 8

int main(int argc, char** argv) {
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size, world_rank;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    // status
    MPI_Status status;

    int i, *A, *B, *C, *As, *Bs, *Cs;
    int ms = m/world_size; // chia số khoảng tính toán

    As = (int*) malloc(ms*sizeof(int));  //Số ô nhớ cần cấp để lưu cho m phần tử. sizeof(int) số byte int
    Bs = (int*) malloc(ms*sizeof(int));
    Cs = (int*) malloc(ms*sizeof(int));
    A = (int*) malloc(m*sizeof(int));  //Số ô nhớ cần cấp để lưu cho m phần tử. sizeof(int) số byte int
    B = (int*) malloc(m*sizeof(int));
    C = (int*) malloc(m*sizeof(int));

    if (world_rank == 0){
        for (i = 0; i < m; i++) *(A+i) = i;
        for (i = 0; i < m; i++) *(B+i) = 2+i;
    }
    
    // Chia mien tinh toan:

    // if (world_rank == 0) {
    //     printf("HERE 11111\n");
    //     for (i = 0; i < ms; i++) *(As+i) = *(A+i);
    //     for (i = 0; i < ms; i++) *(Bs+i) = *(B+i);
    //     for (int cpu =1; cpu < world_size; cpu++){
    //         MPI_Send(A + cpu*ms, ms, MPI_INT, cpu, cpu, MPI_COMM_WORLD);
    //         MPI_Send(B + cpu*ms, ms, MPI_INT, cpu, cpu+100, MPI_COMM_WORLD);
    //     }
    
    // } else{
    //     printf("HERE 2222\n");
    //     MPI_Recv(As, ms, MPI_INT, 0, world_rank, MPI_COMM_WORLD, &status);
    //     MPI_Recv(Bs, ms, MPI_INT, 0, 100+world_rank, MPI_COMM_WORLD, &status);

    // }
    MPI_Scatter(A, ms, MPI_INT, As, ms, MPI_INT, 0, MPI_COMM_WORLD);  // chia để gửi cho các phần tử 
    MPI_Scatter(B, ms, MPI_INT, Bs, ms, MPI_INT, 0, MPI_COMM_WORLD);

    for (i = 0; i < ms; i++) {
            *(Cs+i) = *(As+i) + *(Bs+i);
        }

    // if (world_rank != 0){
    //     printf("HERE 33333\n");
    //     MPI_Send(Cs, ms, MPI_INT, 0, world_rank, MPI_COMM_WORLD);
    // }else{
    //     printf("HERE 44444\n");
    //     for (i=0; i < ms; i++) *(C+i) = *(Cs+i);
    //     for (int cpu = 1; cpu < world_size; cpu++){
    //         MPI_Recv(C+ms*cpu, ms, MPI_INT, cpu, cpu, MPI_COMM_WORLD, &status);
    //     }
    // }
    MPI_Gather(Cs, ms, MPI_INT, C, ms, MPI_INT, 0, MPI_COMM_WORLD);

    if (world_rank == 0){
        printf("HERE  5555\n");
        for (i=0; i < m; i++) printf("%d ", *(C+i));
    }

    free(A);
    free(B);
    free(C);
    free(As);
    free(Bs);
    free(Cs);
    
    // Finalize the MPI environment.
    MPI_Finalize();
    return 0;
}