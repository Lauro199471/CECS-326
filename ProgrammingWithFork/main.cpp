#include <cstdlib>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main() {
  string search;
  string candidate ;
  int countwords = 0 ;
    
  ifstream File("robot.txt");
  if(File.is_open())
  {
    cout << "File opened.\n" ;

    cout << "Write the word you're searching for\n" ;
    cin >> search ;

    while(File>>candidate ) 
    {
      if( search == candidate ) ++countwords ;
    }

    std::cout << "The word '" << search << "' has been found " << countwords << " times.\n" ;
  }

  else
  {
    cout << "Error! File not found!\n" ;
    return 1 ;
  }

  return 0;
}


























