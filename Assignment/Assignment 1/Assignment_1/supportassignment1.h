#ifndef SUPPORTASSIGNMENT1_H
#define SUPPORTASSIGNMENT1_H

struct CharAndInt
{
   //charArray is an array of 20 char*
   char* charArray[20];
   // intArray is an array of 20 int
   int intArray[20];
};
typedef struct CharAndInt myStruct;

void init_INT_ARRAY(myStruct *c)
{
    c->intArray[0] = 2700;
    int i = 0;
    for(i=0;i<20;i=i+1)
    {
        c->intArray[i+1] = 2 * c->intArray[i];
    }
}

void init_CHARPTR_ARRAY(myStruct* c)
{
    int i;
    for(i = 0; i < 20 ; i = i + 1)
    {
        c->charArray[i] = (char*)malloc(c->intArray[i]);
        c->charArray[i][0] = (rand()%25)+65;
    }
}

void print_INT_ARRAY(myStruct *c)
{
    int i;
    for(i=0;i<20;i=i+4)
    {
      printf("[" red "%X" reset "]: " blue "%10d  " reset,
             &(c->intArray[i]) , c->intArray[i]);
      printf("[" red "%X" reset "]: " blue "%10d  " reset,
             &(c->intArray[i+1]) , c->intArray[i+1]);
      printf("[" red "%X" reset "]: " blue "%10d  " reset,
             &(c->intArray[i+2]) , c->intArray[i+2]);
      printf("[" red "%X" reset "]: " blue "%10d\n" reset,
             &(c->intArray[i+3]) , c->intArray[i+3]);

    }
}

void print_CHARPTR_ARRAY(myStruct *c)
{
    int i;
    for(i=0;i<20;i=i+4)
    {
        printf(yellow "%2d" reset ":[" green "%9X" reset "]: " magenta "%1c  " reset,
              i + 1 , c->charArray[i] , c->charArray[i][0]);
        printf(yellow "%2d" reset ":[" green "%9X" reset "]: " magenta "%1c  " reset,
              i + 2 , &(c->charArray[i+1][0]) , c->charArray[i+1][0]);
        printf(yellow "%2d" reset ":[" green "%9X" reset "]: " magenta "%1c  " reset,
              i + 3 , &(c->charArray[i+2][0]) , c->charArray[i+2][0]);
        printf(yellow "%2d" reset ":[" green "%9X" reset "]: " magenta "%1c\n" reset,
              i + 4 , &(c->charArray[i+3][0]) , c->charArray[i+3][0]);
    }
}



void deallocateAllMemory(myStruct* c)
{
    int i;
    for(i=0;i<20;i=i+1)
    {
        free((*c).charArray[i]);
        c->charArray[i] = NULL;
    }
}

void deallocateAMemory(myStruct* c ,int i)
{
    free((*c).charArray[i]);
    c->charArray[i] = NULL;
}
#endif // SUPPORTASSIGNMENT1_H


