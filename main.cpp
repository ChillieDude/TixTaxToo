#include "Globals.h"


//Always initialize pointers to NULL
SDL_Window* theWindow = NULL;
SDL_Renderer* theRenderer = NULL;

//We need a surface in order to load images - and then use a renderer to convert the surface into a texture
SDL_Surface* theSurface = NULL;

//init Screen Width and Height
const int SCREEN_W = 640;
const int SCREEN_H = 480;
const int ROWS_TOTAL = 3;
const int LINE_W = 10;


//Auto Updating Constants -----------

//There will be one less line then there are tiles for each Axis (X & Y)
const int LINE_TOTAL = (ROWS_TOTAL - 1) * 2;

const int TILE_W = (SCREEN_W - LINE_W * (LINE_TOTAL / 2) ) / ROWS_TOTAL;
const int TILE_H = (SCREEN_H - LINE_W * (LINE_TOTAL / 2) ) / ROWS_TOTAL;
const int TILE_TOTAL = ROWS_TOTAL * ROWS_TOTAL;

SDL_Rect tLines[LINE_TOTAL];
SDL_Rect tSprites[SPRITE_TOTAL];
tTile tTiles[TILE_TOTAL];
tTexture theSpriteSheet;

//Let us go first!
bool isMyTurn = true;

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
