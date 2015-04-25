#include "Globals.h"

tTexture tStrWelcome;
tTexture tStrSelectLevel;
tTexture tStrCurrentLevel;

tTexture tStrEasy, tStrMedium, tStrHard;
void DestroyWelcomeTextures()
{
    tStrCurrentLevel.Deallocate();
    tStrEasy.Deallocate();
    tStrHard.Deallocate();
    tStrMedium.Deallocate();
    tStrSelectLevel.Deallocate();
    tStrWelcome.Deallocate();
}
void LoadWelcomeStrings()
{
    //Welcome Screen -----------------------------
    const int TEXT_SIZE = 32;

    tStrWelcome.LoadText("Welcome to Tix-Tax-Toe!", textColor, 60);
    tStrWelcome.SetLocation( SCREEN_W / 2 - tStrWelcome.GetWidth() / 2 , 0 );

    tStrSelectLevel.LoadText("Select your level", textColor, 40);
    tStrSelectLevel.SetLocation(SCREEN_W / 2 - tStrSelectLevel.GetWidth() / 2, tStrWelcome.GetHeight() );

    int tempX = tStrCurrentLevel.GetWidth(), tempY = tStrSelectLevel.GetHeight() + tStrWelcome.GetHeight();

    tStrCurrentLevel.LoadText("Current level : ", textColor, TEXT_SIZE);
    tStrCurrentLevel.SetLocation( 0 ,tStrSelectLevel.GetHeight() + tStrWelcome.GetHeight() );

    tStrEasy.LoadText("Easy", textColor, TEXT_SIZE);
    tStrMedium.LoadText("Medium", textColor, TEXT_SIZE);
    tStrHard.LoadText("Hard", textColor, TEXT_SIZE);

    tStrEasy.SetLocation(tempX , tempY );
    tStrMedium.SetLocation(tempX, tempY);
    tStrHard.SetLocation(tempX, tempY);

    


}
//Every Frame check this
void SetWelcome()
    {
        int tempX;
        switch(theGameLevel)
        {
        case LEVEL_EASY:
            tempX = SCREEN_W / 2 - (tStrCurrentLevel.GetWidth() + tStrEasy.GetWidth() ) / 2;
            break;

        case LEVEL_MEDIUM:
            tempX = SCREEN_W / 2 - (tStrCurrentLevel.GetWidth() + tStrMedium.GetWidth() ) / 2;
            break;

        case LEVEL_HARD:
            tempX = SCREEN_W / 2 - (tStrCurrentLevel.GetWidth() + tStrHard.GetWidth() ) / 2;
            break;
        }
        if(tStrCurrentLevel.GetX() != tempX)
        {
            tStrCurrentLevel.SetLocation(tempX, tStrCurrentLevel.GetY());
            tempX += tStrCurrentLevel.GetWidth();

            tStrEasy.SetLocation(tempX, tStrCurrentLevel.GetY());
            tStrMedium.SetLocation(tempX, tStrCurrentLevel.GetY());
            tStrHard.SetLocation(tempX, tStrCurrentLevel.GetY());
        }
        tButtons[BUTTON_RESUME].SetText("Play");
        tButtons[BUTTON_RESUME].SetLocation(SCREEN_W / 2 - (tButtons[BUTTON_RESUME].GetW() / 2 ), SCREEN_H * 3 / 4);
    }

void DrawWelcome()
{
    SDL_SetRenderDrawColor(theRenderer, 0x00, 0x00, 0x00, 0xFF);
    SDL_RenderClear(theRenderer);

    tStrWelcome.Render();
    tStrSelectLevel.Render();
    tStrCurrentLevel.Render();

    switch(theGameLevel)
        {
        case LEVEL_EASY:
            tStrEasy.Render();
            break;

        case LEVEL_MEDIUM:
            tStrMedium.Render();
            break;

        case LEVEL_HARD:
            tStrHard.Render();
            break;
        }
        tButtons[0].Render();
        tButtons[BUTTON_EASY].Render();
        tButtons[BUTTON_HARD].Render();
        tButtons[BUTTON_MEDIUM].Render();
}





