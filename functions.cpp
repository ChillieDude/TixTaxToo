#include "Globals.h"

/////////////////////////////////////
////////   Our Game Loop     ////////
/////////////////////////////////////







/////////////////////////////////////
////////  Load Game Content  ////////
/////////////////////////////////////

bool LoadContent() {
    LoadButtons();
    LoadWelcomeStrings();
    SetMenu();

	if(!theSpriteSheet.LoadImage("SpriteSheet.bmp")) {
		std::cout << "Oops" <<std::endl;
		return false;
	}

	//While we load our content, we should check and see if the resolution isnt perfect

	if((SCREEN_W - LINE_W * (LINE_TOTAL / 2)) % ROWS_TOTAL != 0) {
		std::cout << "Non-Critical Error: Screen width isnt perfect: " << (SCREEN_W - LINE_W * (LINE_TOTAL / 2)) % ROWS_TOTAL << " unused Pixels" << std::endl;

	}
	if((SCREEN_H - LINE_W * (LINE_TOTAL / 2)) % ROWS_TOTAL != 0) {
		std::cout << "Non-Critical Error: Screen height isnt perfect: " << (SCREEN_H - LINE_W * (LINE_TOTAL / 2)) % ROWS_TOTAL << " unused Pixels" << std::endl;
	}

	//This sprite sheet will read right left to right, sprite size being 100
	for(int i = 0; i!= SPRITE_TOTAL; ++i) {
		tSprites[i].h = 100;
		tSprites[i].w = 100;
		tSprites[i].y = 0;
		tSprites[i].x = i*100;
	}

	//Set the location of all tiles
	int x = 0, y = 0;
	for(int i = 0; i != TILE_TOTAL; ++i) {
		if(x == ROWS_TOTAL) {
			++y;
			x = 0;
		}
		tTiles[i].SetLocation(x*TILE_W + x*LINE_W, y*TILE_H + y*LINE_W);
		++x;
		//DEBUG
		//std::cout << "Tile " << i << "\t: X = " << tTiles[i].GetX() << "\t\t& Y = " << tTiles[i].GetY() << "  \t W = " << tTiles[i].GetW() << " & H = " << tTiles[i].GetH() << std::endl;

	}

	//Now set the location for the Lines
	x = 1, y = 1;
	for(int i = 0; i != LINE_TOTAL; ++i) {
		//First all of the Horizontal lines
		if(x <= LINE_TOTAL / 2) {
			tLines[i].x = TILE_W * x + LINE_W * (x-1);
			tLines[i].y = 0;
			tLines[i].h = SCREEN_H;
			tLines[i].w = LINE_W;

			++x;
		} else {
			tLines[i].x = 0;
			tLines[i].y = TILE_H * y + LINE_W * (y-1);
			tLines[i].h = LINE_W;
			tLines[i].w = SCREEN_W;

			++y;
		}

	}
    //Debug
	//std::cout << "Tile W : " << TILE_W << "\nTile H : " << TILE_H << std::endl;
	return true;
}




/////////////////////////////////////
////////   Game Functions    ////////---------------------------
/////////////////////////////////////


void DrawBoard() {
	//Change the renderer color
	SDL_SetRenderDrawColor(theRenderer, 0x00, 0x00, 0x00, 0xFF); //Color Black - Full Alpha

	//Draw the Lines
	for(int i = 0; i != LINE_TOTAL; ++i) {
		SDL_RenderFillRect(theRenderer, &tLines[i]);
	}

	//Draw the Tiles
	for(int i = 0; i!= TILE_TOTAL; ++i) {
		tTiles[i].Render();
	}


}


bool InitSDL() {
	//When SDL cannot be initialized, it will return a value of -1
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		std::cout << "Could not initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	else {
		//If we are here (now that SDL is started) we can call an SDL Function

		//SDL_CreateWindow() Takes 5 arguments.
		//Name of Window, The X Value, Y Value, Width, Height, and a lastly: Flags (We wont worry about the x, y, or flags for now)
		theWindow = SDL_CreateWindow("Window!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
		//If anything went wrong, theWindow (And Any pointer as such) will be NULL
		if(theWindow == NULL) {
			std::cout << "Could not create the window! ERROR" <<SDL_GetError() << std::endl;
			return false;
		} else {
			//Creating a Renderer is similar: You supply a window, an "index", and flags
			//When can omit the SDL_RENDERER_ACCELERATED, and the program will still run, but we want hardware acceleration
			//-1 is the first Renderer to accept flags:
			//More info on CreateRenderer() can be found here: http://wiki.libsdl.org/SDL_CreateRenderer
			theRenderer = SDL_CreateRenderer(theWindow, -1, SDL_RENDERER_ACCELERATED);

			//Again, if anything goes wrong with a pointer, it will point to NULL
			if(theRenderer == NULL) {
				std::cout << "Something Went Wrong! Render Error" << SDL_GetError() <<std::endl;
				return false;
			} else {
				//If we are here, then the Window is created, the renderer is properly attached to the window
				//Lets set the Renderer Color
				Uint8 red = 255, blue =255, green = 0xFF, alpha = 0xFF;
				SDL_SetRenderDrawColor(theRenderer, red, green, blue, alpha);
				//Accepts the Renderer you want to use (we only will use one in our first few projects)
				//Along with 4 8bit-Unsigned-Integers (Uint8)
                    if(TTF_Init()== -1) return false;
                    else
                    {
                        theFont = TTF_OpenFont("8bitlim.ttf", 32);
                    }
				//Woohoo everything worked!
				return true;
			}
		}
	}
}

void ResetGame() {
	std::cout << "Game over!" << std::endl;
	isMyTurn = true;
	for(int i = 0; i != TILE_TOTAL; ++i) {
		tTiles[i].Reset();
	}
}

void Close() {
	//We have to make sure we deallocate memory we have used

	SDL_DestroyWindow(theWindow);
	SDL_DestroyRenderer(theRenderer);
	theSpriteSheet.Deallocate();
    DestroyWelcomeTextures();

	theWindow = NULL;
	theRenderer = NULL;

	//Now that the variables are taken care of.... Quit SDL systems
	SDL_Quit();
    TTF_Quit();
}
