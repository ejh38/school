/* Zach Sadler
 * zps6@pitt.edu
 * Tu/Tu 11am
 * Project 3
 */


#include <stdlib.h>
#include <stdio.h>
#include "mymalloc.h"


Node *first = NULL;
Node *last = NULL;
Node *temp;
Node *curr;
Node *to_use;
Node *to_free;

void *my_worstfit_malloc(int size)
{
	//print();

	short biggest_size = 0; 		// we'll use this to track where we can fit their allocation
	int to_return = 0;					// the return address we give, if not sbrk'ing
	/* Case one: If it's the first link, then just add it on
	 */
	if (first == NULL && last == NULL) {
		temp = (Node *)(sbrk(sizeof(Node)));		// make a new Node at the end
		
		temp -> size = size;		// set the node's size to what they want
		temp -> in_use = 1;			// it's in use
		temp -> next = NULL;		// it's next and prev are both NULL
		temp -> prev = NULL;

		first = temp;						// then hook up first
		last = temp;						// and last

	//	printf("We just set the first node!\n");
		return (void *)(sbrk(size));		// then return back their pointer
	}

	// If it's not the first node, then we need to look through the list.
	// Look through the nodes we've already made, and find the worst fit
	for (curr = first; curr != NULL; curr = curr -> next) {
		if (curr -> in_use == 0) {						// if we get a free one
			if ((curr -> size) > biggest_size) {		// and it's size is the biggest yet
				biggest_size = curr -> size;				// then store it's size
				to_use = curr;										// and the node!
			}		// skip any nodes that won't fit
		}			// skip any in_use nodes
	}				// and stop when we get to the end

	// So at this point, biggest_size contains the size of the largest free node
	// and to_use points to that node

	/* Case two: biggest_size can't accomodate size.
	 *					 So we need to make a new node at the end and return that
	 */
	if (biggest_size < size) {
		temp = (Node *)(sbrk(sizeof(Node)));		// make a new Node at the end
		
		temp -> size = size;		// set the node's size to what they want
		temp -> in_use = 1;			// it's in use
		temp -> next = NULL;		// its next is NULL, since it's now the end
		temp -> prev = last;		// its prev is last, since it's now the end
		(temp -> prev) -> next = temp;

		last = temp;						// and point last to this new node

//		printf("We just had to make a new node at the end, since we couldn't accomodate.\n");
		return (void *)(sbrk(size));		// then return back their pointer
	}

	/* Case three: biggest_size CAN accomodate size, but we don't need to split.
	 *						 This means that we can fit size, but can't fit another
	 *						 free node (with at least 1 byte size) in the leftover space. 
	 *						 This is internal fragmentation.
	 */
	 if (biggest_size >= size && (biggest_size < size + sizeof(Node) + 1)) {
	 	temp = to_use;
		temp -> in_use = 1;			// it's in use

		to_return = temp;
		to_return += sizeof(Node);
//		printf("We just fit a node between two other nodes, but didn't have to split.\n");
		return (void *)(to_return);  // we return the address they can work with
	 }

	/* Case four: biggest_size CAN accomodate size + sizeof(Node) + 1.
	 *						This means we do need to split, and make a brand new node.
	 *						This is external fragmentation.
	 */
	 if (biggest_size >= size + sizeof(Node) + 1) {
	 	Node *split; 

	 	temp = to_use;				// set temp to the one we found
	 	temp -> in_use = 1;		// set it to in use
	 	temp -> size = size;	// and give it the size they asked for
	 	
	 	split = temp;
	 	split += 1;
	 	split = (Node *)(split + sizeof(temp -> size));

	 	if (temp == last) {
	 		last = split;
	 	}
	 	// now we'll deal with the new node, and use curr to help us
	 	split -> size = biggest_size - size - sizeof(Node); // give curr the leftovers
	 	split -> in_use = 0;						// set it to free
	 	split -> prev = temp;					// set it's previous
	 	split -> next = temp -> next;	// set it's next to temp's old next

	 	if (split -> next != NULL) {
		 	(split -> next) -> prev = split; 
		}
	 	
	 	temp -> next = split;					// then change temp's next to the new one

	 	to_return = temp;
		to_return += sizeof(Node);

//		printf("I'm giving you address 0x%x \n", to_return);
//		printf("I had to split\n");
	 	return (void *)(to_return);	// return a workable address
	 }


//	 printf("\n**\n**\n**Oh no, we made it here and ran out of cases!! This shouldn't happen!\n**\n**\n\a\a\a\a\a\a\a");
	 return (void *)(sbrk(size + sizeof(Node)) + sizeof(Node));

}

