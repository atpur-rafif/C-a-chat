#include <stdio.h>

typedef struct Fraction{
    int numerator;
    int denominator;
} Fraction;

#include "./lib/list_generic.h"

#undef TYPE
#define TYPE Fraction
#include "./lib/list_generic.h"


int main(){
    Listint a;
    ListFraction b;
}