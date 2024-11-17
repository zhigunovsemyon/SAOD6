#include "list.h"
#include <stdlib.h> /*malloc(); free()*/

int memb_counter = 0;
void* Malloc(size_t const size){
	++memb_counter;
	return malloc(size);
}
void Free(void *ptr){
	--memb_counter;
	free(ptr);
}
#define malloc Malloc
#define free Free

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

	ListMember *const tail = ListMemberAllocate(src[len - 1], NULL);
	if(!tail)
		return NULL;

	ListMember *head = tail;
	for (int i = len - 2; i >= 0; --i){
		head = ListMemberAllocate(src[i], head);
		// assert(head != NULL); //Заменить на "деструктор"	
	}

	return head;
}

void ListMemberRemoveList(ListMember ** ptr){
	while((*ptr = ListMemberRemove(*ptr)));
}
