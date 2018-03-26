#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  string search;
  string candidate ;
  string replace;
  int countwords = 0 ;
    
  ifstream File("robot.txt");
  ofstream fileout("temp.txt"); //Temporary file
  
  if(!File || !fileout) //if both files are not available
  {
    cout << "Error opening files!" << endl;
    return 1;
  }
  if(File.is_open())
  {
    cout << "Write the word you're searching for:\033[1;32m ";
    cin >> search ;
    cout << "\033[0m";
    
    cout << "Replace:\033[1;31m ";
    cin >> replace;
    cout << "\033[0m";
    
    while(File>>candidate ) 
    {
      if( search == candidate ) //if your word found then replace
      {
        candidate = replace;
        ++countwords ;  
      } 
      fileout << candidate << " ";
    }

    cout << "The word '" << search << "' has been found " << countwords << " times.\n" ;
  }

  else
  {
    cout << "Error! File not found!\n" ;
    return 1 ;
  }

  return 0;
}


























