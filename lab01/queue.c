/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>

#include "harness.h"
#include "queue.h"

/*
   Create empty queue.
   Return NULL if could not allocate space.
   */
queue_t *q_new()
{
	/* Remember to handle the case if malloc returned NULL */
	queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
	if(queue!=NULL){
		queue->head=queue->tail=NULL;
		queue->size=0;
		return queue;
	}
	return NULL;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
	/* Remember to free the queue structue and list elements */
	if(q==NULL) return;

	list_ele_t *node=q->head;
	list_ele_t *tmp=NULL;
	while(node!=NULL){
		tmp = node->next;
		free(node);
		node = tmp;
	}
	free(q);
	return;
}

/*
   Attempt to insert element at head of queue.
   Return true if successful.
   Return false if q is NULL or could not allocate space.
   */
bool q_insert_head(queue_t *q, int v)
{
	/* What should you do if the q is NULL? */
	/* What if malloc returned NULL? */
	if(q==NULL) return false;

	list_ele_t *node = (list_ele_t *)malloc(sizeof(list_ele_t));
	if(node == NULL) return false;

	node->value = v;
	node->next = q->head;
	if(q->size == 0){
		q->head = q->tail = node;
	}else{
		q->head = node;
	}
	q->size++;

	return true;
}


/*
   Attempt to insert element at tail of queue.
   Return true if successful.
   Return false if q is NULL or could not allocate space.
   */
bool q_insert_tail(queue_t *q, int v)
{
	/* Remember: It should operate in O(1) time */
	if (q == NULL) return false;

	list_ele_t *node = (list_ele_t *)malloc(sizeof(list_ele_t));
	if(node == NULL) return false;

	node->value = v;
	node->next = NULL;
	if(q->size==0){
		q->head = q->tail = node;
	}else{
		q->tail->next = node;
		q->tail = node;
	}
	q->size++;
	return true;
}

/*
   Attempt to remove element from head of queue.
   Return true if successful.
   Return false if queue is NULL or empty.
   If vp non-NULL and element removed, store removed value at *vp.
   Any unused storage should be freed
   */
bool q_remove_head(queue_t *q, int *vp)
{
	if(q == NULL || q->size == 0 || vp == NULL) return false;

	q->size--;

	list_ele_t *node = q->head;
	*vp = node->value;
	if(q->size == 0){
		q->head = q->tail=NULL;
	}else{
		q->head = q->head->next; 
	}

	free(node);
	
	return true;
}

/*
   Return number of elements in queue.
   Return 0 if q is NULL or empty
   */
int q_size(queue_t *q)
{
	/* Remember: It should operate in O(1) time */
	if(q == NULL) return 0;
	return q->size;
}

/*
   Reverse elements in queue.

   Your implementation must not allocate or free any elements (e.g., by
   calling q_insert_head or q_remove_head).  Instead, it should modify
   the pointers in the existing data structure.
   */
void q_reverse(queue_t *q)
{
	if(q == NULL || q->size == 0 || q->size == 1) return;

	list_ele_t *n1 = q->head;
	list_ele_t *n2 = n1->next;
	list_ele_t *n3 = n2->next;
	while(n2 != NULL){
		n3 = n2->next;
		n2->next = n1;
		n1 = n2;
		n2 = n3;
	}
	q->head->next = NULL;
	q->tail = q->head;
	q->head = n1;
	return;
}

