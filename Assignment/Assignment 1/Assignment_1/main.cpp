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
   int index;
   int userInput = 0 , i = 0;
   int deallocatedIndex[21];
   int deallocatedInt = 0;

   for(i = 0;i < 21;i=i+1)
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

       // Access a Pointer
       if(userInput == 1)
       {
            system("clear");
            initHeader();
            index = menu1();

            if(deallocatedIndex[index] == index)
            {
                printf(cyan "**PT IS GONE ... re-Initialized**\n" reset);
                init_CHARPTR_ARRAY_index(&mainStruct ,index);
                deallocatedIndex[index] = 255;
            }

            while(1)
            {
                deallocatedInt = deallocatedInt % 20;
                menu1_2();
                scanf("%d",&userInput);
                // Exit
                if(userInput == 3)
                    break;
                // Delete all Char's
                else if(userInput == 2)
                {
                    if(deallocatedIndex[index] == 255)
                    {

                        deallocatedIndex[index] = index;
                        delete mainStruct.charArray[index];
                    }

                }
                // Print first 10 Chars
                else if(userInput == 1)
                    print_CHARPTR_ARRAY(&mainStruct , index);
            }
       }
       // List Deallocated Pointers
       else if( userInput == 2)
       {
           i = 0;
            printf(gray "deallocated memory (index):\n" reset);
            for(i = 0; i < 20 ; i = i + 1)
            {
                if(deallocatedIndex[i] != 255)
                    printf("%d " reset, deallocatedIndex[i]);
            }
            printf("\n");
       }
       // Deallocate All Pointer
       else if( userInput == 3)
       {
           deallocatedInt = 0;
           for(i = 0;i < 20;i=i+1)
           {
                if(deallocatedIndex[i] == i || i == 20){}
                else
                {
                    deallocatedIndex[i] = i;
                    delete mainStruct.charArray[i];
                }
           }
       }
       printf(reset "\n");
   }while(userInput != 4);
   printf(reset "Exiting...\n");
   return 0;
}
