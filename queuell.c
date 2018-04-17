#include<stdio.h>
#include<stdlib.h>
typedef struct sll{
	int data;
	struct sll *next;
}sll;
sll *enqueue(sll *ptr){
	sll *temp;
	temp=(sll*)malloc(sizeof(sll));
	printf("Enter the element: ");
	scanf("%d",&temp->data);
	temp->next=ptr;
	ptr=temp;
	return ptr;
}


sll *dequeue(sll *temp, sll *front){
	sll *temp1;
	if(temp==NULL){
		printf("No element to delete! The queue is empty!");
		return NULL;
	}
	else if(temp==front){
		printf("The deleted element is: %d\n",temp->data);
		free(temp);
		return NULL;
	}
	else{
		while(temp->next->next!=NULL){
			temp=temp->next;
		}
		temp1=temp->next;
		temp->next=NULL;
		printf("The deleted element is: %d\n",temp1->data);
		free(temp1);
	}
	return temp;
}
void display(sll *ptr){
	sll *temp=ptr;
	if(ptr==NULL)
		printf("No element to show! The queue is empty!\n");
	else{
		while(temp->next!=NULL){
			printf("%d->",temp->data);
			temp=temp->next;
		}
		printf("%d\n",temp->data);
	}
}
int main(){
	sll *rear=NULL,*front=NULL,*temp;
	int ch,i,n;
	while(1){
	       printf("\n1.Insert\n2.Delete\n3.Traverse\n4.Exit\nEnter your choice: ");
		scanf("%d",&ch);
		switch(ch){
			case 1: printf("Enter the no. of elements to insert: ");
					scanf("%d",&n);
					for(i=0;i<n;i++)
						rear=enqueue(rear);
					temp=rear;
					while(temp->next!=NULL)
						temp=temp->next;
					front=temp;
					break;
			case 2: front=dequeue(rear,front);
					if(front==NULL)
						rear=NULL;
					break;
			case 3: display(rear);
					break;
			case 4: return 1;
			default: printf("Wrong choice!");
		}
	}
	return 0;
}
