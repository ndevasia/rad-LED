#include <unistd.h>
#include <cstring>
#include <map>
#include "gamelogic.h"
#include "render.h"
#include "input.h"

using std::map;

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
    memset(frame.data(), 0, sizeof frame);

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

    frame[currCol] = { 0, 255, 0 };

    return frame; 
}

static map<int, const char *> buttonNames
{
    {UP, "UP"},
    {RIGHT, "RIGHT"},
    {DOWN, "DOWN"},
    {LEFT, "LEFT"},
    {A, "A"},
    {B, "B"},
    {ONE, "ONE"},
    {TWO, "TWO"}
};

void doOneFrame() {
	InputState input = getButtonStates();

    for (int i = 0; i < LENGTH; ++i)
    {
        printf("Button %s: isPressed: %d, isHeld: %d\n",
               buttonNames[i],
               input[i].isPressed,
               input[i].isHeld);
    }

    printf("\n");

	Frame frame = makeFrame(input);
    renderFrame(frame);
}

void newGame() {
	while (true) {
		doOneFrame();
		sleep(1); //so that frames only update once a second
	}
}