void my_free(void *ptr)
{
	print();

	to_free = (Node *)(ptr - sizeof(Node));
	to_free -> in_use = 0;						// it's no longer in use

	// for conveience sake, make shorthand to the right and left nodes
	Node *right = NULL;
	Node *left = NULL;
	if (to_free -> next != NULL) {
		right = to_free -> next;
	}
	if (to_free -> prev != NULL) {
		left = to_free -> prev;
	}

	/* Case 3728: This is the end of the world
	 */
	if (first == last && right == NULL && left == NULL) {
//		printf("Getting rid of the only node ever created\n");
		sbrk(-((first -> size) + sizeof(Node)));

		return;
	}

	/* Case 1: We're freeing the only in use node, with both sides free
	 */
	if (left == first && right == last && (left -> in_use == 0) && (right -> in_use == 0)) {
		first = NULL;
		last = NULL;

		sbrk(-((to_free -> size) + (left -> size) + (right -> size) + 3*sizeof(Node)));
//		printf("We just freed the one and only node, with empties on both sides!\n");
		
		return;
	}

	/* Case 2: We're freeing the only in use node, with free on the right 
	 */
	if (to_free == first && right == last && (right -> in_use == 0)) {
		first = NULL;
		last = NULL;

		sbrk(-((to_free -> size) + (right -> size) + 2*sizeof(Node)));
//		printf("We just freed the one and only node, with empty on right!\n");
		
		return;
	} 

	/* Case 3: We're freeing the only in use node, with free on the left 
	 */
	if (to_free == last && left == first && (left -> in_use == 0)) {
		first = NULL;
		last = NULL;

		sbrk(-((to_free -> size) + (left -> size) + 2*sizeof(Node)));
//		printf("We just freed the one and only node, with empty on left!\n");
		return;
	}

	/* Case 4: We're freeing the last node, and not coalescing
	 */
	if (to_free == last && (left -> in_use) == 1) {
//		printf("We just freed the last node and didn't coalesce.\n");

		return;
	}

	/* Case 4: We're freeing the last node, and coalescing right
	 */
	if (to_free == last && (left -> in_use) == 0) {
		to_free -> size = (to_free -> size) + (left -> size) + sizeof(Node);
		to_free -> prev = (left -> prev);
		(left -> prev) -> next = to_free;


//		printf("We just freed the last node and coalesced.\n");
		return;
	}

	/* Case 5: We're freeing the first node, and coalescing left
	 */
	if (to_free == first && (right -> in_use) == 0) {
		to_free -> size = (to_free -> size) + (right -> size) + sizeof(Node);
		to_free -> next = (right -> next);
		(left -> next) -> prev = to_free;


//		printf("We just freed the last node and coalesced.\n");
		return;
	}

	

	/* Case 5: We're freeing the first node, and not coalescing 
	 */
	if (to_free == first && right -> in_use == 1) {
//	 	printf("We just freed the first node and didn't coalesce.\n");

	 	return;
	}

	/* Case 10: We're freeing, and coalescing on both 
	 */
	if (right -> in_use == 0 && left -> in_use == 0) {
		to_free -> size = (to_free -> size) + (left -> size) + (right -> size) + 2*sizeof(Node);
		to_free -> prev = left -> prev;
		to_free -> next = right -> next;

		if (left == first) {	
//			printf("CHANGED THE VALUE OF FIRST\n");
			first = to_free;
		}
		else {
			(left -> prev) -> next = to_free;
		}

		if (right == last) {	
//			printf("CHANGED THE VALUE OF LAST\n");
			last = to_free;
		}
		else {
			(right -> next) -> prev = to_free;
		}

//		printf("We just freed a node and coalesced on both sides.\n");
		return;
	}
	 

	/* Case 6: We're freeing the second to last, and coalescing on right 
	 */
	if (right -> in_use == 0 && right == last) {

		to_free -> size = (to_free -> size) + (right -> size) + sizeof(Node); 
		to_free -> next = right -> next;
		
		last = to_free;

//		printf("We just freed the second to last node and coalesced right.\n");
		return;
	}

	/* Case 7: We're freeing the second to first, and coalescing on left 
	 */
	if (left -> in_use == 0 && left == first) {

		to_free -> size = (to_free -> size) + (left -> size) + sizeof(Node); 
		to_free -> prev = left -> prev;
		
		first = to_free;

//		printf("We just freed the second to first node and coalesced left.\n");
		return;
	}

	/* Case 8: We're freeing a node, and coalescing on left 
	 */
	if (left -> in_use == 0) {

		to_free -> size = (to_free -> size) + (left -> size) + sizeof(Node); 
		to_free -> prev = left -> prev;

		(to_free -> prev) -> next = to_free; 

//		printf("We just freed a node and coalesced left.\n");
		return;
	}

	/* Case 9: We're freeing a node, and coalescing on right 
	 */
	if (right -> in_use == 0) {

		to_free -> size = (to_free -> size) + (right -> size) + sizeof(Node); 
		to_free -> next = right -> next;

		(to_free -> next) -> prev = to_free; 
		
//		printf("We just freed a node and coalesced right.\n");
		return;
	}

//	printf ("WE DIDNT DO ANYTHING\n");
	return;
}

void print()
{
	if(first!=last){
	
		curr= last;
//		printf("back to front:\n");

		while(curr!=first){
//			printf("size: %d ",curr->size);
//			printf("in_use: %d\n",curr->in_use);
			curr = curr->prev;
		}
//		printf("size: %d ",curr->size);
//		printf("in_use: %d\n",curr->in_use);
/*
		printf("\n\nfront to back:\n");
		
		curr= first;
		while(curr!=NULL){
			printf("size: %d\n",curr->size);
			printf("in_use: %d\n",curr->in_use);
			curr = curr->next;
		}
		*/
	}
		return;
}
