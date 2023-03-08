#include <stdint.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct PCB{
	int PID;
	
	struct PCB *next;
	struct PCB *prev;
};

//first node of the list
struct PCB *head = NULL;

//last node of the list
struct PCB *last = NULL;

//current node of list;
struct PCB *curr = NULL;

//check if list empty
uint32_t empty(){
	if(head == NULL) return 1;
	return 0;
}

//add new node to list
void addPCB(struct PCB *node){
	if(empty() == 1) {
		head = node;  
		last = node;
		head->prev = last; //always head's previous is last node
		last->next = head; //always last' next is head node
	}
	else{
		curr = last;
		last = node;
		last->prev = curr;
		last->next = head;
		head->prev = last;
		curr->next = last;	
	}
}

//remove PCB from list
void removePCB(struct PCB *node){
	if(node == head){
		head = node->next;
		head->next = (node->next)->next;
		head->prev = last;
		last->next = head;
	}
	else if(node == last){
		last = node->prev;	
		last->next = head;
		last->prev = (node->prev)->prev;
	}
	else{
		struct PCB *front = node->next;
		struct PCB *back = node->prev;
		
		front->prev = back;
		back->next = front;
	}
	
}

/* test main
int main(){
	int len;
	//printf("%s","hello");
	struct PCB *node1 = malloc(sizeof(struct PCB)) ;
	node1->PID = 1;
	addPCB(node1);
	
	struct PCB *node2 = malloc(sizeof(struct PCB)) ;
	node2->PID = 2;
	addPCB(node2);
	
	struct PCB *node3 = malloc(sizeof(struct PCB)) ;
	node3->PID = 3;
	addPCB(node3);
	
	
	
	printf("%i",head->PID);
	printf("%i",head->next->PID);
	printf("%i",head->prev->PID);
	
	removePCB(node2);
	printf("%c",'\n');
	
	printf("%i",head->PID);
	printf("%i",head->next->PID);
	printf("%i",last->PID);
	
	printf("%c",'\n');
	
	return 0;	
}*/
