#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include <SDL.h>
#include <iostream>

class tTexture
{
public:
    tTexture();
    ~tTexture();

    void Deallocate();
    bool LoadImage(std::string filename);
    void RenderX( SDL_Rect* target, SDL_Rect* clip);

    //Easier to use Render VV
    void Render(int x, int y, SDL_Rect* clip);

    //Functions for calling height / width
    int GetHeight();
    int GetWidth();

private:
    SDL_Texture* sTexture;
    int tWidth;
    int tHeight;
};


//We want every single .cpp file to be able to access these variables, so we use extern (Try this w/o Extern!)
extern SDL_Window* theWindow;
extern SDL_Renderer* theRenderer;
extern SDL_Surface* theSurface;
extern tTexture theSpriteSheet;


//One of the few times you wont supply a const with a value up front
extern const int SCREEN_W;
extern const int SCREEN_H;
extern const int LINE_W;
extern const int TILE_W;
extern const int TILE_H;
extern const int TILE_TOTAL;

//these can be deleted without any harm VV But make sure to delete line1 / line2 in Play()
extern int boxH;
extern int boxW;
//
//Lets also declare our functions
bool InitSDL();
bool LoadContent();
void Close();
void Play();

enum tSpriteSheet
{
    SPRITE_NONE = 0,
    SPRITE_OVER = 1,
    SPRITE_CLICK = 2,
    SPRITE_RELEASE = 3,
    SPRITE_TOTAL = 4
};

extern SDL_Rect tSprites[SPRITE_TOTAL];

class tTile
{
public:
    tTile();

    void SetLocation(int x, int y);
    void Render();
    void HandleEvent(SDL_Event* event);
    void SetSprite(tSpriteSheet newSprite);
private:
    tSpriteSheet currentSprite;
    SDL_Rect currentPosition;
};



extern tTile tTiles[];





#endif // GLOBALS_H_INCLUDED
