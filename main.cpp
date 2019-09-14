#include "radLED.h"
#include "input.h"
#include "character.h"

void doOneFrame() {
	std::map<WiiButton, ButtonState> map = getMap();
	pixel[][] pixelArray = GameFrame(map); //idk how namespaces work so maybe this is wrong
	for (int r = 0; r < numRows; r++) {
		for (int c = 0; c < numCols; c++) {
			pixel pix = pixelArray[r][c];
			sendByte(pix.r);
			sendByte(pix.g);
			sendByte(p.b);
		}
	}
}

void newGame() {
	Character player(PLAYER_START_LOCATION, PLAYER_START_HP);
	Character[] enemies
		while (True) {
			doOneFrame(player, enemies);
			sleep(1); //so that frames only update once a second
		}
}

int main() { //HERE IS THE MAIN
	//while (True) { //need some sort of escape clause here
	//	doOneFrame();
	//}
	newGame();
}



