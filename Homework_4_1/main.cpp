/*
 * Lauro Cabral
 * Homework 4
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
#include <time.h>
#include "semaphore.h"
#include <string>

using namespace std;

#define running 1

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


enum {MUTEX , sem_A , sem_B , sem_C}; 
const int BUFFSIZE = 4; // 4 Processes 

//==================================
//  Main Functions for Processes   =
//==================================
void parent_main(SEMAPHORE&  , char*);
void child_1_main(SEMAPHORE& , char*);
void child_2_main(SEMAPHORE& , char*);
void child_3_main(SEMAPHORE& , char*);


int main()
{  
  // Create Variables
  pid_t wpid=0;
  int status = 0;
  
  int print_process_id;
  char* print_process;

  // Setting Up Shared Data
  print_process_id = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(char), PERMS);
  print_process = (char *)shmat(print_process_id, 0, SHM_RND);


          
  // Mutux Initilazing
  SEMAPHORE sem(4);
  sem.V(MUTEX);
  sem.V(sem_A);
  sem.V(sem_B);
  
  if (fork())
  {
    // Parent Process
    if(fork())
    {
      // Parent Process
      if(fork())
      {
        // Parent Process
        parent_main(sem , print_process);
      }
      else
      {
        // Child 3
        child_3_main(sem , print_process);
      }
    }
    else
    {
      // Child 2
      child_2_main(sem , print_process);
    }
  }
  else
  {
    // Child 1
    child_1_main(sem , print_process);
  }
  
  // wait for child to finish
  while ((wpid = wait(&status)) > 0);
  return 0;
}

/*****************************************************
 *          Main Functions for Processes             * 
 *****************************************************/
void parent_main(SEMAPHORE &sem , char* print_process)
{ 
  while(running){}
}

// A process
void child_1_main(SEMAPHORE &sem , char* print_process)
{
  while(running)
  { 
    sem.P(sem_A);
    sem.P(MUTEX);
    //===================================================
    //               Start Critical Section
    //=================================================== 
    *print_process = 'A';
    cout << RESET << *print_process << " " << endl;
    sleep(1);
    //===================================================
    //                End Critical Section
    //===================================================
    sem.V(sem_C);
    while(*print_process == 'A');
  }
}

// B process
void child_2_main(SEMAPHORE &sem , char* print_process)
{  
  while(running)
  { 
    sem.P(sem_B);
    sem.P(MUTEX);
    //===================================================
    //               Start Critical Section
    //=================================================== 
    *print_process = 'B';
    cout << RESET << *print_process << " " << endl;
    sleep(1);
    //===================================================
    //                End Critical Section
    //===================================================
    sem.V(sem_C);
    while(*print_process == 'B');
  }
}

// C process
void child_3_main(SEMAPHORE &sem , char* print_process)
{  
  while(running)
  {
    sem.P(sem_C);
    
    //===================================================
    //               Start Critical Section
    //===================================================  
    cout << RESET << "C" << " " << endl;
    sleep(1);
    if(*print_process == 'A')
    {
      sem.V(MUTEX);
      sem.V(sem_B);
    }
    else
    {
      sem.V(MUTEX);
      sem.V(sem_A);
    }
    //===================================================
    //                End Critical Section
    //===================================================
  }
}
