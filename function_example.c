#include <stdio.h>
#include <stdlib.h>
#define m 5

/** Hàm thường */
float test_function(float a, float b){
    // a.x+b = 0
    float x;
    x = -b/a;
    return x;
}

/** Hàm con trỏ */
void pointer_test_function(int *A, int *B, int *C){
    // A[m] + B[m] = C[m]
    for (int i = 0; i < m; i++){
        *(C+i) = *(A+i) + *(B+i);
    }
    return;
}

int main(){
    /** normal function */
    // float m, n;
    // printf("NHAP m, n = "); scanf("%f%f", &m, &n);
    // float nghiem = test_function(m, n);
    // printf("NGHIEM LA %f ", nghiem);

    /** */
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

    pointer_test_function(A, B, C);

    for (int i = 0; i<m; i++) printf("SO CAN TIM %d   ", *(C+i));

    return 0;
}