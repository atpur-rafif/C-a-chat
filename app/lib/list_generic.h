#include "./macro.h"
#include <stdlib.h>

#ifndef TYPE
#define TYPE int
#endif


#define LIST_MEMBER APPEND_MACRO(ListMember, TYPE)
#define LIST APPEND_MACRO(List, TYPE)

typedef struct LIST_MEMBER {
    TYPE value;
    struct LIST_MEMBER* next;
} LIST_MEMBER;

typedef struct LIST_MEMBER* LIST;

LIST FUN(createNew)();
void FUN(insertAt)(LIST* list, int idx, TYPE value);
void FUN(deleteAt)(LIST* list, int idx);