/*
Напишите алгоритм и программу, меняющую местами m-й и
n-й элементы списка.
*/
#include <stdlib.h> /*EXIT_SUCCESS; malloc(); free()*/
#define DATATYPE double


/*Элемент списка*/
typedef struct ListMember ListMember;
struct ListMember {
	DATATYPE data;
	ListMember *next;
};

ListMember *ListMemberAllocate(DATATYPE const data){
	ListMember * el; /*Создаваемый элемент*/
	/*Выделение памяти под элемент, проверка*/
	el = (ListMember *)malloc(sizeof(ListMember));
	if (!el)
		return NULL;

	/*Выставление значений, возврат*/
	el->data = data;
	el->next = NULL;
	return el;
}


int main (void) {

	return EXIT_SUCCESS;
}
