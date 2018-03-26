#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

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
    countwords = 0; textTotal = "";
    
    // Get User input        
    cout << "\n\nWrite the word you're searching for:\033[1;32m ";
    cin >> search ;
    cout << "\033[0m";

    cout << "Replace:\033[1;31m ";
    cin >> replace;
    cout << "\033[0m\n";
    
    // Find
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
    
  }
  return 0;
}

























