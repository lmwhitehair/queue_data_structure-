#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/**
* @author: Logan Whitehair
* @brief: simple implementation of a FIFO queue structure in C
*/



/**
 * @brief: node structure used to represent individual nodes within a queue
*/
typedef struct queue_node {

	int data;
	struct queue_node* nextPtr; // pointer to next node in the queue 

} node;

/**
 * @brief: queue structure
*/
typedef struct queue_ptr {

	struct queue_node* frontPtr;
	struct queue_node* rearPtr;
	int max_size; // maximum allowed size, this param is configured within the create_queue function 
	int cur_size; // dynamic size of each queue instance 

} queue;

queue* create_queue(int max_size);
void enqueue(queue* queuePtr, int data);
int dequeue(queue* queuePtr);
int is_empty(queue* queuePtr);
void print_queue(queue* queuePtr);


/**
 * @brief: main function
 * @return: status code
*/
int main(void) {

	queue* queuePtr = create_queue(5);

	enqueue(queuePtr, 1);
	enqueue(queuePtr, 2);
	enqueue(queuePtr, 3);
	enqueue(queuePtr, 4);
	enqueue(queuePtr, 5);
	enqueue(queuePtr, 6);

	printf("\nDequeued item: %d\n", dequeue(queuePtr));
	printf("Dequeued item: %d\n", dequeue(queuePtr));

	enqueue(queuePtr, 6);

	puts("\nCurrent queue: ");
	print_queue(queuePtr);

	return 0;
}

/**
 * @brief: function to initialize new queue structure
 * @param: max_size - used to set the maximum size of the queue structure
 * @return: returns initialized structure
*/
queue* create_queue(int max_size) {

	queue* queuePtr = malloc(sizeof(queue)); // allocate memory for new queue structure 
	if (queuePtr == NULL) {

		puts("Could not allocate memory to initialize queue.");
		exit(1);

	}

	queuePtr->max_size = max_size; // initializing all values within the struct 
	queuePtr->cur_size = 0;
	queuePtr->frontPtr = NULL;
	queuePtr->rearPtr = NULL;

	return queuePtr;

}

/**
 * @brief: enqueue function that adds new nodes to the queue in FIFO behavior
 * @param: queuePtr - the queue structure that the node gets pushed onto
		   data - integer data that you want to store within the node
*/
void enqueue(queue* queuePtr, int data) {


	if (queuePtr == NULL) { // error check 

		puts("Invalid queue while enqueueing.");
		exit(1);

	}

	if (queuePtr->cur_size >= queuePtr->max_size) { // check if queue structure isn't larger than maximum size 

		printf("queue is full, could not add new node with data: %d\n", data);
		return;

	}

	node* nodePtr = (node*)malloc(sizeof(node)); // allocate memory for new node 
	if (nodePtr == NULL) {

		puts("Could not allocate memory for new node.");
		exit(1);

	}

	nodePtr->data = data; // initialize node data 
	nodePtr->nextPtr = NULL;

	if (queuePtr->rearPtr != NULL) { // if queue structure is not empty 

		queuePtr->rearPtr->nextPtr = nodePtr;
		queuePtr->rearPtr = nodePtr;
		queuePtr->cur_size = queuePtr->cur_size++;

	}
	else { // if queue structure is empty 

		queuePtr->frontPtr = nodePtr;
		queuePtr->rearPtr = nodePtr;
		queuePtr->cur_size = queuePtr->cur_size++;

	}
}

/**
 * @brief: dequeue function used to remove nodes from the queue in FIFO behavior
 * @param: queue structure that the node gets removed from
 * @return: data of the removed node
*/
int dequeue(queue* queuePtr) {

	if (is_empty(queuePtr)) { // if queue structure is empty

		puts("No items in queue.");
		exit(1);

	}


	int data = queuePtr->frontPtr->data; // store data node before removing 
	node* tempPtr = queuePtr->frontPtr; // store node before removing
	queuePtr->frontPtr = tempPtr->nextPtr; // pop front node 
	queuePtr->cur_size = queuePtr->cur_size--; // update size 


	if (queuePtr->frontPtr == NULL) {

		queuePtr->rearPtr = NULL;

	}

	free(tempPtr);
	tempPtr = NULL;

	return data;

}

/**
 * @brief: function to check if queue structure is empty
 * @param: queue structure
 * @return: 1 if TRUE 0 if FALSE
*/
int is_empty(queue* queuePtr) {

	if (queuePtr == NULL)
	{
		puts("Invalid queue.");
		exit(1);
	}

	return ((queuePtr->frontPtr == NULL) && (queuePtr->rearPtr == NULL));

}

/**
 * @brief: function to print the nodes within a queue
 * @param: queue structure
*/
void print_queue(queue* queuePtr) {

	if (queuePtr == NULL) {

		puts("Invalid queue.");
		exit(1);

	}

	node* curPtr = queuePtr->frontPtr;

	while (curPtr != NULL) { // loop through struct an print node data 

		printf("%d -> ", curPtr->data);
		curPtr = curPtr->nextPtr;

	}

}