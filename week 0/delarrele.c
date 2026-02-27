#include <stdio.h>

void main(){
    int arr[100];
    int size,pos,j;

    printf("Enter size of the array: ");
    scanf("%d", &size);

    printf("Enter elements in array: ");
    for(int i = 0; i < size; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Enter the pos to be deleted: ");
    scanf("%d",&pos);

    if(pos>size){
        printf("Invalid pos");
    }else{
        for(j=0;j<pos-1;j++);
        while(j<size){
            arr[j]=arr[j+1];
            j=j+1;
        }
    }
    printf("Array: \n");
    for(int i=0; i<size-1; i++){
        printf("%d ",arr[i]);
    }
}