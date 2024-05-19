#ifndef UNTITLED9_STRING__H
#define UNTITLED9_STRING__H

#include <stdlib.h>
#include <ctype.h>
#include <memory.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__)

#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20

extern char stringBuffer_[MAX_STRING_SIZE + 1];

typedef struct WordDescriptor {
    char *begin; // позиция начала слова
    char *end; // позиция первого символа, после последнего символа слова
} WordDescriptor;

typedef struct BagOfWords {
    WordDescriptor words[MAX_N_WORDS_IN_STRING];
    size_t size;
} BagOfWords;

extern BagOfWords _bag;
extern BagOfWords _bag2;

// возвращает количество символов в строке (не считая ноль-символ)
size_t strlen_(const char *begin);

// возвращает указатель на первый элемент с кодом ch, расположенным на ленте памяти между адресами begin и end не
// включая end. Если символ не найден, возращается значение end.
char *find(char *begin, char *end, int ch);

// возвращает указатель на первый символ, отличный от пробельных, расположенный на ленте памяти,
// начиная с begin и заканчивая ноль-символом. Если символ не найден, возвращается адрес первого ноль-символа.
char *findNonSpace(char *begin);

// возвращает указатель на первый пробельный символ, расположенный на ленте памяти начиная с адреса begin
// или на первый ноль-символ.
char *findSpace(char *begin);

// возвращает указатель на первый справа символ, отличный от пробельных, расположенный на ленте памяти, начиная с
// rbegin (последний символ строки, за которым следует ноль-символ) и заканчивая rend
// (адрес символа перед началом строки). Если символ не найден, возвращается адрес rend.
char *findNonSpaceReverse(char *r_begin, const char *r_end);

// возвращает указатель на первый пробельный символ справа, расположенный на ленте памяти, начиная с rbegin и заканчивая
// rend. Если символ не найден, возвращается адрес rend.
char *findSpaceReverse(char *r_begin, const char *r_end);

// Функция возвращает отрицательное значение, если lhs располагается до rhs в лексикографическом
// порядке (как в словаре), значение 0, если lhs и rhs равны, иначе – положительное значение
int strcmp_(const char *lhs, const char *rhs);

// записывает по адресу beginDestination фрагмент памяти, начиная с адреса beginSource до endSource.
// Возвращает указатель на следующий свободный фрагмент памяти в destination.
char *copy(const char *beginSource, const char *endSource, char *beginDestination);

// записывает по адресу beginDestination элементы из фрагмента памяти начиная с beginSource заканчивая endSource,
// удовлетворяющие функции-предикату f. Функция возвращает указатель на
// следующий свободный для записи фрагмент в памяти.
char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int));

// записывает по адресу beginDestination элементы из фрагмента памяти начиная с r_beginSource заканчивая r_endSource,
// удовлетворяющие функции-предикату f. Функция возвращает значение beginDestination по окончанию работы функции
char *copyIfReverse(char *r_beginSource, const char *r_endSource, char *beginDestination, int (*f)(int));

// возвращает адрес последнего элемента строки
char *getEndOfString(char *s);

// новая функция тестирования, которая дает информацию о том, где именно произошла ошибка
void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line);

// возвращает true, если слово было считано, иначе false
bool getWord(char *beginSearch, WordDescriptor *word);

// считывает слова с конца строки
bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word);

// очищает строку, путем замены всех символов на \0
void freeString(char* s);

// производит вывод слова
void printWord(WordDescriptor word);

// проверяет слово на палиндром
bool isPalindrome(WordDescriptor *word);

// выполняет перевод WordDescriptor в char*
void wordDescriptorToString(WordDescriptor word, char *destination);

// возвращает true, если слово без пробела было считано, иначе false
bool getWordWithoutSpace(char *begin_search, WordDescriptor *word);

// очищает "мешок" со значениями
void freeBag(BagOfWords *bag);

// возвращает true, если слова равны, иначе false
bool isWordEqual(WordDescriptor word1, WordDescriptor word2);

#endif
