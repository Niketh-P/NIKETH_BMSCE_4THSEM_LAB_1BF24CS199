#include<stdio.h>
#include<stdlib.h>

int arr[3][3];

void main(){
    int a,i,j;
    printf("Enter matrix elements(a11,a12,a13,a21...): ");
    for(int x=0;x<3;x++){
        for(int y=0;y<3;y++){
            scanf("%d",&a);
            arr[x][y]=a;
        }
    }
    printf("Matrix: \n");
    for(int x=0;x<3;x++){
        for(int y=0;y<3;y++){
            printf("%d ", arr[x][y]);
        }
        printf("\n");
    }
    printf("Sum of left diagonal: ");
    i=(arr[0][0]+arr[1][1]+arr[2][2]);
    printf("%d", i);
}