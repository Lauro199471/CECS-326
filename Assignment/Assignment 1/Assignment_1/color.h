#ifndef COLOR_H
#define COLOR_H

#define red     "\033[1;31m"
#define green   "\033[1;32m"
#define yellow  "\033[1;33m"
#define blue    "\033[1;34m"
#define purple  "\033[1;35m"
#define cyan    "\033[1;36m"
#define gray    "\033[1;37m"
#define bold    "\033[1;29m"
#define magenta "\033[1;35m"
#define reset   "\033[0m"

#endif // COLOR_H

/*

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
      // *(c->charArray + i) = ran;
    }
}

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




   // Char
   *x.charArray = 'A';
   *(x.charArray +1) = 'B';
   printf("x.charArray:  %d\n",  x.charArray);
   printf("&(x.charArray):  %d\n", &(x.charArray));
   printf("&(x.charArray):  %d\n", &(x.charArray));
   printf("*(x.charArray+0):    %d\n", *x.charArray);
   printf("*(x.charArray+1):    %d\n", *(x.charArray+1));
*/
