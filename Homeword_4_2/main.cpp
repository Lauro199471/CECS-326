/*
 * Lauro Cabral
 * Homework 4 2
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
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <time.h>

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


enum {sem_A0 , sem_A1 , sem_A2 , sem_B0 , sem_B1 , sem_B2}; 
const int BUFFSIZE = 6; // 6 Processes 

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const std::string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}


//==================================
//  Main Functions for Processes   =
//==================================
void parent_main(SEMAPHORE&  , bool* , bool* , bool* , bool* , bool* , bool*);
void child_1_main(SEMAPHORE& , bool* , bool* , bool* , bool* , bool* , bool*);
void child_2_main(SEMAPHORE& , bool* , bool* , bool* , bool* , bool* , bool*);
void child_3_main(SEMAPHORE& , bool* , bool* , bool* , bool* , bool* , bool*);
void child_4_main(SEMAPHORE& , bool* , bool* , bool* , bool* , bool* , bool*);
void child_5_main(SEMAPHORE& , bool* , bool* , bool* , bool* , bool* , bool*);


int main()
{  
  // Create Variables
  pid_t wpid=0;
  int status = 0;
  
  int taken_A0_id , taken_A1_id , taken_A2_id, 
      taken_B0_id , taken_B1_id , taken_B2_id;
  
  bool* taken_A0; 
  bool* taken_A1;
  bool* taken_A2;
  bool* taken_B0;
  bool* taken_B1;
  bool* taken_B2;
  
  // Setting Up Shared Data
  taken_A0_id = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(bool), PERMS);
  taken_A1_id = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(bool), PERMS);
  taken_A2_id = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(bool), PERMS);
  taken_B0_id = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(bool), PERMS);
  taken_B1_id = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(bool), PERMS);
  taken_B2_id = shmget(IPC_PRIVATE, BUFFSIZE*sizeof(bool), PERMS);
  
  taken_A0 = (bool *)shmat(taken_A0_id, 0, SHM_RND);
  taken_A1 = (bool *)shmat(taken_A1_id, 0, SHM_RND);
  taken_A2 = (bool *)shmat(taken_A2_id, 0, SHM_RND);
  taken_B0 = (bool *)shmat(taken_B0_id, 0, SHM_RND);
  taken_B1 = (bool *)shmat(taken_B1_id, 0, SHM_RND);
  taken_B2 = (bool *)shmat(taken_B2_id, 0, SHM_RND);

          
  // Mutux Initilazing
  SEMAPHORE sem(6);
  sem.V(sem_A0);
  sem.V(sem_A1);
  sem.V(sem_A2);
  
  sem.V(sem_B0);
  sem.V(sem_B1);
  sem.V(sem_B2);
  
  *taken_A0 = false;
  *taken_A1 = false;
  *taken_A2 = false;
  
  *taken_A0 = false;
  *taken_B1 = false;
  *taken_B2 = false;
  
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
          if(fork())
          {
            // Parent Process
            parent_main(sem , taken_A0 , taken_A1 , taken_A2 , taken_B0 , taken_B1 , taken_B2);
          }
          else
          {
            // Child 5
            child_5_main(sem , taken_A0 , taken_A1 , taken_A2 , taken_B0 , taken_B1 , taken_B2);
          }
        }
        else
        {
          // Child 4
          child_4_main(sem , taken_A0 , taken_A1 , taken_A2 , taken_B0 , taken_B1 , taken_B2);
        }

      }
      else
      {
        // Child 3
        child_3_main(sem , taken_A0 , taken_A1 , taken_A2 , taken_B0 , taken_B1 , taken_B2);
      }
    }
    else
    {
      // Child 2
      child_2_main(sem , taken_A0 , taken_A1 , taken_A2 , taken_B0 , taken_B1 , taken_B2);
    }
  }
  else
  {
    // Child 1
    child_1_main(sem , taken_A0 , taken_A1 , taken_A2 , taken_B0 , taken_B1 , taken_B2);
  }
  
  // wait for child to finish
  while ((wpid = wait(&status)) > 0);
  return 0;
}

/*****************************************************
 *          Main Functions for Processes             * 
 *****************************************************/
