//SDL Obviously works at this point

#include "Globals.h"


//Always initialize pointers to NULL
SDL_Window* theWindow = NULL;
SDL_Renderer* theRenderer = NULL;
//We need a surface in order to load images - and then use a renderer to convert the surface into a texture
SDL_Surface* theSurface = NULL;
SDL_Texture* theTexture = NULL;

const int SCREEN_W = 640;
const int SCREEN_H = 480;
//Line MUST be an even number (For 4 Tiles)
const int LINE_W = 2;
const int TILE_H = SCREEN_H / 2 - LINE_W / 2;
const int TILE_W = SCREEN_W / 2 - LINE_W / 2;
const int TILE_TOTAL = 4;

SDL_Rect tSprites[SPRITE_TOTAL];
tTile tTiles[TILE_TOTAL];

//The tho bellow variables will be deleted eventually
int boxH = SCREEN_H / 2 - LINE_W;
int boxW = SCREEN_W / 2 - LINE_W;

tTexture theSpriteSheet;

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
        if( !LoadContent() )
        {
            std::cout << "You need to configure SpriteSheet.bmp" << std::endl;
        }
        else
        {
             Play();
        }

  }

  Close();
  return 0;
}
