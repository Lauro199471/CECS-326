#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"
#include "supportassignment1.h"

// single struct with an array of 20 pointers to 'char' and an integer array with 20 elements
void initHeader(void)
{
    printf(yellow"\t  CECS something with 3\n"reset);
    printf(gray"\t    Lauro Cabral\n"reset);
}

int main()
{

   myStruct mainStruct;
   srand(time(0));

   initHeader();

   init_INT_ARRAY(&mainStruct);
   print_INT_ARRAY(&mainStruct);

   printf("\n");

   init_CHARPTR_ARRAY(&mainStruct);
   print_CHARPTR_ARRAY(&mainStruct);


   printf(reset "DONE\n");

   return 0;
}
