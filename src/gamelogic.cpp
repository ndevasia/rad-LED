#include <unistd.h>
#include "gamelogic.h"
#include "render.h"
#include "input.h"

int currCol = 0;

struct Character
{
    int location;
    int hp;
};

static constexpr int PLAYER_START_LOCATION = 0;
static constexpr int PLAYER_START_HP = 50; //max hp is 100
static constexpr int PLAYER_MAX_HP = 255;
static constexpr int ENEMY_START_HP = 255;
static constexpr double ENEMY_PROBABILITY = .5;
static constexpr int ENEMY_DISTANCE_RANGE = 5;
static constexpr int ATTACK_POWER = 35;
static constexpr double REFRESH_RATE = 0.5;

Character player {PLAYER_START_LOCATION, PLAYER_START_HP};
Character enemies[3];

Frame makeFrame(InputState input)
{
    Frame frame;

    if (input[RIGHT].isHeld)
    {
        currCol += 1;
        
    }
    else if(input[LEFT].isHeld && currCol > 0)
    {
        currCol -= 1;
    }

    if (input[TWO].isPressed)
    {
        //attacking code
    }
    else if (input[B].isHeld) 
    {
        //recharge code
    }

    for (int i = 0; i < frame.size(); ++i)
    {
        frame[i] = {255, 0, 0};
    }

    //frame[currCol] = { 0, 255, 0 };

    return frame; 
}

void doOneFrame() {
	InputState input = getButtonStates();
	Frame frame = makeFrame(input);
    renderFrame(frame);
}

void newGame() {
	while (true) {
		doOneFrame();
		sleep(1); //so that frames only update once a second
	}
}
