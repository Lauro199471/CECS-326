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
    int i , j;
    for(i = 0; i < 20 ; i = i + 1)
    {
        c->charArray[i] = (char*)malloc(c->intArray[i]);
        for(j = 0; j < c->intArray[i] ; j = j + 1)
        {
            c->charArray[i][j] = (rand()%25)+65;
        }

    }
}
void init_CHARPTR_ARRAY_index(myStruct* c , int index)
{
    int j;
    c->charArray[index] = (char*)malloc(c->intArray[index]);
    for(j = 0; j < c->intArray[index] ; j = j + 1)
    {
        c->charArray[index][j] = (rand()%25)+65;
    }
}

void print_CHARPTR_ARRAY(myStruct *c , int index)
{
    int i;
    printf("\n");
    //printf(reset "[" green "%15p" reset "]: " , c->charArray[index]);
    for(i=0;i<10;i=i+1)
    {
        //printf(magenta "%1c " reset, c->charArray[index][i]);
    }
    printf("\n");
}



void deallocateAllMemory(myStruct* c)
{
    int i;
    for(i=0;i<20;i=i+1)
    {
        //free((*c).charArray[i]);
        //delete (*c)->charArray[i];
        c->charArray[i] = NULL;
    }
}

void deallocateAMemory(myStruct* c ,int i)
{
    free((*c).charArray[i]);
    c->charArray[i] = NULL;
}

void deleteChar(myStruct* c ,int i)
{
    free((*c).charArray[i]);
    c->charArray[i] = NULL;
}
#endif // SUPPORTASSIGNMENT1_H