void parent_main(SEMAPHORE &sem , bool* taken_A0 , bool* taken_A1 , bool* taken_A2 , bool* taken_B0 , bool* taken_B1 , bool* taken_B2)
{ 
  while(running){}
}

// Robot A
void child_1_main(SEMAPHORE &sem , bool* taken_A0 , bool* taken_A1 , bool* taken_A2 , bool* taken_B0 , bool* taken_B1 , bool* taken_B2)
{
  int x = 0;
  
  while(running)
  { 
    if(*taken_A0 == false && *taken_A1 == false)
    {
      *taken_A0 = true;
      *taken_A1 = true;
      
      sem.P(sem_A0);
      //===================================================
      //               Start Critical Section
      // sleep function will simulate the robot stuff
      //=================================================== 
      srand(time(NULL));
      x = rand()%15+1;
      cout << BOLDRED << "Robot A : A0 " << x << RESET << " " << currentDateTime() << endl;
      sleep(x);
      //===================================================
      //                End Critical Section
      //===================================================
      
      sem.V(sem_A0);
      *taken_A0 = false;
      *taken_A1 = false;
    }
    
    
    if(*taken_B0 == false && *taken_A0 == false)
    {
      *taken_A0 = true;
      *taken_B0 = true;
      
      sem.P(sem_B0);
      //===================================================
      //               Start Critical Section
      // sleep function will simulate the robot stuff
      //=================================================== 
      srand(time(NULL));
      x = rand()%15+1;
      cout << BOLDRED << "Robot A : B0 " << x << RESET << " " << currentDateTime() << endl;
      sleep(x);
      //===================================================
      //                End Critical Section
      //===================================================
      
      sem.V(sem_B0);
      *taken_A0 = false;
      *taken_B0 = false;
    }
  }
}

// Robot B
void child_2_main(SEMAPHORE &sem , bool* taken_A0 , bool* taken_A1 , bool* taken_A2 , bool* taken_B0 , bool* taken_B1 , bool* taken_B2)
{ 
  int x = 0;
  
  while(running)
  { 
    
    if(*taken_B0 == false && *taken_A0 == false)
    {
      *taken_A0 = true;
      *taken_B0 = true;
      
      sem.P(sem_B0);
      //===================================================
      //               Start Critical Section
      // sleep function will simulate the robot stuff
      //=================================================== 
      srand(time(0));
      x = (rand() + 4 )%15+1;
      cout << BOLDBLUE << "Robot B : B0 " << x << RESET << " " << currentDateTime() << endl;
      sleep(x);
      //===================================================
      //                End Critical Section
      //===================================================
      
      sem.V(sem_B0);
      *taken_A0 = false;
      *taken_B0 = false;
    }
    
    if(*taken_B1 == false)
    {
      *taken_B1 = true;
      
      sem.P(sem_B1);
      //===================================================
      //               Start Critical Section
      // sleep function will simulate the robot stuff
      //=================================================== 
      srand(time(0));
      x = (rand() + 4 )%15+1;
      cout << BOLDBLUE << "Robot B : B1 " << x << RESET << " " << currentDateTime() << endl;
      sleep(x);
      //===================================================
      //                End Critical Section
      //===================================================
      
      sem.V(sem_B1);
      *taken_B1 = false;
    }
  }
}

