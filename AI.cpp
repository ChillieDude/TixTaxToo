#include "Globals.h"

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
