#ifndef GLOBALS_H_INCLUDED
#define GLOBALS_H_INCLUDED

#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

void SetWelcome();
void Test();

extern const int MENU_H;
extern const int MENU_W;
extern const int MENU_X;
extern const int MENU_Y;

extern TTF_Font* theFont;
extern SDL_Color textColor;


enum gameLevel
{
    LEVEL_EASY = 0,
    LEVEL_MEDIUM = 1,
    LEVEL_HARD = 2,
    LEVEL_TOTAL = 3
};
extern gameLevel theGameLevel;

enum gameState
{
    GAMESTATE_WELCOME = 0,
    GAMESTATE_PLAY = 1,
    GAMESTATE_MENU = 2,
    GAMESTATE_STATS = 3,
    GAMESTATE_RESULTS = 4,
    GAMESTATE_TOTAL = 5
};
extern gameState theGameState;


class tTexture
{
public:
    tTexture();
    ~tTexture();

    void Deallocate();
    bool LoadImage(const std::string filename);
    void RenderX( SDL_Rect* target, SDL_Rect* clip);

    bool LoadText(const std::string text, const SDL_Color textColor, const int fontSize = 32);
    //Easier to use Render VV
    void Render();

    //Functions for calling height / width
    int GetHeight();
    int GetWidth();
    int GetY();
    int GetX();

    void SetLocation(int x, int y);

private:
    SDL_Texture* sTexture;
    SDL_Rect renderLocation;
};


//We want every single .cpp file to be able to access these variables, so we use extern (Try this w/o Extern!)
extern SDL_Window* theWindow;
extern SDL_Renderer* theRenderer;
extern SDL_Surface* theSurface;
extern tTexture theSpriteSheet;
extern TTF_Font* theFont;


//One of the few times you wont supply a const with a value up front
extern const int SCREEN_W;
extern const int SCREEN_H;
extern const int LINE_W;
extern const int ROWS_TOTAL;

extern const int LINE_TOTAL;
extern const int TILE_W;
extern const int TILE_H;




extern bool isMyTurn;


void DestroyWelcomeTextures();
void LoadWelcomeStrings();
//Lets also declare our functions
bool InitSDL();
bool LoadContent();
void LoadButtons();
void Close();
void Play();
void ComputersTurn();
void Menu();

void DrawBoard();
void DrawMenu();
void DrawWelcome();
void ResetGame();
void SetMenu();




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

//tButtons
enum buttonFlag
{
    BUTTON_RESUME = 0,
    BUTTON_STATS = 1,
    BUTTON_STATS_RETURN = 2,
    BUTTON_EASY = 3,
    BUTTON_MEDIUM = 4,
    BUTTON_HARD = 5,
    BUTTON_EXIT = 6,
    BUTTON_TOTAL = 7
};


class tButton
{
public:
    tButton(std::string theText);
    tButton();
    ~tButton();

    int GetW();
    int GetH();
    bool Outlined();

    void ChangeOutline(const bool flag);
    //returns true if the user wants to exit
    bool HandleEvent(SDL_Event* e);
    void SetLocation(int x, int y);
    void Render();
    void RenderOutlined();
    void Deallocate();
    void SetButtonFlag(buttonFlag btnFlag);
    void SetWidthHeight(int w, int h);
    void SetText(const std::string theText);


private:
    SDL_Rect currentLocation;
    buttonFlag tButtonFlag;
    std::string textString;
    tTexture textTexture;
    bool outlined;
};

extern tButton tButtons[BUTTON_TOTAL];
//End

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

//AI Functions
bool IWin(char givenCharacter);
bool winCondition(int* slots, int size, winFlag* flags);
bool win_logic(int* slots, int size, int flag);
void findAttemptedPath(int*& slots, int size, int& tset);
const int slotsTaken(char c);




#endif // GLOBALS_H_INCLUDED
