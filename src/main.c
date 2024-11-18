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

#define size 16
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

	/*Выдадут ошибку, не сделают ничего со списком*/
	if(!InsertMemberAsNth(&head, -1, 9.11)){
		fprintf(stderr, "Не удалось вставить элемент по индексу %d!\n", -1);
	}
	if(!InsertMemberAsNth(&head, 100, 9.11)){
		fprintf(stderr, "Не удалось вставить элемент по индексу %d!\n", 100);
	}

	if(ListMemberSwapMembers(&head, 1, 1))
		fprintf(stderr, "Не удалось переставить элементы местами!\n");

	PrintList(head);
	ListMemberRemoveList(&head);

	/*Не выполнит ничего*/
	ListMemberRemoveList(&head);

	assert(head == NULL);
	return EXIT_SUCCESS;
}
