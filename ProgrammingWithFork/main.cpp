#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define running 1

using namespace std;

void find_and_replace();

int main() {
  string text = "";
  string textTotal = "";
  
  string search;
  string candidate;
  string replace;  
  
  int countwords = 0;
  int status = 0;
  
  pid_t pid=1,wpid=0;
  
  ifstream filein("robot.txt");
  ofstream temp_fileout("temp.txt"); //Temporary file
  ifstream temp_filein("temp.txt");
   
  
  if(filein.is_open() && temp_fileout.is_open() && temp_filein.is_open())
  {
    cout << "Files are good\n";
  }
  
  // clear temp file
  temp_fileout.open("temp.txt",ofstream::out | ofstream::trunc);
  temp_fileout.close();
  temp_fileout.open("temp.txt");
         
  while(!filein.eof())
  {
    getline(filein, text);
    textTotal += text + " ";
  }
  temp_fileout << textTotal;
  cout << textTotal;
  temp_fileout.close();
  temp_filein.close();
  
  while(running)
  {
    countwords = 0; textTotal = "";status = 0;pid=1;
    
    // Get User input        
    cout << "\n\nWrite the word you're searching for:\033[1;32m ";
    cin >> search ;
    cout << "\033[0m";

    // if string is '!wq' terminate
    if(search.compare("!wq") == 0)
    {
        cout << "\n--End of Program--\n";
        // wait for child to finish
        //wait(NULL);
        //wait(NULL);
        break;

    }

    cout << "Replace:\033[1;31m ";
    cin >> replace;
    cout << "\033[0m\n";
    
    // Find and replace using child process
    printf("\n--beginning of Child program--\n\n");
    pid = fork();
   
    if(pid == 0)
    {
        // Child Process
        temp_filein.open("temp.txt");
        while(temp_filein>>candidate ) 
        {
        text = candidate;
        if( search == candidate ) //if your word found then replace
        {
          candidate = "\033[1;35m"+replace+"\033[0m";
          text = replace;
          ++countwords ;  
        } 
        textTotal = textTotal + " " + text;
        cout << candidate << " "; 
        }
        temp_filein.close();

        // Clear and Fill
        temp_fileout.open("temp.txt",ofstream::out | ofstream::trunc);
        temp_fileout.close();
        temp_fileout.open("temp.txt");


        temp_fileout << textTotal;
        cout << "\n\nThe word \033[1;31m'" << search 
        << "'\033[0m has been found \033[1;33m" << countwords << "\033[0m times.\n";
        while(countwords == 0){cout <<".";}
        printf("\n--end of Child processing--\n");
        exit(0);
    }
    else if(pid < 0)
    {
        // fork failed
        cout << "Fork failed\n";
        return 1;
    }
    
    // wait for child and parent to finish
    while ((wpid = wait(&status)) > 0);
    
    
    printf("\n--end of processing--\n");
    
    
  }
    // wait for child to finish
    while ((wpid = wait(&status)) > 0);
    return 0;
}

























