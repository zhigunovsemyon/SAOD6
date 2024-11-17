#include "list.h"
#include <stdlib.h> /*malloc(); free()*/

int memb_counter = 0;
static void* Malloc(size_t const size){
	++memb_counter;
	return malloc(size);
}
static void Free(void *ptr){
	--memb_counter;
	free(ptr);
}
#define malloc Malloc
#define free Free

static ListMember **GotoNthElement(ListMember **ptr, int const n) {
	return (n /*!=0*/) ? GotoNthElement(&((*ptr)->next), n - 1) : ptr;
}

DATATYPE *ListMemberGetNthData(ListMember *ptr, int const n) {
	return &((*GotoNthElement(&ptr, n))->data);
}

/*Создание элемента*/
ListMember *ListMemberAllocate(DATATYPE const data, ListMember *const next) {
	ListMember *el; /*Создаваемый элемент*/
	/*Выделение памяти под элемент, проверка*/
	el = (ListMember *)malloc(sizeof(ListMember));
	if (!el)
		return NULL;

	/*Выставление значений, возврат*/
	el->data = data;
	el->next = next;
	return el;
}

/*Удаление некотрого элемента.
 * Возвращает указатель на следующий за удалённым элементом*/
ListMember *ListMemberRemove(ListMember *const el) {
	if (!el/*==NULL*/)
		return NULL;
	ListMember *const next = el->next;
	free(el);
	return next;
}

/*Вставка элемента через n других
 Возврат указателя на вставленный элемент*/
ListMember *InsertMemberAsNth(ListMember **ptr, int const n,
			       DATATYPE const data) {
	if (!(*ptr))
		return NULL;
	if (n /*!= 0*/)
		return InsertMemberAsNth(&((*ptr)->next), n - 1, data);

	*ptr = ListMemberAllocate(data, *ptr);
	return *ptr;
}

/*Удаление n-ного элемента*/
void RemoveNthElement(ListMember **ptr, int const n) {
	if (n < 0)
		return;

	if (n /*!= 0*/) {
		RemoveNthElement(&((*ptr)->next), n - 1);
		return;
	}

	*ptr = ListMemberRemove(*ptr);
}

ListMember * CreateListFromArray(DATATYPE const *const src, int const len){
	if (!(src && len))
		return NULL;

	ListMember *head = NULL;
	for (int i = len - 1; i >= 0; --i){
		/*Создание нового элемента, проверка*/
		head = ListMemberAllocate(src[i], head);
		if (!head /*==NULL*/) {
			ListMemberRemoveList(&head);
			break; //Выход из цикла перевыделений
		}
	}

	return head;
}

void ListMemberRemoveList(ListMember ** ptr){
	while((*ptr = ListMemberRemove(*ptr)));
}
