
#include <stdio.h>
#include <stdlib.h>
#define m 5
// int main(void) {
//     int v_year;
//     float divide_result;
//     scanf("%i", &v_year);

//     divide_result = v_year%4;

//     if (divide_result == 0)
//         printf("LEAP YEAR");
//     else
//         printf("NOT LEAP YEAR");
//     return 0;
// }


// int length = sizeof(Arr) / sizeof(Arr[0]);

// int main(void) {
//     int a;
//     int b;
//     int c;
//     int d;
//     int e;
//     int result=0;
//     scanf("%i%i%i%i%i", &a, &b, &c, &d, &e);
//     int v_arr[5] = {a, b, c, d, e};
    
//     for (int i = 0; i < sizeof(v_arr)/sizeof(v_arr[0]); i++){
//         result = result+v_arr[i];
//     }
    
//     printf("result = %i", result);
//     return 0;
// }


// int main() {
//     int a = 0;
//     int sum=0;
//     printf("INIT sum = %d", sum);

//     while (sum < 88){
//         printf("nhap so a = ");scanf("%d", &a);
//         sum = sum+a;
//     }
//     printf("OUTTT sum = %d", sum);
//     return 0;
// }


// int main() {
//     int n = 0; 
//     int sum=0;
//     // printf("NHAP N = "); scanf("%d", &n);

//     while (sum < 100){
//         if (sum + n +1 >= 100) break;
//         n++;
//         sum = sum+n;
//     }
//     printf("OUTTT sum = %d", sum);
//     return 0;
// }


// int main(void) {
//     int a, min = 10000;
//     int result=0;
//     int v_arr[5];
    
//     for (int i = 0; i < sizeof(v_arr)/sizeof(v_arr[0]); i++){
//         printf("Nhap so = v_arr[%i]", i); scanf("%d", &v_arr[i]);
//         if (v_arr[i] < min){
//             min = v_arr[i];
//         }
//     }

//     printf("min = %i", min);
//     return 0;
// }

/** CONG HAI VECTOR */

int main(void) {
    int i, *A, *B, *C;
    A = (int*) malloc(m*sizeof(int));  //Số ô nhớ cần cấp để lưu cho m phần tử. sizeof(int) số byte int
    B = (int*) malloc(m*sizeof(int));
    C = (int*) malloc(m*sizeof(int));

    for (int i = 0; i < m; i++){
        printf("Nhap so = A[%i] ", i); scanf("%d", &A[i]);
    }
    for (int i = 0; i < m; i++){
        printf("Nhap so = B[%i] ", i); scanf("%d", &B[i]);
    }

    for (int i = 0; i < m; i++){
        *(C+i) = *(A+i) + *(B+i);
    }

    for (int i = 0; i<m; i++) printf("SO CAN TIM %d   ", *(C+i));

    return 0;
}


