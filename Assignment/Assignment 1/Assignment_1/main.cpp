#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "color.h"
#include "supportassignment1.h"

void initHeader(void)
{
    printf(yellow "\t\t\t\t\t\t  CECS 326\n" reset);
    printf(gray "\t\t\t\t\t\tLauro Cabral\n" reset);
}
void menuStart()
{
  printf(red "(1)" reset " Access a Pointer"
         green "  (2)" reset " List Deallocated Memory(Index)"
         blue  "  (3)" reset " Deallocate All Memory"
         yellow "  (4)" reset " Exit Program\n>> ");
}

int menu1()
{
  int x;
  printf(red"Index: " reset);
  scanf ("%d", x);
  return x;
}
void menu1_2(void)
{
    printf(red "(1)" reset " Print Char's"
           green "  (2)" reset " Delete All Chars"
           blue  "  (3)" reset " Return to Main Menu\n>>"
          );
}

int main()
{
   int* exp;
   int i , index;
   int userInput = 0;

   myStruct mainStruct;
   srand(time(0));

   init_INT_ARRAY(&mainStruct);

   while(userInput != 4)
   {
       system("clear");
       initHeader();
       menuStart();
       scanf ("%d",&userInput);

       if(userInput == 1)
       {
            system("clear");
            initHeader();
            index = menu1();
            userInput = 0;
            while(userInput != 3)
            {
                menu1_2();
                scanf ("%d",&userInput);
                if(userInput == 3)
                    break;
                if(userInput == 2)
                    deallocateAMemory(&mainStruct , index);
                if(userInput == 1)
                    print_CHARPTR_ARRAY(&mainStruct);
            }
       }
    }












   //////////////////////////////////////////////////////////////
   /*
   print_INT_ARRAY(&mainStruct);

   printf("\n");

   init_CHARPTR_ARRAY(&mainStruct);
   print_CHARPTR_ARRAY_HEAP(&mainStruct);

   printf("\n");
   //deallocateAllMemory(&mainStruct);
     deallocateAMemory(&mainStruct , 3);

   //system("clear");
   initHeader();

   if(mainStruct.charArray[3] == NULL)
   {
        printf(green "\nPass\n");
   }
   else
   {
        printf(red "\nNo Pass\n");
   }

   printf(reset "DONE\n");
   */
   printf(reset "\n");
   return 0;
}
