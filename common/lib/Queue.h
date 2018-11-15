#ifndef QUEUE_H
#define QUEUE_H

struct Queue {
	int front, rear;
	unsigned capacity, size;
	int* array;
};

struct Queue* createQueue(unsigned capacity);
int isFull(struct Queue* queue);
int isEmpty(struct Queue* queue);
void enqueue(struct Queue* queue, int item);
int dequeue(struct Queue* queue);
int front(struct Queue* queue);
int rear(struct Queue* queue);
int get_average(struct Queue* queue);

#endif
