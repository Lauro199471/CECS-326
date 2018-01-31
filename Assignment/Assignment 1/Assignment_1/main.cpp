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

int menu1(void)
{
  int x;
  printf(red"Index: " reset);
  scanf ("%d", &x);
  return x;
}
void menu1_2(void)
{
    printf(red "(1)" reset " Print Char's"
           green "  (2)" reset " Delete All Chars"
           blue  "  (3)" reset " Return to Main Menu\n>> "
          );
}

int main()
{
   int index , index_2;
   int userInput = 0 , i = 0;
   int deallocatedIndex[20];
   int deallocatedInt = 0;

   for(i = 0;i < 20;i=i+1)
   {
       deallocatedIndex[i] = 255;
   }
    printf("\n");

   myStruct mainStruct;
   srand(time(0));

   init_INT_ARRAY(&mainStruct);
   init_CHARPTR_ARRAY(&mainStruct);

   do
   {
       initHeader();
       menuStart();
       scanf("%d",&userInput);

       if(userInput == 1)
       {
            system("clear");
            initHeader();
            index = menu1();
            while(1)
            {
                menu1_2();
                scanf("%d",&userInput);
                if(userInput == 3)
                    break;
                else if(userInput == 2)
                {
                    deallocatedIndex[deallocatedInt] = index;
                    deallocatedInt = deallocatedInt + 1;
                    delete mainStruct.charArray[index];
                }
                else if(userInput == 1)
                    print_CHARPTR_ARRAY(&mainStruct , index);
            }
       }
       else if( userInput == 2)
       {
           i = 0;
            printf(gray "deallocated memory (index):\n" reset);
            index_2 = deallocatedIndex[i];
            while(index_2 != 255)
            {
                printf("%d " reset, deallocatedIndex[i]);
                i = i + 1;
                index_2 = deallocatedIndex[i];
            }
             printf("\n");
       }
       else if( userInput == 3)
       {
           deallocatedInt = 0;
           for(i = 0;i < 20;i=i+1)
           {
               deallocatedIndex[i] = i;
               delete mainStruct.charArray[i];
           }
       }
       //scanf("%d",&userInput);
       //system("clear");
       printf(reset "\n");
   }while(userInput != 4);

   printf(reset "Exiting...\n");
   return 0;
}
