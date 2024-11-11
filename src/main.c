/*
Напишите алгоритм и программу, меняющую местами m-й и
n-й элементы списка.
*/
#include <stdio.h>  /*printf()*/
#include <stdlib.h> /*EXIT_SUCCESS; malloc(); free()*/
#include <time.h>   /*time()*/
#define DATATYPE double

/*Элемент списка*/
typedef struct ListMember ListMember;
struct ListMember {
	DATATYPE data;
	ListMember *next;
};

/*Создание элемента*/
ListMember *ListMemberAllocate(DATATYPE const data) {
	ListMember *el; /*Создаваемый элемент*/
	/*Выделение памяти под элемент, проверка*/
	el = (ListMember *)malloc(sizeof(ListMember));
	if (!el)
		return NULL;

	/*Выставление значений, возврат*/
	el->data = data;
	el->next = NULL;
	return el;
}

/*Вставка элемента в начало существующего списка.
 * Возврат указателя на вставленный элемент*/
ListMember *InsertMemberInBegin(ListMember **ptr, DATATYPE const data) {
	ListMember *memb = ListMemberAllocate(data);
	if (!memb /*==NULL*/)
		return NULL;
	memb->next = (*ptr);
	*ptr = memb;
	return memb;
}

/*Вставка элемента через n других
 Возврат указателя на вставленный элемент*/
ListMember *InsertMemberAfterN(ListMember **ptr, int const n,
			       DATATYPE const data) {
	return (n /*!=0*/) ? InsertMemberAfterN(ptr, n - 1, data)
			   : InsertMemberInBegin(ptr, data);
}

/*Удаление крайнего элемента*/
void Remove1stElement(ListMember **ptr) {
	ListMember *member = *ptr;
	if (!member /*==NULL*/)
		return;
	*ptr = member->next;
	free(member);
}

/*Удаление n-ного элемента*/
void RemoveNthElement(ListMember **ptr, int const n) {
	return (n /*!=0*/) ? RemoveNthElement(ptr, n - 1)
			   : Remove1stElement(ptr);
}

/*Удаление целого листа*/
void RemoveWholeList(ListMember **ptr) {
	while (*ptr)
		Remove1stElement(ptr);
}

void SwapNum(int *const a, int *const b) {
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

int GetRandNum(int a, int b) {
	if (a > b)
		SwapNum(&a, &b);

	return a + rand() % (++b - a);
}

int main(void) {
	srand((unsigned int)time(NULL));

	ListMember *head, /*Указатель на первый элемент*/
		*tail; /*Указатель на крайний элемент*/
	head = ListMemberAllocate((DATATYPE)GetRandNum(-10, 10));
	if (!head /*==NULL*/)
		return EXIT_FAILURE;
	tail = head;

	for (int i = 1; i < 100; ++i) {
		tail->next = ListMemberAllocate((DATATYPE)i);
		// tail->next = ListMemberAllocate((DATATYPE)GetRandNum(-10, 10));
		tail = tail->next;
	}

	while (head /*!=NULL*/) {
		printf("%.2lf\n", head->data);
		Remove1stElement(&head);
	}

	return EXIT_SUCCESS;
}
