#include <stdio.h>
#include <stdlib.h>

void push(int *stack, int *top, int limit){
		int value;
		if(*top == limit){
				printf("\n[Push] [Error] Stack overflow!\n");
				return;
		}
		printf("\n[Push] Enter value to insert : ");
		scanf("%d", &value);
		stack[*top] = value;
		*top = *top + 1;
		printf("[Push] Complete!\n");
}

void pop(int *stack, int *top){
		if(*top == 0){
				printf("\n[Pop] [Error] Stack underflow!\n");
				return;
		}
		*top = *top - 1;
		printf("\n[Pop] Item popped : %d\n", stack[*top]);
}

void print_stack(int *stack, int top, int limit){
		int i = 1;
		if(top == 0){
			printf("\n[Print] [Error] Stack underflow!\n");
			return;
		}
		printf("\n[Print] Stack contains : { %d", stack[0]);
		while(i < limit){
				if(i < top)
					printf(", %d", stack[i]);
				else
					printf(", <Null>");
				i++;
		}
		printf(" }\n");
}

int main(){	
		int limit, *stack = NULL, top = 0;
		char choice = '1';
		printf("\n[Stack] Enter stack limit : ");
		scanf("%d", &limit);
		stack = (int *)malloc(sizeof(int) * limit);
		if(stack == NULL){
				printf("[Error] Memory unavailable!");
				return 1;
		}
		printf("[Stack] Creation successful!\n");
		while(choice >= '1' && choice <= '3'){
			printf("\n[Menu] 1. Push\n[Menu] 2. Pop\n[Menu] 3. Print : ");
			scanf(" %c", &choice);
			switch(choice){
				case '1':
					push(stack, &top, limit);
					break;
				case '2':
					pop(stack, &top);
					break;
				case '3':
					print_stack(stack, top, limit);
					break;
				default:
					printf("\n[Stack] Wrong choice!\n");
					break;
			}
		}
		
		printf("\n");
		free(stack);
		return 1;
}
