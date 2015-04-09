//Lets see if SDL Works 

#include "Globals.h"
#include <iostream>
#include <SDL.h>

//Always initialize pointers to NULL
SDL_Window* theWindow = NULL;
SDL_Renderer* theRenderer = NULL;

const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int LINE_W = 3;

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
