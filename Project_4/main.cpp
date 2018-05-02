/*
 * Lauro Cabral
 * Project 4
 */
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <X11/Xlib.h>
#include "semaphore.h"

using namespace std;

#define running 1
#define U_DIV 827395609
#define V_DIV 962094883
const int BUFFSIZE = 4; // 4 Processes 


#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


enum {MUTEX , MUTUX_STATUS , MUTUX_U , MUTUX_V}; 

//==================================
//         U() and V()             =
//==================================
void U(void)
{
  sleep(1);
}
void V(void)
{
  sleep(2);
}

//==================================
//  Main Functions for Processes   =
//==================================
void parent_main(SEMAPHORE&  , char* , int* , bool* , bool*);
void child_1_main(SEMAPHORE& , char* , int* , bool* , bool*);
void child_2_main(SEMAPHORE& , char* , int* , bool* , bool*);
void child_3_main(SEMAPHORE& , char* , int* , bool* , bool*);
void child_4_main(SEMAPHORE& , char* , int* , bool* , bool*);


int main()
{  
  pid_t wpid=0;
  int status = 0;
  int shmid_queue_id , shmid_queue_ptr_id , U_V_status_id , U_V_sample_id;
  
  char* shmid_queue;
  int* shmid_queue_ptr;
  bool* U_V_status;
  bool* U_V_sample;
  
  shmid_queue_id = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(char), PERMS);
  shmid_queue_ptr_id = shmget(IPC_PRIVATE, sizeof(int), PERMS);
  U_V_status_id = shmget(IPC_PRIVATE, sizeof(bool), PERMS);
  U_V_sample_id = shmget(IPC_PRIVATE, sizeof(bool), PERMS);
  
  shmid_queue = (char *)shmat(shmid_queue_id, 0, SHM_RND);
  shmid_queue_ptr = (int *)shmat(shmid_queue_ptr_id, 0, SHM_RND);
  U_V_status = (bool *)shmat(U_V_status_id, 0, SHM_RND);
  U_V_sample = (bool *)shmat(U_V_sample_id, 0, SHM_RND);
          
  SEMAPHORE sem(2);
  sem.V(MUTEX);
  //sem.V(MUTEX);
  sem.V(MUTUX_STATUS);
  
  // Initilaze Shared Stuff
  *shmid_queue_ptr = 0;
  *U_V_status = true;
  *U_V_sample = true;

  if (fork())
  {
    // Parent Process
    if(fork())
    {
      // Parent Process
      if(fork())
      {
        // Parent Process
        if(fork())
        {
          // Parent Process
          cout << RESET << BOLDWHITE << "Parent\n" << RESET;
          parent_main(sem , shmid_queue , shmid_queue_ptr , U_V_status , U_V_sample);
        }
        else
        {
          // Child 4
          cout << BOLDYELLOW << "P4\n" << RESET;
          child_4_main(sem , shmid_queue , shmid_queue_ptr , U_V_status , U_V_sample);
          exit(0);
        }
      }
      else
      {
        // Child 3
        cout << BOLDGREEN << "P3\n" << RESET;
        child_3_main(sem , shmid_queue , shmid_queue_ptr , U_V_status , U_V_sample);
        exit(0);
      }
    }
    else
    {
      // Child 2
      cout << BOLDBLUE << "P2\n" << RESET;
      child_2_main(sem , shmid_queue , shmid_queue_ptr , U_V_status , U_V_sample);
      exit(0);
    }
  }
  else
  {
    // Child 1
    cout << BOLDRED << "P1\n" << RESET;
    child_1_main(sem , shmid_queue , shmid_queue_ptr , U_V_status , U_V_sample);
    exit(0);
  }
  
  // wait for child to finish
  while ((wpid = wait(&status)) > 0);
  return 0;
}

/*****************************************************
 *          Main Functions for Processes             * 
 *****************************************************/
