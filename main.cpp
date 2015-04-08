//Lets see if SDL Works 

#include<iostream>
#include <SDL.h>

int main( int argc, char* args[] )
{
  //When SDL cannot be initialized, it will return a value of -1
  if( SDL_Init(SDL_INIT_EVERYTHING) == -1)
  {
    std::cout << "Could not initialize SDL: " << SDL_Error() << std::endl;
  }
  
  else
  {
    std::cout << "Success, commence the program!" <<std::endl;
  }
  
  SDL_Quit();
  return 0;
}
