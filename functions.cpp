#include "Globals.h"


/////////////////////////////////////
////////  Load Game Content  ////////
/////////////////////////////////////

bool LoadContent()
{
    if(!theSpriteSheet.LoadImage("SpriteSheet.bmp") )
    {
        std::cout << "Oops" <<std::endl;
        return false;
    }
    //This sprite sheet will read right left to right, sprite size being 100
    for(int i = 0; i!= SPRITE_TOTAL; ++i )
    {
        tSprites[i].h = 100;
        tSprites[i].w = 100;
        tSprites[i].y = 0;
        tSprites[i].x = i*100;
    }

    int x = 0, y = 0;
    for(int i = 0; i != TILE_TOTAL; ++i)
    {
        if(x == 2)
        {
            ++y;
            x=0;
        }
        tTiles[i].SetLocation( x*TILE_W + x*LINE_W, y*TILE_H + y*LINE_W);
        ++x;
    }

    tTiles[1].SetSprite(SPRITE_OVER);
    tTiles[2].SetSprite(SPRITE_CLICK);
    tTiles[3].SetSprite(SPRITE_RELEASE);

    return true;
}


/////////////////////////////////////
////////   Our Game Loop     ////////
/////////////////////////////////////

void Play()
{


    //We will need these Rects when we start drawing 
    SDL_Rect line1, line2;

    line1.x = TILE_W;
    line1.y = 0;
    line1.h = SCREEN_H;
    line1.w = LINE_W;

    line2.x = 0;
    line2.y = TILE_H;
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


        for(int i = 0; i!= TILE_TOTAL; ++i)
        {
            tTiles[i].Render();
        }

        //Update screen
        SDL_RenderPresent( theRenderer );
    }
    //Quit is true at this point so we return
    return;
}


/////////////////////////////////////
////////   tTile Functions   ////////
/////////////////////////////////////


tTile::tTile()
{
    currentPosition.x = 0;
    currentPosition.y = 0;
    currentPosition.h = TILE_H;
    currentPosition.w = TILE_W;

    currentSprite = SPRITE_NONE;
}

void tTile::SetSprite(tSpriteSheet newSprite)
{
    currentSprite = newSprite;
}

void tTile::SetLocation(int x, int y)
{
    currentPosition.x = x;
    currentPosition.y = y;
}

void tTile::Render()
{
    theSpriteSheet.RenderX( &currentPosition, &tSprites[currentSprite] );
}

/////////////////////////////////////
//////// tTexture Functions  ////////
/////////////////////////////////////
void tTexture::Render(int x, int y, SDL_Rect* clip = NULL)
{
    //This is the box on location of the screen we will render to
    SDL_Rect renderLocation;
    //Use the x and y that were supplied
    renderLocation.x = x;
    renderLocation.y = y;
    //And use the height and width of the full image
    renderLocation.h = tHeight;
    renderLocation.w = tWidth;

    //Unless you want to supply a clip from a sprite sheet, then you would want the width/height of the clip instead of the height / width of the WHOLE sprite sheet
    if(clip != NULL)
    {
        //Set the new H/W
        renderLocation.h = clip->h;
        renderLocation.w = clip->w;
    }

    SDL_RenderCopy(theRenderer, sTexture, clip, &renderLocation);

}

int tTexture::GetHeight()
{
    return tHeight;
}

int tTexture::GetWidth()
{
    return tWidth;
}

void tTexture::RenderX( SDL_Rect* target, SDL_Rect* clip )
{
    //We pass two Rects to this function
    //target is the Rectangle on the screen that you will occupy
    //clip is the rectangle that you select a sprite from the sprite sheet
    SDL_RenderCopy(theRenderer, sTexture, clip , target);
}

tTexture::tTexture()
{
    sTexture = NULL;
    tHeight = 0;
    tWidth = 0;
}

tTexture::~tTexture()
{
    Deallocate();
}

void tTexture::Deallocate()
{
    if(sTexture != NULL)
    {
        SDL_DestroyTexture(sTexture);
        sTexture = NULL;
        tHeight = 0;
        tWidth = 0;
    }

}

bool tTexture::LoadImage(std::string filename)
{
    //This function uses the surface to load an image, then create a texture out of it

    Deallocate();

    //Create a "Guinna Pig" texture
    SDL_Texture* thePig = NULL;

    //Load a BMP into theSurface. BMP Is the only file type that native SDL2 can import. W(e will have to add SDL2_image to import other formats)
    theSurface = SDL_LoadBMP( filename.c_str() ); //SDL_LoadBMP expects a ( char[] )
    //Debug VV
    if(theSurface == NULL)
    {
        std::cout << "Could not Load image! : " << SDL_GetError() <<std::endl;
    }
    else
    {
        //
        thePig = SDL_CreateTextureFromSurface(theRenderer, theSurface);

        //Debug VV
        if(thePig == NULL)
        {
            std::cout << "Could not create texture! : " << SDL_GetError() <<std::endl;
        }
        //Set the height and width. -> ->(Remember that theSurface is a pointer)
        tWidth = theSurface->w;
        tHeight = theSurface->h;
        //We are going to recycle our global "Surface"
        SDL_FreeSurface(theSurface);
        theSurface = NULL;
    }


    //Here is where we copy thePig into sTexture: If anything went wrong, thePig would have been NULL
    sTexture = thePig;
    return sTexture != NULL;
}




/////////////////////////////////////
////////   Game Functions    ////////
/////////////////////////////////////

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
