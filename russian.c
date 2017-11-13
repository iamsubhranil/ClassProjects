// program in c to perform the multiplication of two numbers(not very large) using Russian Peasant method
// the steps are 
// 1. write each number at the head of particular columns repesctively
// 2. double the number in the first column and halve the number in the second column. if the number in the second column is odd, 
// divide it by 2 and drop the remainder. if the number is even cross out the entire row
// 3. keep doubling, halving and crossing out until the number in the second column is one
// 4. add up the remaining numbers in the first column. the total is the product of the original numbers
// example :
// consider the two numbers 17 and 19
// 17								19
// ===============================================================
// 8								38 x(struck of)
// 4								76 x(struck of)
// 2								152 x(struck of)
// 1								304
//
// Now the remaining number on the RHS is added, i.e. (19+304) = 323 = 17x19

#include <stdio.h>

int main(){
	long long a, b, d, p, n[20], s, i;
	char ch = 'Y';
	do{
		printf("\nEnter the two numbers : ");
		scanf("%lld%lld", &a, &b);
		printf("\nPeasant Multiplication Method as follows : \n");
		printf("\n===========================================\n");
		i = 0;
		for(d = a, p = b;d > 0;d = d/2, p = p*2){
			if(d % 2 == 0)
				printf("\n\n%3lld\t\t%3lld x(struck of)", d, p);
			else{
				printf("\n\n%3lld\t\t%3lld", d, p);
				n[i++] = p;
			}
		}
		s = n[0];
		printf("\n\n %lld", n[0]);
		for(d = 1;d < i;d++){
			s = s + n[d];
			printf(" + %lld", n[d]);
		}
		printf(" = %lld", s);
		printf(" which is equal to %lld * %lld = %lld", a, b, (a*b));
		printf("\n\nDo you want to continue (y/n) ? ");
		scanf(" %c", &ch);
	} while(ch == 'Y' || ch == 'y');
	
	return 0;
}
