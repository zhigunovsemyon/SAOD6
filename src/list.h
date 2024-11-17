/*Используемый тип данных*/
#define DATATYPE double

/*Элемент списка*/
typedef struct ListMember ListMember;
struct ListMember {
	DATATYPE data;
	ListMember *next;
};

/*Создание элемента со значением data и указывающий на следующий элемент next*/
ListMember *ListMemberAllocate(DATATYPE const data, ListMember *const next);

/*Удаление некотрого элемента.
 * Возвращает указатель на следующий за удалённым элементом*/
ListMember *ListMemberRemove(ListMember *const el);

/*Вставка элемента через n других
 Возврат указателя на вставленный элемент*/
ListMember *InsertMemberAsNth(ListMember **ptr, int const n,
			       DATATYPE const data);

/*Удаление n-ного элемента*/
void RemoveNthElement(ListMember **ptr, int const n);

/*Создание списка из переданного массива известного размера*/
ListMember *CreateListFromArray(DATATYPE const *const src, int const len);

/*Удаление всего списка*/
void ListMemberRemoveList(ListMember **ptr);

/*Доступ к данным n-ного элемента списка ptr*/
DATATYPE *ListMemberGetNthData(ListMember *ptr, int const n);

/*Меняет местами m-й и n-й элементы списка.
Возвращает 0 при успешной перестановке, 1 при неудаче*/
int ListMemberSwapMembers(ListMember **ptr, int m, int n);