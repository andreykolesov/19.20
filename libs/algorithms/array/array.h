#ifndef UNTITLED_ARRAY_H
#define UNTITLED_ARRAY_H

#include <stddef.h>

// ввод массива a размера n
void inputArray_(int a[], size_t n);

// вывод массива a размера n
void outputArray_(const int a[], size_t n);

// возвращает индекс первого вхождения элемента x
// в массиве a размера n при наличии, иначе n
size_t linearSearch_(const int a[], const size_t n, int x);

// возвращает индекс первого вхождения элемента x
// в отсортированном массиве а размера n при наличии, иначе n
size_t binarySearch_(const int a[], const size_t n, int x);

// возвращает индекс первого элемента равного или большего x
// в отсортированном массиве a размера n
// при отсутствии возвращает n
size_t binarySearchMoreOrEqual_(const int a[], const size_t n, int x);

// вставка элемента со значением value
// в массив а размера n на позицию pos
void insert_(int a[], size_t *n, size_t pos, int value);

// вставка элемента со значением value
// в конец массива a размера n
void append_(int a[], size_t *n, int value);

// удаление из массива a размера n элемента на позиции pos
// с сохранением порядка оставшихся элементов
void deleteByPosSaveOrder_(int a[], size_t *n, size_t pos);

// удаление из массива a размера n элемента на позиции pos
// без сохранения порядка оставшихся элементов
// размер массива a уменьшается на единицу
void deleteByPosUnsaveOrder_(int a[], size_t *n, size_t pos);

// возвращает истина, если все элементы массива а размера n
// удовлетворяют функции-предикату predicate
// иначе ложь
int all_(const int a[], size_t n, int (*predicate)(int));

// возвращает истина, если один элемент массива а размера n
// удовлетворяют функции-предикату predicate
// иначе ложь
int any_(const int a[], size_t n, int (*predicate)(int));

// применяет фукнцию-предикат predicate ко всем элементам массива source
// сохраняет результат в массив dest размера n
void forEach_(const int source[], int dest[], size_t n, int(*predicate)(int));

// возвращает количество элементов массива a размера n
// удовлетворяющих функции-предикату predicate
int countIf_(const int a[], size_t n, int(*predicate)(int));

// удаляет из массива a размера n все элементы, соответсвующие
// функции-предикату deletePredicate, записывает в n
// новый размер массива
void deleteIf_(int a[], size_t *n, int(*deletePredicate)(int));

#endif //UNTITLED_ARRAY_H
