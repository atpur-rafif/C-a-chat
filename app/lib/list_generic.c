#include "./list_generic.h"

LIST FUN(createNew)(){
    return NULL;
};

LIST_MEMBER* FUN(getIndexAt)(LIST list, int idx){
    LIST_MEMBER* curr = list;
    for(int i = 0; i < idx; ++i){
        curr = curr->next;
    }
    return curr;
}

void FUN(insertAt)(LIST* list, int idx, TYPE value){
	LIST_MEMBER *new = malloc(sizeof(LIST_MEMBER));
	new->value = value;
	new->next = NULL;

	if(idx == 0){
        new->next = *list;
        *list = new;
    } else {
        LIST_MEMBER* at = FUN(getIndexAt)(*list, idx - 1);
        new->next = at->next;
        at->next = new;
    }
}

void FUN(deleteAt)(LIST* list, int idx){
    if(idx == 0){
        LIST_MEMBER* old = (*list);
        *list = old->next;
        free(old);
    } else {
        LIST_MEMBER* at = FUN(getIndexAt)(*list, idx - 1);
        LIST_MEMBER* target = at->next;
        at->next = target->next;
        free(target);
    }
}

#undef FUN