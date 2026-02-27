#include<stdio.h>
#include<stdlib.h>

int arr[7];

void main(){
    int a,s1,s2;
    printf("Enter array elements: \n");
    for(int i;i<7;i++){
        scanf("%d", &a);
        arr[i]=a;
    }
    s1=arr[0];
    for(int j=0;j<7;j++){
        if(arr[j]<s1){
            s1=arr[j];
        }
    }
    s2=arr[0];
    for(int k;k<7;k++){
        if(arr[k]==s1){
            continue;
        }else if(arr[k]<s2){
            s2=arr[k];
        }
    }
    printf("The 2nd smallest element in the array is: ");
    printf("%d",s2 );

}