void parent_main(SEMAPHORE &sem , char* shmid_queue , int* shmid_queue_ptr , bool* U_V_status , bool* U_V_sample )
{ 
  printf("=============START===============\n");
  bool flag;
  while(running)
  {
    sleep(2);
    printf( RESET "| %c | %c | %c | %c |  PTR: %d\n" , 
            *(shmid_queue+0),
            *(shmid_queue+1),
            *(shmid_queue+2),
            *(shmid_queue+3),
            *(shmid_queue_ptr)
            );
  }
}

void child_1_main(SEMAPHORE &sem , char* shmid_queue , int* shmid_queue_ptr , bool* U_V_status , bool* U_V_sample )
{
  while(running)
  {
    // Add to Queue & Incr PTR
    *(shmid_queue + ((*shmid_queue_ptr)%BUFFSIZE)) = '1'; 
    (*shmid_queue_ptr) = (*shmid_queue_ptr) + 1;
    printf( BOLDRED "\tP1 Added to queue\n");
    
    // Check if Top
    while(*(shmid_queue) != '1');
    
    //===================================================
    //               Start Critical Section
    //===================================================
    sem.P(MUTEX);
      sleep(3);
      if(*U_V_status == true && *U_V_sample == true)
      {
        *U_V_sample = false;
        *U_V_status = false;
        // Shift from queue & Decr PTR
        *(shmid_queue) = *(shmid_queue + 1);
        *(shmid_queue + 1) = *(shmid_queue + 2);
        *(shmid_queue + 2) = *(shmid_queue + 3);
        (*shmid_queue_ptr) = (*shmid_queue_ptr) - 1;
        
        printf( BOLDRED "\tP1 RUNNING A" RESET);
        U();
        *U_V_status = true;
      }
      else
      {
        *U_V_sample = true;
        // Remove from queue & Decr PTR
        *(shmid_queue) = *(shmid_queue + 1);
        *(shmid_queue + 1) = *(shmid_queue + 2);
        *(shmid_queue + 2) = *(shmid_queue + 3);
        (*shmid_queue_ptr) = (*shmid_queue_ptr) - 1;
        
        printf( BOLDRED "\tP1 RUNNING B" RESET );
        V();
      }
      printf( BOLDRED "\n\tP1 DONE\n" RESET );
    sem.V(MUTEX);
    //===================================================
    //                End Critical Section
    //=================================================== 
  }
}

void child_2_main(SEMAPHORE &sem , char* shmid_queue , int* shmid_queue_ptr , bool* U_V_status , bool* U_V_sample )
{  
  sleep(2);
  while(running)
  {
    // Add to Queue & Incr PTR
    *(shmid_queue + ((*shmid_queue_ptr)%BUFFSIZE)) = '2'; 
    (*shmid_queue_ptr) = (*shmid_queue_ptr) + 1;
    printf( BOLDBLUE "\tP2 Added to queue\n");
    
    // Check if Top
    while(*(shmid_queue) != '2');
    
    //===================================================
    //               Start Critical Section
    //===================================================
    sem.P(MUTEX);
      
      sleep(3);
      if(*U_V_status == true && *U_V_sample == true)
      {
        *U_V_status = false;
        *U_V_sample = false;
        // Shift queue & Decr PTR
        *(shmid_queue) = *(shmid_queue + 1);
        *(shmid_queue + 1) = *(shmid_queue + 2);
        *(shmid_queue + 2) = *(shmid_queue + 3);
        (*shmid_queue_ptr) = (*shmid_queue_ptr) - 1;
        
        printf( BOLDBLUE "\tP2 RUNNING A" RESET);
        U();
        *U_V_status = true;
      }
      else
      {
        *U_V_sample = true;
        // Remove from queue & Decr PTR
        *(shmid_queue) = *(shmid_queue + 1);
        *(shmid_queue + 1) = *(shmid_queue + 2);
        *(shmid_queue + 2) = *(shmid_queue + 3);
        (*shmid_queue_ptr) = (*shmid_queue_ptr) - 1;
        
        printf( BOLDBLUE "\tP2 RUNNING B" RESET );
        V();
      }
      printf( BOLDBLUE "\n\tP2 DONE\n" RESET );
    sem.V(MUTEX);
    //===================================================
    //                End Critical Section
    //=================================================== 
  }
}