// Robot C
void child_3_main(SEMAPHORE &sem , bool* taken_A0 , bool* taken_A1 , bool* taken_A2 , bool* taken_B0 , bool* taken_B1 , bool* taken_B2)
{ 
  int x = 0;
  
  while(running)
  {
    if(*taken_A1 == false)
    {
      *taken_A1 = true;
     
      sem.P(sem_A1);
      //===================================================
      //               Start Critical Section
      // sleep function will simulate the robot stuff
      //=================================================== 
      srand(time(0));
      x = (rand() + 2 )%15 + 1;
      cout << BOLDGREEN << "Robot C : A1 " << x << RESET << " " << currentDateTime() << endl;
      sleep(x);
      //===================================================
      //                End Critical Section
      //===================================================
      
      sem.V(sem_A1);
      *taken_A1 = false;
    }
    
    if(*taken_B1 == false)
    {
      *taken_B1 = true;
      
      sem.P(sem_B1);
      //===================================================
      //               Start Critical Section
      // sleep function will simulate the robot stuff
      //=================================================== 
      srand(time(0));
      x = (rand() + 4 )%15 + 1;
      cout << BOLDGREEN << "Robot C : B1 " << x << RESET << " " << currentDateTime() << endl;
      sleep(x);
      //===================================================
      //                End Critical Section
      //===================================================
      
      sem.V(sem_B1);
      *taken_B1 = false;
    }
  }
}

// Robot D
void child_4_main(SEMAPHORE &sem , bool* taken_A0 , bool* taken_A1 , bool* taken_A2 , bool* taken_B0 , bool* taken_B1 , bool* taken_B2)
{ 
  int x = 0;
  
  while(running)
  {
    if(*taken_A0 == false && *taken_A1 == false)
    {
      *taken_A0 = true;
      *taken_A1 = true;
      
      sem.P(sem_A0);
      //===================================================
      //               Start Critical Section
      // sleep function will simulate the robot stuff
      //=================================================== 
      srand(time(NULL));
      x = (rand()+7)%15+1;
      cout << BOLDYELLOW << "Robot D : A0 " << x << RESET << " " << currentDateTime() << endl;
      sleep(x);
      //===================================================
      //                End Critical Section
      //===================================================
      
      sem.V(sem_A0);
      *taken_A0 = false;
      *taken_A1 = false;
    }
    
    
    if(*taken_B2 == false && *taken_B1 == false && *taken_A2 == false)
    {
      *taken_B1 = true;
      *taken_B2 = true;
      *taken_A2 = true;
      
      sem.P(sem_B2);
      //===================================================
      //               Start Critical Section
      // sleep function will simulate the robot stuff
      //=================================================== 
      srand(time(NULL));
      x = (rand()+7)%15+1;
      cout << BOLDYELLOW << "Robot D : B2 " << x << RESET << " " << currentDateTime() << endl;
      sleep(x);
      //===================================================
      //                End Critical Section
      //===================================================
      
      sem.V(sem_B2);
      *taken_B1 = false;
      *taken_B2 = false;
      *taken_A2 = false;
    }
  }
}

// Robot E
void child_5_main(SEMAPHORE &sem , bool* taken_A0 , bool* taken_A1 , bool* taken_A2 , bool* taken_B0 , bool* taken_B1 , bool* taken_B2)
{ 
  int x = 0;
  
  while(running)
  {
    if(*taken_A1 == false)
    {
      *taken_A1 = true;
      
      sem.P(sem_A1);
      //===================================================
      //               Start Critical Section
      // sleep function will simulate the robot stuff
      //=================================================== 
      srand(time(0));
      x = (rand() + 8 )%15 + 1;
      cout << BOLDMAGENTA << "Robot E : A1 " << x << RESET << " " << currentDateTime() << endl;
      sleep(x);
      //===================================================
      //                End Critical Section
      //===================================================
      
      sem.V(sem_A1);
      *taken_A1 = false;
    }
    
    if(*taken_A2 == false)
    {
      *taken_A2 = true;
      
      sem.P(sem_A2);
      //===================================================
      //               Start Critical Section
      // sleep function will simulate the robot stuff
      //=================================================== 
      srand(time(0));
      x = (rand() + 8 )%15 + 1;
      cout << BOLDMAGENTA << "Robot E : A2 " << x << RESET << " " << currentDateTime() << endl;
      sleep(x);
      //===================================================
      //                End Critical Section
      //===================================================
      
      sem.V(sem_A2);
      *taken_A2 = false;
    }
  }
}