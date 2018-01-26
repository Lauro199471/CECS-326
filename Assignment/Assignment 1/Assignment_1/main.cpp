#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"
#include "supportassignment1.h"

void initHeader(void)
{
    printf(yellow"\t  CECS 326\n"reset);
    printf(gray"\tLauro Cabral\n"reset);
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
