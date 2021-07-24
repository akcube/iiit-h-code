#include<stdio.h>

#define N 8

void rotate90(short (*arr)[8]);
short arr[N][N];

int main(void){
    
    for(int i=0; i<N; i++)
        for(int j=0; j<N; j++)
            scanf("%hi", &arr[i][j]);

    printf("\n");

    rotate90(arr);

    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            printf("%hi ", arr[i][j]);
        }
        printf("\n");
    }
    
}