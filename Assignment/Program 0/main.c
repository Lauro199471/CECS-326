#include <stdio.h>
#include <stdlib.h>
#include<time.h>

// single struct with an array of 20 pointers to 'char' and an integer array with 20 elements
struct CharAndInt
{
   char* charArray[20];
   int intArray[20];
};
typedef struct CharAndInt STRUCTLAB0;

/* prototype */
void initINTARRAY(STRUCTLAB0 *c);

int main()
{
   int i = 0;
   // Use current time as seed for random generator
    srand(time(0));

   STRUCTLAB0 x;
   initINTARRAY(&x);

   printf("Bytes: %d\n" , sizeof(x.charArray));
   printf("Bytes: %d\n" , sizeof(x.intArray));
   printf("Bytes: %d\n" , sizeof(x));
   printf("Bytes: %d\n" , sizeof(char*));

   for(i=0;i<20;i=i+1)
   {
     printf("x.intArray+%d: %d\n",i+1,x.intArray+i);
   }

   for(i=0;i<20;i=i+1)
   {
     printf("*(x.intArray+%d): %d\n",i+1,*(x.intArray+i));
   }


   for(i=0;i<20;i=i+1)
   {
    printf("*(x.charArray+%d): %c\n", i,*(x.charArray+i));
   }



   /*
   // Char
   *x.charArray = 'A';
   *(x.charArray +1) = 'B';
   printf("x.charArray:  %d\n",  x.charArray);
   printf("&(x.charArray):  %d\n", &(x.charArray));
   printf("&(x.charArray):  %d\n", &(x.charArray));
   printf("*(x.charArray+0):    %d\n", *x.charArray);
   printf("*(x.charArray+1):    %d\n", *(x.charArray+1));
   */
   return 0;
}

void initINTARRAY(STRUCTLAB0 *c)
{
    int i = 0 , ran = 0;
    c->intArray[0] = 2700;
    for(i=0;i<20;i=i+1)
    {
       c->intArray[i+1] = 2 * c->intArray[i];
    }
    //rand() % (max_number + 1 - minimum_number) + minimum_number

    *(c->charArray) = i;

    for(i=0;i<20;i=i+1)
    {
       ran = (rand()%25)+65;
       *(c->charArray + i) = ran;
    }
}

