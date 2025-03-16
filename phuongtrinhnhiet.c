// #include <stdio.h>
// #include <stdlib.h>

// #define  M       20
// #define  Ntime   1000
// #define  dt      0.01
// #define  dx      0.1
// #define  D       0.1
// //=========================
// void KhoiTao(float *T){
//   int i;
//   for (  i = 0 ; i < M ; i++ )
//      *(T+i) = 25.0;
// }
// //=========================
// void DHB2(float *T, float *dT){
// int i;
// float c,l,r;
// for (  i = 0 ; i < M ; i++ ) {
//       c = *(T+i);
//       l = (i==0)   ? 100.0 : *(T+(i-1));
//       r = (i==M-1) ? 25.0  : *(T+(i+1));
//       *(dT+i) = D*(r-2*c+l)/(dx*dx);
//     }
// }
// //=========================
// int main(){
//     int i,t;
//     float *T,*dT;
//     T  = (float *) malloc ((M)*sizeof(float));
//     dT = (float *) malloc ((M)*sizeof(float));
//     KhoiTao(T);
//     for (t=0;t<Ntime;t++) {
//         DHB2(T, dT);
//         for (  i = 0 ; i < M ; i++ )
//             *(T+i) = *(T+i) + dt*(*(dT+i));
//         }
//     for (  i = 0 ; i < M ; i++ ) printf("%f \n",*(T+i));
//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#define  M       20
#define  Ntime   1000
#define  dt      0.01
#define  dx      0.1
#define  D       0.1
//=========================
void KhoiTao(float *T){
  int i;
  for (  i = 0 ; i < M ; i++ )
     *(T+i) = 25.0;
}
//=========================
void DHB2(float *Ts, float *dTs, int Ms, float Tl, float Tr){
int i;
float c,l,r;
for (  i = 0 ; i < Ms ; i++ ) {
      c = *(Ts+i);
      l = (i==0)   ? Tl : *(Ts+(i-1));
      r = (i==Ms-1) ? Tr  : *(Ts+(i+1));
      *(dTs+i) = D*(r-2*c+l)/(dx*dx);
    }
}
//=========================
int main(int argc, char *argv[]){
  int i,t;
  float *T,*dT;
  T  = (float *) malloc ((M)*sizeof(float));
  dT = (float *) malloc ((M)*sizeof(float));
  int NP, Rank;
  MPI_Init (&argc, &argv);
  MPI_Comm_size(MPI_COMM_WORLD,&NP);
  MPI_Comm_rank(MPI_COMM_WORLD,&Rank);
  MPI_Status Warning;
// Step 1: Input (A, B) at Rank 0
  if (Rank == 0)
    KhoiTao(T);
// Step 2:Domain decomposition
  int Ms = M/NP;
  float *Ts,*dTs, Tl, Tr;
  Ts  = (float *) malloc ((Ms)*sizeof(float));
  dTs = (float *) malloc ((Ms)*sizeof(float)); 
// Step 3:Input distribution
  MPI_Scatter(T,Ms,MPI_FLOAT,Ts,Ms,MPI_FLOAT,0,MPI_COMM_WORLD);
// Step 4:Computation
for (t=0;t<Ntime;t++) {
// Step 4.1 - Tl
   if (Rank == 0){
	Tl = 100;
	MPI_Send(Ts + Ms - 1, 1, MPI_FLOAT,
               Rank + 1, Rank, MPI_COMM_WORLD);
   } else if (Rank == NP - 1) {
	MPI_Recv(&Tl, 1, MPI_FLOAT, 
    Rank - 1, Rank - 1, MPI_COMM_WORLD, &Warning);
   } else {
	MPI_Send(Ts + Ms - 1, 1, MPI_FLOAT, 
               Rank + 1, Rank, MPI_COMM_WORLD);
	MPI_Recv(&Tl, 1, MPI_FLOAT, 
    Rank - 1, Rank - 1, MPI_COMM_WORLD, &Warning);
   }
// Step 4.1 - Tr
   if (Rank == NP - 1){
	Tr = 25;
	MPI_Send (Ts, 1, MPI_FLOAT, 
               Rank - 1, Rank, MPI_COMM_WORLD);
   } else if (Rank == 0) {
	MPI_Recv (&Tr, 1, MPI_FLOAT, 
    Rank + 1, Rank + 1, MPI_COMM_WORLD, &Warning);
   } else {
	MPI_Send (Ts, 1, MPI_FLOAT, 
               Rank - 1, Rank, MPI_COMM_WORLD);
	MPI_Recv (&Tr, 1, MPI_FLOAT, 
    Rank + 1, Rank + 1, MPI_COMM_WORLD, &Warning);
    }
// Step 4.2: Compute
      DHB2(Ts, dTs, Ms,Tl,Tr);
      for (  i = 0 ; i < Ms ; i++ )
          *(Ts+i) = *(Ts+i) + dt*(*(dTs+i));
// Step 5:Output gathering
}
   MPI_Gather(Ts,Ms,MPI_FLOAT,T,Ms,MPI_FLOAT,0,MPI_COMM_WORLD);
   if (Rank==0) for (  i = 0 ; i < M ; i++ ) printf("%f \n",*(T+i));
   MPI_Finalize();
return 0;
}


