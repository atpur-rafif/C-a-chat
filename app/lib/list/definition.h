#include "../macro.h"

#ifndef TYPE
#define TYPE int
#endif

#define LIST APPEND_MACRO(List, TYPE)
#define LIST_MEMBER APPEND_MACRO(LIST, Member)

#define LIST_FOR_EACH(list, name) \
    for(typeof(list) name = list; name != NULL; name = name->next)

typedef struct LIST_MEMBER {
    TYPE value;
    struct LIST_MEMBER* next;
} LIST_MEMBER;

typedef struct LIST_MEMBER* LIST;

LIST FUN(createNew)();
void FUN(insertAt)(LIST* list, int idx, TYPE value);
void FUN(deleteAt)(LIST* list, int idx);