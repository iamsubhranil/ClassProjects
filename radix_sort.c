#include <stdlib.h>
#include <stdio.h>

// Radix sort (decimal)
// ===================

#define el_abs(x) (x < 0 ? -x : x)

void sort_radix(int *arr, int count){
    // Find the maximum number
    int64_t max = el_abs(arr[0]);
    for(int i = 1; i < count ;i++){
        if(max < el_abs(arr[i]))
            max = el_abs(arr[i]);
    }
    // Count the number of digits in it, and hence number of passes
    int passes = 0;
    while(max > 0){
        max /= 10; passes++;
    }

    // Create 20 buckets, for digits -ve 0-9 and +ve 0-9 respectively
    int buckets[20][count];

    int partExtractor = 10, digitExtractor = 1;
    // Start pass
    while(passes > 0){
        // Pointer to buckets
        int bucketPointer[20] = {0};
        // Extraction loop
        for(int i = 0; i < count ; i++){
            int64_t element = arr[i]; // Get the element at ith position
            int64_t digit = ((el_abs(element))% partExtractor) / digitExtractor; // Extract the digit
            if(element >= 0)
                digit += 10;
            else
                digit = 9 - digit;
            buckets[digit][bucketPointer[digit]] = element; // Put the element into required bucket
            bucketPointer[digit]++; // Increase the bucketPointer for that digit
        }

        // Put them again in the original array
        int digit = 0, arrPointer = 0, tempPointer = 0;
        while(digit < 20){
            if(tempPointer == bucketPointer[digit]){ // tempPointer should always be less than
                tempPointer = 0;                    // bucketPointer if the bucket at digit
                digit++;                            // has atleast one element
                continue;
            }

            // Put the element from bucket to the original array
            arr[arrPointer] = buckets[digit][tempPointer];
            arrPointer++;
            tempPointer++;
        }

        // Increment
        partExtractor *= 10;
        digitExtractor *= 10;
        passes--;
    }
}

static void print_list(int *arr, int count){
    printf("{ %d", arr[0]);
    for(int i = 1;i < count;i++){
        printf(", %d", arr[i]);
    }
    printf(" }");
}

int main(){
    int num;
    printf("\nEnter the number of elements : ");
    scanf("%d", &num);
    if(num < 1){
        printf("\nThere should be atleast 1 element!\n");
        return 1;
    }
    int *arr = (int *)malloc(sizeof(int) * num);
    for(int temp = 0;temp < num;temp++){
        printf("\nEnter element %d : ", (temp + 1));
        scanf("%d", &arr[temp]);
    }
    printf("\nBefore sorting : ");
    print_list(arr, num);
    sort_radix(arr, num);
    printf("\nAfter sorting : ");
    print_list(arr, num);
    printf("\n");
    free(arr);
    return 0;
}
