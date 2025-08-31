#ifndef API_H
#define API_H

#include <stddef.h>

/// Обобщенный интерфейс итератора
struct Iterator;

/// Исполнить функцию `func` на каждом элементе, который возвращает `iter`
void forEach(struct Iterator* iter, void (*func)(int));

/// Создать итератор, вызывающий функцию `func` на каждом элементе переданного итератора `iter`
struct Iterator* map(struct Iterator* iter, int (*func)(int));

/// Удалить итератор, полученный вызовом `map`
void deinitMap(struct Iterator*);

/// Односвязный список с элементами типа `int`
struct List;

/// Создать новый пустой список
struct List* initList();
/// Добавить элемент в голову списка, вернуть новый список
struct List* prepend(struct List* head, int item);
/// Очистить память под переданным списком
void deinitList(struct List* l);

/// Создать итератор по списку
struct Iterator* iterateList(struct List*);
/// Удалить переданный итератор по списку
void deinitListIterator(struct Iterator*);

#endif
