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



extern bool isMyTurn;



//Lets also declare our functions
bool InitSDL();
bool LoadContent();
void Close();
void Play();
void ComputersTurn();
void Menu();

void DrawBoard();
void DrawMenu();
void ResetGame();


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
    void HandleEvent(SDL_Event* event, Uint32& lastEvent);
    void SetSprite(tSpriteFlag newSprite);
    void SetChar(char c);
    void SetMark();

    char CallC();
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


class tButton
{
public:
    tButton();

    void HandleEvent(SDL_Event* e);
    void SetLocation(int x, int y);
    void Render();


private:
    SDL_Rect currentLocation;
    std::string text;
};



//AI Functions

enum winFlag
{
    TILE_TOP_LEFT = 0,
    TILE_TOP_MIDDLE = 1,
    TILE_TOP_RIGHT = 2,
    TILE_CENTER_LEFT = 3,
    TILE_CENTER_MIDDLE = 4,
    TILE_CENTER_RIGHT = 5,
    TILE_BOTTOM_LEFT= 6,
    TILE_BOTTOM_MIDDLE = 7,
    TILE_BOTTOM_RIGHT = 8,
    TILE_TOTAL = 9
};

bool IWin(char givenCharacter);
bool win_logic(int* slots, int size, int flag)


#endif // GLOBALS_H_INCLUDED
