#include<stdio.h>
#include<stdlib.h>

int arr[7];

void main(){
    int a,l1,l2;
    printf("Enter array elements: \n");
    for(int i;i<7;i++){
        scanf("%d", &a);
        arr[i]=a;
    }
    l1=arr[0];
    for(int j=0;j<7;j++){
        if(arr[j]>l1){
            l1=arr[j];
        }
    }
    l2=arr[0];
    for(int k;k<7;k++){
        if(arr[k]==l1){
            continue;
        }else if(arr[k]>l2){
            l2=arr[k];
        }
    }
    printf("The 2nd smallest element in the array is: ");
    printf("%d",l2 );

}