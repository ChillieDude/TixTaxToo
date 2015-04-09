#include <SDL.h>
#include <iostream>
#include "Globals.h"

bool InitSDL()
{
    //When SDL cannot be initialized, it will return a value of -1
    if( SDL_Init(SDL_INIT_EVERYTHING) == -1)
    {
        std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    else
    {
        //If we are here (now that SDL is started) we can call an SDL Function

        //SDL_CreateWindow() Takes 5 arguments.
        //Name of Window, The X Value, Y Value, Width, Height, and a lastly: Flags (We wont worry about the x, y, or flags for now)
        theWindow = SDL_CreateWindow("Window!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
        //If anything went wrong, theWindow (And Any pointer as such) will be NULL
        if(theWindow == NULL)
        {
            std::cout << "Could not create the window! ERROR" <<SDL_GetError() << std::endl;
            return false;
        }
        else
        {
            //Creating a Renderer is similar: You supply a window, an "index", and flags
            //When can omit the SDL_RENDERER_ACCELERATED, and the program will still run, but we want hardware acceleration
            //-1 is the first Renderer to accept flags:
            //More info on CreateRenderer() can be found here: http://wiki.libsdl.org/SDL_CreateRenderer
            theRenderer = SDL_CreateRenderer(theWindow, -1, SDL_RENDERER_ACCELERATED);

            //Again, if anything goes wrong with a pointer, it will point to NULL
            if(theRenderer == NULL)
            {
                std::cout << "Something Went Wrong! Render Error" << SDL_GetError() <<std::endl;
                return false;
            }
            else
            {
                //If we are here, then the Window is created, the renderer is properly attached to the window
                //Lets set the Renderer Color
                Uint8 red = 255, blue =255, green = 0xFF, alpha = 0xFF;
                SDL_SetRenderDrawColor(theRenderer, red, green, blue, alpha);
                //Accepts the Renderer you want to use (we only will use one in our first few projects)
                //Along with 4 8bit-Unsigned-Integers (Uint8)

                //Woohoo everything worked!
                return true;
            }
        }
    }
}



void Play()
{
    //We will need these Rects when we start drawing - Later we will create a bool LoadContent() Function!
    SDL_Rect line1, line2;

    line1.x = SCREEN_W / 2 - LINE_W / 2;
    line1.y = 0;
    line1.h = SCREEN_H;
    line1.w = LINE_W;

    line2.x = 0;
    line2.y = SCREEN_H / 2 - LINE_W / 2;
    line2.h = LINE_W;
    line2.w = SCREEN_W;

    //Use a quit flag to start a game loop
    bool quit = false;
    SDL_Event event;

    while( !quit )
    {
        //While there are events to pull...
        while(SDL_PollEvent(&event) != 0)
        {
            //Handle each one
            //SDL_QUIT is something like hitting the Red X on the top right of screen. Also added support for ESC quit
            if(event.type == SDL_QUIT || event.key.keysym.sym == SDLK_ESCAPE)
            {
                quit = true;
            }
            //place Else here to react to other actions

        }

        //This is where the drawing happens!


        //Clear screen with white
        SDL_SetRenderDrawColor( theRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( theRenderer );

        //We must remember to change the renderer color
        SDL_SetRenderDrawColor(theRenderer, 0, 0, 0, 255); //Color Black - Full Alpha
        SDL_RenderFillRect(theRenderer, &line1);
        SDL_RenderFillRect(theRenderer, &line2);


        //Update screen
        SDL_RenderPresent( theRenderer );
    }
    //Quit is true at this point so we return
    return;
}



void Close()
{
    //We have to make sure we deallocate memory we have used

    SDL_DestroyWindow(theWindow);
    SDL_DestroyRenderer(theRenderer);

    theWindow = NULL;
    theRenderer = NULL;

    //Now that the variables are taken care of.... Quit SDL systems
    SDL_Quit();
}
