#include <stdio.h>

#define TYPE int
#define DEFINE_LIST_GENERIC_IMPLEMENTATION
#include "./lib/list/generic.h"

typedef struct Fraction{
    int numerator;
    int denominator;
} Fraction;

#define TYPE Fraction
#define DEFINE_LIST_GENERIC_IMPLEMENTATION
#include "./lib/list/generic.h"

int main(){
    Listint a = NULL;
    insertAt_int(&a, 0, 1);
    insertAt_int(&a, 0, 2);
    insertAt_int(&a, 0, 3);

    LIST_FOR_EACH(a, j){
        printf("%d\n", j->value);
        fflush(stdout);
    };

    ListFraction f = NULL;
    for(int i = 0; i < 10; ++i){
        insertAt_Fraction(&f, 0, (Fraction ){i + 1, i + 2});
    }


    LIST_FOR_EACH(f, frac){
        printf("%d %d\n", frac->value.denominator, frac->value.numerator);
    }
}