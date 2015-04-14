#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

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
extern const int ROWS_TOTAL;

extern const int LINE_TOTAL;
extern const int TILE_W;
extern const int TILE_H;
extern const int TILE_TOTAL;

extern bool isMyTurn;



//Lets also declare our functions
bool InitSDL();
bool LoadContent();
void Close();
void Play();
void ComputersTurn();


//Sprite Flags  : BEGIN
enum tSpriteFlag
{
    SPRITE_NONE = 0,
    SPRITE_OVER = 1,
    SPRITE_CLICK = 2,
    SPRITE_RELEASE = 3,
    SPRITE_COM = 4,
    SPRITE_TOTAL = 5
};

extern SDL_Rect tSprites[SPRITE_TOTAL];
//Sprite Flags  : END


class tTile
{
public:
    tTile();

    void Reset();
    void SetLocation(int x, int y);
    void Render();
    void HandleEvent(SDL_Event* event);
    void SetSprite(tSpriteFlag newSprite);
    void SetChar(char c);
    void SetMark();

    bool isOpen();

    int GetY();
    int GetX();
    int GetW();
    int GetH();
private:

    tSpriteFlag currentSprite;
    SDL_Rect currentPosition;
    bool marked;
    char player;
};

extern tTile tTiles[];
extern SDL_Rect tLines[];

#endif // GLOBALS_H_INCLUDED