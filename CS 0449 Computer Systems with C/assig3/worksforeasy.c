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
	/* from class notes:
	 * traverse linked list
	 * find worst fit
	 * split (so it's node and size on one side and the rest on the other)
	 * create 2 nodes (one for the curr, and one for the next (that's free))
	 * in struct, track how much they got
	 */

	short biggest_size = 0; 		// we'll use this to track where we can fit their allocation

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

		printf("We just set the first node!\n");
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

		printf("We just had to make a new node at the end, since we couldn't accomodate.\n");
		return (void *)(sbrk(size));		// then return back their pointer
	}

	/* Case three: biggest_size CAN accomodate size, but we don't need to split.
	 *						 This means that we can fit size, but can't fit another
	 *						 free node (with at least 1 byte size) in the leftover space. 
	 *						 This is internal fragmentation.
	 */
	 if (biggest_size < size + sizeof(Node) + 1) {
	 	temp = to_use;
		temp -> in_use = 1;			// it's in use

		printf("We just fit a node between two other nodes, but didn't have to split.\n");
		return (void *)(&temp + sizeof(Node));  // we return the address they can work with
	 }

	/* Case four: biggest_size CAN accomodate size + sizeof(Node) + 1.
	 *						This means we do need to split, and make a brand new node.
	 *						This is external fragmentation.
	 */
	 if (biggest_size >= size + sizeof(Node) + 1) {
	 	temp = to_use;				// set temp to the one we found
	 	temp -> in_use = 1;		// set it to in use
	 	temp -> size = size;	// and give it the size they asked for

	 	// now we'll deal with the new node, and use curr to help us
	 	curr -> size = biggest_size - size; // give curr the leftovers
	 	curr -> in_use = 0;						// set it to free
	 	curr -> prev = temp;					// set it's previous
	 	curr -> next = temp -> next;	// set it's next to temp's old next

	 	temp -> next = curr;					// then change temp's next to the new one

	 	return (void *)(&temp + sizeof(Node));	// return a workable address
	 }


	 printf("\n**\n**\n**Oh no, we made it here and ran out of cases!! This shouldn't happen!\n**\n**\n\a\a\a\a\a\a\a");
	 return (void *)(sbrk(size + sizeof(Node)) + sizeof(Node));

}

void my_free(void *ptr)
{
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
	
	/* Case one: We're freeing the only node.
	 *					 We need to reset first and last, then move sbrk back. 
	 *					THIS IS WRONGGGGGGSGSGSGSYGDYSDGSDGSGHDGSD
	 */
	if (to_free == first && right == last) {
		first = NULL;
		last = NULL;

		sbrk(-((to_free -> size) + 2*sizeof(Node) + (right -> size)));
		return;
	}

	/* Case two: We're freeing the last node and not coalescing left
	 *					 We need to reset the last node.
	 */
	if (to_free == last && ((to_free -> prev) -> in_use) != 0) {

		printf("We just freed the last node and didn't coalesce.\n");

		return;
	}


	/* Case three: We're freeing the first node and not coalescing right
	 *						 We need to reset the first node.
	 */
	if (to_free == first && (to_free -> next) -> in_use != 0) {

	 	printf("We just freed the first node and didn't coalesce.\n");

	 	return;
	}



	 /* Case four: We're freeing the last node and coalescing right.
	  *						 We need to add the size of the node we're coalescing,
	  *						 adjust our next to the correct position,
	  *						 and set last
	  */
	if (right -> in_use == 0 && right == last) {

		to_free -> size = (to_free -> size) + (right -> size) + sizeof(Node); 
		to_free -> next = right -> next;
		
		last = to_free;

		printf("We just freed a node and coalesced right.\n");
		return;
	}

	if (right -> in_use == 0 && right != last) {


	}


	/* Case three: We're freeing a node and coalescing left and right.
	 *						 We need to make a single, triple chunk node.
	 */
	if (((to_free -> prev) -> in_use == 0) && (((to_free) -> next) -> in_use == 0)) {
		Node *left = to_free -> prev;
		Node *right = to_free -> next;

		left -> next = right -> next;		// set the next node

		printf("NOT HERE\n");

		return;
	} 








/*





//	printf("to_free's size: %d, in_use: %d\n", to_free->size, to_free->in_use);
	to_free -> in_use = 0;								// it's no longer in use

	// this is coalescing to the right
	// loop through the next nodes, starting to the next of to_free, while they exist
	for (curr = to_free -> next; curr != NULL; curr = curr -> next) {
		if (curr -> in_use == 0) {						// if it's a free space
			to_free -> size += curr -> size + sizeof(Node);		// add their sizes
		}
		else {
			break;		// otherwise stop looking
		}
	}
	to_free -> next = curr;		// and now we have the next correctly set

	// now coalesce to the left
	for (curr = to_free -> prev; curr != NULL; curr = curr -> prev) {
		if (curr -> in_use == 0) {	// if it's a free space
			to_free -> size += curr -> size + sizeof(Node);	// add their sizes
		}
		else {
			break;		// otherwise keep looking
		}
		curr -> next = to_free;
	}

*/
	return;
}

void print()
{
	if(first!=last){
	
		curr= last;
		printf("back to front\n");

		while(curr!=first){
			printf("size: %d\n",curr->size);
			printf("in_use: %d\n",curr->in_use);
			curr = curr->prev;
		}

		printf("size: %d\n",curr->size);
		printf("in_use: %d\n",curr->in_use);
		printf("front to back\n\n\n");
		
		curr= first;
		while(curr!=NULL){
			printf("size: %d\n",curr->size);
			printf("in_use: %d\n",curr->in_use);
			curr = curr->next;
		}
	}
		return;
}
