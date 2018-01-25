#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"

// single struct with an array of 20 pointers to 'char' and an integer array with 20 elements
struct CharAndInt
{
   char** charArray[20];
   int intArray[20];
};
typedef struct CharAndInt STRUCTLAB0;

/* prototype */
void initINTARRAY(STRUCTLAB0 *c);

int main()
{
   printf(yellow "\tCECS 326\n" reset);
   return 0;
}
