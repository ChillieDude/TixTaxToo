//Lets see if SDL Works 

#include "Globals.h"
#include <iostream>
#include <SDL.h>

int main( int argc, char* args[] )
{
  //When SDL cannot be initialized, it will return a value of -1
  if( !InitSDL() )
  {
    std::cout << "Something is wrong with InitSDL()" << std::endl;
    return -1;
  }
  
  else
  {
    Play();
  }
  
  Close();
  return 0;
}
