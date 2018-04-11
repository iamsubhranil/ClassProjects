#include<stdio.h>
#include<stdlib.h>
int main()
{
    int *a,i,j,n;
    printf("Enter the number of elements of the array: ");
    scanf("%d",&n);
    a=(int*)malloc(n*sizeof(int));
    for(i=0;i<n;i++){
        printf("Enter the element no. %d: ",i+1);
        scanf("%d",&a[i]);
    }
    printf("The sorted array is: \n");

    for (i=1;i<n;i++){
        int key=a[i];
        j=i-1;
        /* Move elements of a[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while(j>=0&&a[j]>key){
            a[j+1]=a[j];
            j--;
        }
        a[j+1]=key;
    }
    for(i=0;i<n;i++){
        printf("%d\n",*(a+i));
    }
    return 0;
}
