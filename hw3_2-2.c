#include <stdio.h>
#include <stdlib.h>


const int queue_size = 4;
int rear = 0;
int front = 0;

void queueFull();
void queueEmpty();
void print_Front_Rear_Queue(int *);
void add(int,int*);
void delete(int*);

int main(){
	int i;
	int type;
	int temp;
	int queue[queue_size];
	for(i=0;i<queue_size;i++)	queue[i] = 0;

	while(1){
		queueFull();
		queueEmpty();

		printf("Insert(1)delete(2):");
		scanf("%d",&type);

		if(type == 1){
			scanf("%d",&temp);
			add(temp,queue);
			printf("insert number:%d\n",temp);
			print_Front_Rear_Queue(queue);
		}
		else if(type ==2 ){
			delete(queue);
			print_Front_Rear_Queue(queue);
		}
		else{
			printf("usage: please input number 1 or 2");
			exit(1);
		}
	}
	return 0;


}
void add(int add_num,int queue[queue_size]){
	if(rear==queue_size-1){
		rear = 0;
		queue[rear] = add_num;
	}
	else queue[++rear] = add_num;
}
void delete(int queue[queue_size]){
	if(front == queue_size-1){
		front = 0;
		queue[front] = 0;
	}
	queue[++front] = 0;
}
void queueEmpty(){
	if(rear == front)
		printf("queue is Empty\n");
}
void queueFull(){
	if(front == rear+1 ||
		(front == 0 && rear == queue_size-1))
		printf("queue is full\n");
}
void print_Front_Rear_Queue(int queue[queue_size]){
	int i;
	printf("Front = %d,Rear = %d\n", front,rear);
	printf("Queue:");
	for(i=0;i<queue_size;i++){
		printf("[");
		if(queue[i]!=0)
			printf("%d",queue[i]);
		printf("]");
	}		
	printf("\n");
}