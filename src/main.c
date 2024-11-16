/*
Напишите алгоритм и программу, меняющую местами m-й и
n-й элементы списка.
*/
#include "list.h"
#include <assert.h> /*assert()*/
#include <stdint.h> /*INT32_MAX*/
#include <stdio.h>  /*printf()*/
#include <stdlib.h> /*EXIT_SUCCESS; malloc(); free()*/
#include <time.h>   /*time()*/

/*Счётчик созданных элементов*/
extern int memb_counter;

void PrintList_(ListMember const *const ptr, const int i) {
	if (!ptr)
		return;

	printf("list[%d] = %.2lf\n", i, ptr->data);
	PrintList_(ptr->next, i + 1);
}
static inline void PrintList(ListMember const *const ptr) {
	PrintList_(ptr, 0);
}

int main(void) {
	// srand((unsigned int)time(NULL));

	const int size = 16;
	DATATYPE array[size];
	for (int i = 0; i < size; ++i) {
		array[i] = (DATATYPE)i;
		// printf("array[%d] = %.2lf\n", i, array[i]);
	}

	ListMember *head = CreateListFromArray(array, size);
	if (!head /*==NULL*/) {
		perror("CreateListFromArray()");
		return EXIT_FAILURE;
	}

	RemoveNthElement(&head, 3);
	RemoveNthElement(&head, 0);
	RemoveNthElement(&head, 6);

	InsertMemberAsNth(&head, 2, 13.37);
	InsertMemberAsNth(&head, 0, 9.11);

	PrintList(head);
	ListMemberRemoveList(&head);

	assert(head == NULL);
	if (memb_counter != 0){
		fprintf(stderr, "FAIL: memb_counter = %d\n", memb_counter); 
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
