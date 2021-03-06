#include "Globals.h"

//
//Matts Win Function
//

bool win_logic(int* slots, int size, int flag) {

	//up & down

	int nums[2] = {(flag-3 < 0 ? flag+3 : flag-3), (flag-3 < 0 ? flag+6 : flag-6 < 0 ? flag+3 : flag-6)};

	bool f1 = false;
	bool f2 = false;
	bool base = false;

	for(int i = 0;i < size;i++) {
		int slot = slots[i];

		if(slot == flag) base = true;

		if(slot == nums[0])
			f1 = true;
		else if(slot == nums[1])
			f2 = true;
	}

	if(!base)
		return false;

	if(f1 && f2)
		return true;

	//left & right

	int row = ((flag+1) / 3 < 1 ? 1 : (flag+1) / 3 < 2 ? 2 : 3);
	int min = (row == 1 ? TILE_TOP_LEFT : row == 2 ? TILE_CENTER_LEFT : TILE_BOTTOM_LEFT);
	int max = min + 2;

	if(flag >= min) {
		nums[0] = (flag-1 < min ? flag+1 : flag-1);
		nums[1] = (flag-1 < min ? flag+2 : flag-2 < min ? flag+1 : flag-2);

		f1 = false;
		f2 = false;

		for(int i = 0;i < size;i++) {
			int slot = slots[i];

			if(slot == nums[0])
				f1 = true;
			else if(slot == nums[1])
				f2 = true;
		}

		if(f1 && f2) {
			return true;
		}
	}

	//diagonal

	bool possible = flag % 2 == 0;

	if(!possible) return false;

	if(flag == TILE_CENTER_MIDDLE) {
		bool tleft = false, tright = false, bleft = false, bright = false;

		for(int i = 0;i < size;i++) {
			int slot = slots[i];

			if(slot % 2 == 0 && slot != TILE_CENTER_MIDDLE) {
				switch(slot) {
					case TILE_TOP_LEFT:
						tleft = true;
						break;
					case TILE_TOP_RIGHT:
						tright = true;
						break;
					case TILE_BOTTOM_LEFT:
						bleft = true;
						break;
					case TILE_BOTTOM_RIGHT:
						bright = true;
						break;
				}
			}
		}
		if(tleft && bright) {
			return true;
		} else if(tright && bleft) {
			return true;
		}
	}

	return false;
}

bool IWin(char givenCharacter) {
	int spots[TILE_TOTAL];
	int index = 0;

	for(int i = 0; i < TILE_TOTAL; i++) {
		if(tTiles[i].CallC() == givenCharacter) {
			spots[index] = i;
			index++;
		}
	}

	if(index < 3) return false;

	for(int i = 0;i < TILE_TOTAL;i++) {
		if(win_logic(spots, index, i)) return true;
	}

	return false;
}





/////////////////////////////////////
////////   Our Game Loop     ////////
/////////////////////////////////////