void child_3_main(SEMAPHORE &sem , char* shmid_queue , int* shmid_queue_ptr , bool* U_V_status , bool* U_V_sample )
{  
  /*
  while(running)
  {
    // Add to Queue & Incr PTR
    *(shmid_queue + ((*shmid_queue_ptr)%BUFFSIZE)) = '3'; 
    (*shmid_queue_ptr) = (*shmid_queue_ptr) + 1;
    printf( BOLDGREEN "\tP3 Added to queue\n");
    
    // Check if Top
    while(*(shmid_queue) != '3');
    
    //===================================================
    //               Start Critical Section
    //===================================================
    sem.P(MUTEX);
      sleep(3);
      if(*U_V_status == true)
      {
        *U_V_status = false;
        // Shift queue & Decr PTR
        *(shmid_queue) = *(shmid_queue + 1);
        *(shmid_queue + 1) = *(shmid_queue + 2);
        *(shmid_queue + 2) = *(shmid_queue + 3);
        (*shmid_queue_ptr) = (*shmid_queue_ptr) - 1;
        
        printf( BOLDGREEN "\tP3 RUNNING A" RESET);
        U();
        *U_V_status = true;
      }
      else
      {
        // Remove from queue & Decr PTR
        *(shmid_queue) = *(shmid_queue + 1);
        *(shmid_queue + 1) = *(shmid_queue + 2);
        *(shmid_queue + 2) = *(shmid_queue + 3);
        (*shmid_queue_ptr) = (*shmid_queue_ptr) - 1;
        
        printf( BOLDGREEN "\tP3 RUNNING B" RESET );
        V();
      }
      printf( BOLDGREEN "\n\tP3 DONE\n" RESET );
    sem.V(MUTEX);
    //===================================================
    //                End Critical Section
    //=================================================== 
  }*/
}

void child_4_main(SEMAPHORE &sem , char* shmid_queue , int* shmid_queue_ptr , bool* U_V_status , bool* U_V_sample )
{
  /*
  while(running)
  {
    // Add to Queue & Incr PTR
    *(shmid_queue + ((*shmid_queue_ptr)%BUFFSIZE)) = '4'; 
    (*shmid_queue_ptr) = (*shmid_queue_ptr) + 1;
    printf( BOLDYELLOW "\tP4 Added to queue\n");
    
    // Check if Top
    while(*(shmid_queue) != '4');
    
    //===================================================
    //               Start Critical Section
    //===================================================
    sem.P(MUTEX);
      sleep(3);
      if(*U_V_status == true)
      {
        *U_V_status = false;
        // Shift queue & Decr PTR
        *(shmid_queue) = *(shmid_queue + 1);
        *(shmid_queue + 1) = *(shmid_queue + 2);
        *(shmid_queue + 2) = *(shmid_queue + 3);
        (*shmid_queue_ptr) = (*shmid_queue_ptr) - 1;
        
        printf( BOLDYELLOW "\tP4 RUNNING A" RESET);
        U();
        *U_V_status = true;
      }
      else
      {
        // Remove from queue & Decr PTR
        *(shmid_queue) = *(shmid_queue + 1);
        *(shmid_queue + 1) = *(shmid_queue + 2);
        *(shmid_queue + 2) = *(shmid_queue + 3);
        (*shmid_queue_ptr) = (*shmid_queue_ptr) - 1;
        
        printf( BOLDYELLOW "\tP4 RUNNING B" RESET );
        V();
      }
      printf( BOLDYELLOW "\n\tP4 DONE\n" RESET );
    sem.V(MUTEX);
    //===================================================
    //                End Critical Section
    //=================================================== 
  }*/
}