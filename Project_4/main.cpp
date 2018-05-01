// C++ program to demonstrate creating processes using fork()
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


enum {MUTEX , MUTUX_STATUS}; 

//==================================
//         U() and V()             =
//==================================
void U(void)
{

}
void V(void)
{
  
}

//==================================
//  Main Functions for Processes   =
//==================================
void parent_main(SEMAPHORE&  , int*);
void child_1_main(SEMAPHORE& , int*);
void child_2_main(SEMAPHORE& , int*);
void child_3_main(SEMAPHORE& , int*);
void child_4_main(SEMAPHORE& , int*);


int main()
{  
  pid_t wpid=0;
  int status = 0;
  
  int shmid_queue_id , shmid_queue_ptr_id;
  int *shmid_queue , shmid_queue_ptr;
  
  shmid_queue_id = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(int), PERMS);
  shmid_queue_ptr_id = shmget(IPC_PRIVATE, sizeof(int), PERMS);
  
  shmid_queue = (char *)shmat(shmid_queue_id, 0, SHM_RND);
  shmid_queue_ptr = (char *)shmat(shmid_queue_ptr_id, 0, SHM_RND);
  
  SEMAPHORE sem(2);
  sem.V(MUTEX);
  sem.V(MUTEX);
  sem.V(MUTUX_STATUS);
  

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
          cout << reset << bold << "Parent\n" << reset;
          parent_main(sem , shmBUF);
        }
        else
        {
          // Child 4
          cout << yellow << "Fourth\n" << reset;
          child_4_main(sem , shmBUF);
          exit(0);
        }
      }
      else
      {
        // Child 3
        cout << green << "Third\n" << reset;
        child_3_main(sem , shmBUF);
        exit(0);
      }
    }
    else
    {
      // Child 2
      cout << blue << "Second\n" << reset;
      child_2_main(sem , shmBUF);
      exit(0);
    }
  }
  else
  {
    // Child 1
    cout << red << "First\n" << reset;
    child_1_main(sem , shmBUF);
    exit(0);
  }
  
  // wait for child to finish
  while ((wpid = wait(&status)) > 0);
  return 0;
}

/*****************************************************
 *          Main Functions for Processes             * 
 *****************************************************/
void parent_main(SEMAPHORE &sem , int *shmBUF)
{ 
  bool flag;
  while(running)
  {
    if(MUTEX == 1)
    {
      cout << "SHF" << endl;
    }
  }
}

void child_1_main(SEMAPHORE &sem , int *shmBUF)
{
  int flag;
  while(running)
  {
    sleep(1);
    // Put in Queue
    *(shmBUF + )
    sem.P(MUTEX);
      cout << reset << red << "\n\tFirst RANNED  " << reset;
      if(flag == True)
      {
        U();
      }
      else
      { 
        V();
      }
    sem.V(MUTEX);
  }
}

void child_2_main(SEMAPHORE &sem , int *shmBUF)
{
  /*
  bool flag;
  while(running)
  {
    
    sleep(1);
    sem.P(MUTEX);
      sem.P(MUTUX_STATUS);
        flag = U_V_status();
      sem.V(MUTUX_STATUS);
      cout << reset << blue << "\n\tSecond RANNED  " << reset;
      if(flag == True)
      {
        cout << cyan << " U Function" << reset << endl;
        U();
      }
      else
      {
        cout << magenta << " V Function" << reset << endl;
        V();
      }
    sem.V(MUTEX);
  }*/
}

void child_3_main(SEMAPHORE &sem , int *shmBUF)
{
  /*
  bool flag;
  while(running)
  {
    sleep(1);
    sem.P(MUTEX);
      sem.P(MUTUX_STATUS);
        flag = U_V_status();
      sem.V(MUTUX_STATUS);
      cout << reset << green << "\n\tThird RANNED  " << reset;
      if(flag == True)
      {
        cout << cyan << " U Function" << reset << endl;
        U();
      }
      else
      {
        cout << magenta << " V Function" << reset << endl;
        V();
      }
    sem.V(MUTEX);
  }*/
}

void child_4_main(SEMAPHORE &sem , int *shmBUF)
{
  /*
  bool flag;
  while(running)
  {
    sleep(1);
    sem.P(MUTEX);
      sem.P(MUTUX_STATUS);
        flag = U_V_status();
      sem.V(MUTUX_STATUS);
      cout << reset << yellow << "\n\tFourth RANNED  " << reset;
      if(flag == True)
      {
        cout << cyan << " U Function" << reset << endl;
        U();
      }
      else
      {
        cout << magenta << " V Function" << reset << endl;
        V();
      }
    sem.V(MUTEX);
  }*/
}