void Play() {
	//Use a quit flag to start a game loop
	bool quit = false;
	SDL_Event event;
	Uint32 lastEvent = 0;


	while(!quit) {
		//While there are events to pull...
		while(SDL_PollEvent(&event) != 0) {
			//Handle each one
			//SDL_QUIT is something like hitting the Red X on the top right of screen. Also added support for ESC quit
			if(event.type == SDL_QUIT) {
				quit = true;
			}

			if(event.key.keysym.sym == SDLK_ESCAPE) {
				quit = true;
				//Menu();
				//continue;
			}
			for(int i = 0; i != TILE_TOTAL; ++i) {
				tTiles[i].HandleEvent(&event, lastEvent);
			}
			//std::cout << lastEvent <<std::endl;
		}

		if(IWin('X')) {
			std::cout << "\n\nX Wins" << std::endl;
			ResetGame();
		} else if(IWin('O')) {
			std::cout << "\n\nO Wins" << std::endl;
			ResetGame();
		}

		//If its not my turn, let the computer go
		if(isMyTurn == false) {
			ComputersTurn();
		}



		//Clear screen with white
		SDL_SetRenderDrawColor(theRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(theRenderer);

		DrawBoard();

		SDL_RenderPresent(theRenderer);


	}
	//Quit is true at this point so we return
	return;
}

const int slotsTaken(char c) {
	int size = 0;
	for(int i = 0; i < TILE_TOTAL; i++) {
		if(tTiles[i].CallC() == c) {
			size++;
		}
	}
	return size;
}

void findAttemptedPath(int*& slots, int size, int& tset) {
	for(int i = 0;i < size;i++) {
		int flag = slots[i];

		int nums[2] = {(flag-3 < 0 ? flag+3 : flag-3), (flag-3 < 0 ? flag+6 : flag-6 < 0 ? flag+3 : flag-6)};

		bool f1 = false;
		bool f2 = false;

		for(int i = 0;i < size;i++) {
			int slot = slots[i];

			if(slot == nums[0])
				f1 = true;
			else if(slot == nums[1])
				f2 = true;
		}

		if((!f1 && f2) || (f1 && !f2)) {
			if(!f1 && tTiles[nums[0]].CallC() == ' ') {
				tset = nums[0];
				return;
			}
			if(!f2 && tTiles[nums[1]].CallC() == ' ') {
				tset = nums[1];
				return;
			}
		}

		//left & right

		int row = ((flag+1) / 3 < 1 ? 1 : (flag+1) / 3 < 2 ? 2 : 3);
		int min = (row == 1 ? TILE_TOP_LEFT : row == 2 ? TILE_CENTER_LEFT : TILE_BOTTOM_LEFT);
		int max = min + 2;

		if(flag >= min) {
			nums[0] = (flag-1 < min ? flag+1 : flag-1);
			nums[1] = (flag-1 < min ? flag+2 : flag-2 < min ? flag+1 : flag-2);

			f1 = false;
			f2 = false;

			for(int i = 0;i < size;i++) {
				int slot = slots[i];
				if(slot == nums[0])
					f1 = true;
				else if(slot == nums[1])
					f2 = true;
			}

			if((!f1 && f2) || (f1 && !f2)) {
				if(!f1 && tTiles[nums[0]].CallC() == ' ') {
					tset = nums[0];
					return;
				}
				if(!f2 && tTiles[nums[1]].CallC() == ' ') {
					tset = nums[1];
					return;
				}
			}
		}

		//diagonal

		bool possible = flag % 2 == 0;

		if(!possible) { tset = -1; return; }

		bool middle = false, tleft = false, tright = false, bleft = false, bright = false;

		for(int i = 0;i < size;i++) {
			int slot = slots[i];

			if(slot % 2 == 0) {
				switch(slot) {
					case TILE_TOP_LEFT:
						tleft = true;
						break;
					case TILE_TOP_RIGHT:
						tright = true;
						break;
					case TILE_CENTER_MIDDLE:
						middle = true;
						break;
					case TILE_BOTTOM_LEFT:
						bleft = true;
						break;
					case TILE_BOTTOM_RIGHT:
						bright = true;
						break;
				}
			}
		}

		if(!tleft && !tright && !middle && !bleft && !bright) {
			tset = -1;
			return;
		}

		if(middle) {
			if(tleft)
				tset = (tTiles[TILE_BOTTOM_RIGHT].CallC() == ' ' ? TILE_BOTTOM_RIGHT : -1);
			else if(bright)
				tset = (tTiles[TILE_TOP_LEFT].CallC() == ' ' ? TILE_TOP_LEFT : -1);
			else if(tright)
				tset = (tTiles[TILE_BOTTOM_LEFT].CallC() == ' ' ? TILE_BOTTOM_LEFT : -1);
			else if(bleft)
				tset = (tTiles[TILE_TOP_RIGHT].CallC() == ' ' ? TILE_TOP_RIGHT : -1);
			else
				tset = -1;

			return;
		} else if(tTiles[TILE_CENTER_MIDDLE].CallC() == ' ') {
			if((tleft && bright) || (tright && bleft)) {
				tset = TILE_CENTER_MIDDLE;
				return;
			}
		}
	}
	tset = -1;
}

void ComputersTurn() {
	//Boolean to test if there are any spots left
	bool gameFinished = true;
	int spots = 0;

	for(int i = 0; i!= TILE_TOTAL; ++i) {
		//If any of the tiles are open for selection...
		if(tTiles[i].isOpen()) {
			spots++;
			gameFinished = false;   //That means the game isnt finished
		}
	}
	//Debugging V V
	std::cout << "There are " << spots << " spots before COM move" <<std::endl;

	if(gameFinished) {
		ResetGame();
	} else {
		//idea is the tile that the computer will ponder about
		int idea = 0, index = 1;
		int taken = slotsTaken('X');
		int* slots = new int[taken];
		if(taken > 1) {
			index = 0;
			for(int i = 0; i < TILE_TOTAL; i++) {
				if(tTiles[i].CallC() == 'X') {
					slots[index] = i;
					index++;
				}
			}
			findAttemptedPath(slots, taken, idea);

			if(idea == -1) taken = 0;
		}
		
		//initialize the random number generator - every time this function is called
		srand(time(NULL));

		int opened = slotsTaken(' ');

		int* left = new int[opened];
		index = 0;

		for(int i = 0; i < TILE_TOTAL; i++) {
			if(tTiles[i].CallC() == ' ') {
				left[index] = i;
				index++;
			}
		}

		index = 1;

		while(true) {

			//Number 0-8
			if(taken <= 1)
				idea = left[rand() % opened];

			//Debug V V
			std::cout << "Idea Number " << index << "(" << taken << ")" << ": " << idea << std::endl;

			//If the tile that the COM is thinking about - Is Open for selection..
			if(tTiles[idea].isOpen()) {
				//Set the player = O - Marked = true - currentSprite = SPRITE_COM -
				tTiles[idea].SetChar('O');
				tTiles[idea].SetMark();
				tTiles[idea].SetSprite(SPRITE_COM);

				//Its now my turn
				isMyTurn = true;

				//break out of the While(true)
				break;
			} else {
				//If the idea Tile was not available - Increase the index
				index++;
				if(taken > 1) {
					findAttemptedPath(slots, taken, idea);
					if(idea == -1) taken = 0;
				}
				//And restart the While(true) loop
				continue;
			}
		}

		delete[] slots;
		delete[] left;

	}


}


void ResetGame() {
	std::cout << "Game over!" << std::endl;
	isMyTurn = true;
	for(int i = 0; i != TILE_TOTAL; ++i) {
		tTiles[i].Reset();
	}
}
/////////////////////////////////////
////////   tTile Functions   ////////
/////////////////////////////////////


tTile::tTile() {
	//Initialization
	currentPosition.x = 0;
	currentPosition.y = 0;
	currentPosition.h = TILE_H;
	currentPosition.w = TILE_W;

	player = ' ';
	marked = false;
	currentSprite = SPRITE_NONE;
}

char tTile::CallC() {
	return player;
}

void tTile::Reset() {
	//Reset the Tile - (Reset game)
	player = ' ';
	marked = false;
	currentSprite = SPRITE_NONE;
}
void tTile::SetMark() {
	marked = true;
}

void tTile::SetChar(char c) {
	player = c;
}

bool tTile::isOpen() {
	return marked == false;
}
void tTile::SetSprite(tSpriteFlag newSprite) {
	currentSprite = newSprite;
}

int tTile::GetW() {
	return currentPosition.w;
}

int tTile::GetH() {
	return currentPosition.h;
}

int tTile::GetX() {
	return currentPosition.x;
}

int tTile::GetY() {
	return currentPosition.y;
}

void tTile::SetLocation(int x, int y) {
	currentPosition.x = x;
	currentPosition.y = y;
}

void tTile::Render() {
	theSpriteSheet.RenderX(&currentPosition, &tSprites[currentSprite]);
}

void tTile::HandleEvent(SDL_Event* event, Uint32& lastEvent) {

	//If the last event was SDL_MOUSEBUTTONDOWN - And


	//If our event relates to the mouse...
	if(event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP) {
		//We need to store - and fetch - the mouse coordinates for tests
		int mouseX = 0, mouseY = 0;
		SDL_GetMouseState(&mouseX, &mouseY);

		//If Focus becomes true, that means the mouse is over the Tile
		bool focus = false;

		//If the MouseX is in between the X coordinates of the tile....
		if(mouseX >= currentPosition.x && mouseX <= currentPosition.x + currentPosition.w) {
			//AND... if the MouseY is in between the Y coordinates of the tile...
			if(mouseY >= currentPosition.y && mouseY <= currentPosition.y + currentPosition.h) {
				//Then... we set the focus to true (Time to handle Events)
				focus = true;
			}
		}

		//If The mouse is placed on the tTile : Handle the event!
		if(focus == true) {
			switch(event->type) {
				case SDL_MOUSEMOTION:
					//Only change the current sprite to SPRITE_OVER is the last event was NOT
					if(lastEvent == SDL_MOUSEBUTTONDOWN) {
						if(!marked) {
							currentSprite = SPRITE_CLICK;
						}

					} else {
						if(!marked) {
							currentSprite = SPRITE_OVER;
							lastEvent = SDL_MOUSEMOTION;
						}

					}


					break;

				case SDL_MOUSEBUTTONDOWN:
					if(!marked) {
						currentSprite = SPRITE_CLICK;
					}

					lastEvent = SDL_MOUSEBUTTONDOWN;
					break;

				case SDL_MOUSEBUTTONUP:
					if(!marked) {
						currentSprite = SPRITE_RELEASE;
						marked = true;
						isMyTurn = false;
						player = 'X';
					}

					lastEvent = SDL_MOUSEBUTTONUP;
					break;
			}
		} else //If the focus is not set on this tile...
		{
			//And if the tile has not been marked...
			if(!marked) {
				//Set the current sprite to "Blank"
				currentSprite = SPRITE_NONE;
			}

		}
	}
}

/////////////////////////////////////
//////// tTexture Functions  ////////
/////////////////////////////////////
void tTexture::Render(int x, int y, SDL_Rect* clip = NULL) {
	//This is the box on location of the screen we will render to
	SDL_Rect renderLocation;

	//Use the x and y that were supplied
	renderLocation.x = x;
	renderLocation.y = y;

	//And use the height and width of the full image
	renderLocation.h = tHeight;
	renderLocation.w = tWidth;

	//Unless you want to supply a clip from a sprite sheet, then you would want the width/height of the clip instead of the height / width of the WHOLE sprite sheet
	if(clip != NULL) {
		//Set the new H/W
		renderLocation.h = clip->h;
		renderLocation.w = clip->w;
	}

	SDL_RenderCopy(theRenderer, sTexture, clip, &renderLocation);

}

int tTexture::GetHeight() {
	return tHeight;
}

int tTexture::GetWidth() {
	return tWidth;
}

void tTexture::RenderX(SDL_Rect* target, SDL_Rect* clip) {
	//We pass two Rects to this function
	//target is the Rectangle on the screen that you will occupy
	//clip is the rectangle that you select a sprite from the sprite sheet
	SDL_RenderCopy(theRenderer, sTexture, clip, target);
}

tTexture::tTexture() {
	sTexture = NULL;
	tHeight = 0;
	tWidth = 0;
}

tTexture::~tTexture() {
	Deallocate();
}

void tTexture::Deallocate() {
	if(sTexture != NULL) {
		SDL_DestroyTexture(sTexture);
		sTexture = NULL;
		tHeight = 0;
		tWidth = 0;
	}

}

bool tTexture::LoadImage(std::string filename) {
	//This function uses the surface to load an image, then create a texture out of it

	Deallocate();

	//Create a "Guinna Pig" texture
	SDL_Texture* thePig = NULL;

	//Load a BMP into theSurface. BMP Is the only file type that native SDL2 can import. W(e will have to add SDL2_image to import other formats)
	theSurface = SDL_LoadBMP(filename.c_str()); //SDL_LoadBMP expects a ( char[] )

	//Debug VV
	if(theSurface == NULL) {
		std::cout << "Could not Load image! : " << SDL_GetError() <<std::endl;
	} else {
		//theTexture = SDL_CreateTextureFromSurface(theRenderer, theSurface);
		thePig = SDL_CreateTextureFromSurface(theRenderer, theSurface);

		//Debug VV
		if(thePig == NULL) {
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
////////   Game Functions    ////////---------------------------
/////////////////////////////////////
void DrawMenu() {
	SDL_SetRenderDrawColor(theRenderer, 0x00, 0x00, 0x00, 0xFF);

	SDL_Rect MenuSize;
	MenuSize.x = SCREEN_W / 4;
	MenuSize.y = SCREEN_H / 4;
	MenuSize.w = SCREEN_W / 2;
	MenuSize.h = SCREEN_H / 2;

	SDL_RenderFillRect(theRenderer, &MenuSize);

}

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

				//Woohoo everything worked!
				return true;
			}
		}
	}
}

/////////////////////////////////////
////////  Load Game Content  ////////
/////////////////////////////////////

bool LoadContent() {
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

	std::cout << "Tile W : " << TILE_W << "\nTile H : " << TILE_H << std::endl;
	return true;
}




void Close() {
	//We have to make sure we deallocate memory we have used

	SDL_DestroyWindow(theWindow);
	SDL_DestroyRenderer(theRenderer);
	theSpriteSheet.Deallocate();

	theWindow = NULL;
	theRenderer = NULL;

	//Now that the variables are taken care of.... Quit SDL systems
	SDL_Quit();
}
