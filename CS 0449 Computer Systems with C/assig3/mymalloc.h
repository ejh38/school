/* Zach Sadler
 * zps6@pitt.edu
 * Tu/Tu 11am
 * Project 3
 */

typedef struct Node Node;

struct Node {
	int size;
	short in_use;
	Node *next;
	Node *prev;
};

void *my_worstfit_malloc(int);
void my_free(void *ptr);
void print();