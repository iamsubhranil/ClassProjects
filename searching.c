#include <stdio.h> 

long linear_search(long a[], long n, long find);
long binary_search(long a[], long n, long find);

int main()
{
    long array[100], search, i, n, position; 
    int ch;

    printf("Input number of elements in array: ");
    scanf("%ld", &n);

    for (i = 0; i < n; i++){
        printf("Enter the element no %ld: ",i+1);
        scanf("%ld", &array[i]);
    } 
    printf("Input number to search: ");
    scanf("%ld",&search);
    printf("1.Linear search\n2.Binary search\nEnter your choice: ");
    scanf("%d",&ch);
    switch(ch){
        case 1: position = linear_search(array, n, search);
                break;
        case 2: position = binary_search(array, n, search);
                break;
    } 
    if (position == -1)
        printf("%ld is not present in array.\n", search);
    else
        printf("%ld is present at location %ld.\n", search, position);

    return 0;
} 
long linear_search(long a[], long n, long find) 
{
    long c; 
    for (c = 0 ;c < n ; c++ ) 
    {
        if (a[c] == find)
            return c+1;
    } 
    return -1;
}
long binary_search(long a[], long n, long find)
{
    int first = 0; long last = n-1, middle;
    middle = (first+last)/2; 
    while (first <= last) {
        if (a[middle] < find)
            first = middle + 1;    
        else if (a[middle] == find) {
            return middle+1;
        }
        else
            last = middle - 1;
        middle = (first + last)/2;
    }
    return -1;
}
