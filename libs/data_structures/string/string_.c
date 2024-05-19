#include "string_.h"

char stringBuffer_[MAX_STRING_SIZE + 1];

BagOfWords _bag;
BagOfWords _bag2;

size_t strlen_(const char *begin) {
    char *end = begin;

    while (*end != '\0')
        end++;

    return end - begin;
}

char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;

    return begin;
}

char *findNonSpace(char *begin) {
    while (*begin != '\0' && isspace((unsigned char) *begin))
        begin++;

    return begin;
}

char *findSpace(char *begin) {
    while (*begin != '\0' && !isspace((unsigned char) *begin))
        begin++;

    return begin;
}

char *findNonSpaceReverse(char *r_begin, const char *r_end) {
    while (r_begin != r_end && isspace((unsigned char) *r_begin))
        r_begin--;

    return r_begin;
}

char *findSpaceReverse(char *r_begin, const char *r_end) {
    while (r_begin != r_end && !isspace((unsigned char) *r_begin))
        r_begin--;

    return r_begin;
}

int strcmp_(const char *lhs, const char *rhs) {
    while (*lhs != '\0' && *rhs != '\0' && *lhs == *rhs) {
        lhs++;
        rhs++;
    }

    return *(const unsigned char *) lhs - *(const unsigned char *) rhs;
}

char *copy(const char *begin_source, const char *end_source, char *begin_destination) {
    while (begin_source != end_source) {
        *begin_destination = *begin_source;
        ++begin_source;
        ++begin_destination;
    }
    return begin_destination;
}

char *copyIf(char *beginSource, const char *endSource, char *beginDestination, int (*f)(int)) {
    char *start = beginSource;

    while (start != endSource) {
        if (f(*start)) {
            *beginDestination = *start;
            beginDestination++;
        }

        start++;
    }

    return beginDestination;
}

char *copyIfReverse(char *r_beginSource, const char *r_endSource, char *beginDestination, int (*f)(int)) {
    char *start = r_beginSource;

    while (start != r_endSource) {
        if (f(*start)) {
            *beginDestination = *start;
            beginDestination++;
        }

        start--;
    }

    return beginDestination;
}

char *getEndOfString(char *s) {
    char *start = s;

    while (*start != '\0')
        start++;

    return start;
}

void assertString(const char *expected, char *got, char const *fileName, char const *funcName, int line) {
    if (strcmp_(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}

bool getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);

    if (*word->begin == '\0')
        return false;

    word->end = findSpace(word->begin);

    return true;
}

bool getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    if (word->begin == rend)
        return false;

    word->end = findNonSpaceReverse(rbegin, rend);

    word->begin = findSpaceReverse(rbegin, rend);

    word->begin = word->begin == rend ? word->begin : word->begin + 1;

    return true;
}

void freeString(char *s) {
    char *ptr = s;

    while (*ptr != '\0') {
        *ptr = '\0';
        ptr++;
    }
}

void printWord(WordDescriptor word) {
    while (word.begin != word.end) {
        printf("%c", *word.begin);
        word.begin++;
    }

    printf(" ");
}

bool isPalindrome(WordDescriptor *word) {
    char *begin = word->begin;
    char *end = word->end - 1;

    while (begin < end) {
        if (*begin != *end)
            return false;

        begin++;
        end--;
    }

    return true;
}

void wordDescriptorToString(WordDescriptor word, char *destination) {
    if (word.begin == NULL && word.end == NULL)
        return;

    while (word.begin <= word.end) {
        *destination = *word.begin;
        word.begin++;
        destination++;
    }

    *destination = '\0';
}

bool getWordWithoutSpace(char *begin_search, WordDescriptor *word) {
    word->begin = findNonSpace(begin_search);

    if (*word->begin == '\0')
        return false;

    word->end = findSpace(word->begin) - 1;

    return true;
}

void freeBag(BagOfWords *bag) {
    for (int i = 0; i < bag->size; i++) {
        bag->words[i].begin = NULL;
        bag->words[i].end = NULL;
    }

    bag->size = 0;
}

bool isWordEqual(WordDescriptor word1, WordDescriptor word2){
    char* begin1 = word1.begin;
    char* begin2 = word2.begin;

    while (begin1 < word1.end && begin2 < word2.end) {
        if (*begin1 != *begin2)
            return false;

        begin1++;
        begin2++;
    }

    if (word1.end - begin1 > 0 || word2.end - begin2 > 0)
        return false;

    return true;
}