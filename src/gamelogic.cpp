#include <unistd.h>
#include <vector>
#include <cstring>
#include <map>
#include "gamelogic.h"
#include "render.h"
#include "input.h"
#include "character.h"

using std::map;

int currCol = 0;

static constexpr int PLAYER_START_LOCATION = 0;
static constexpr int PLAYER_START_HP = 50; //max hp is 100
static constexpr int PLAYER_MAX_HP = 255;
static constexpr int ENEMY_START_HP = 255;
static constexpr double ENEMY_PROBABILITY = .5;
static constexpr int ENEMY_DISTANCE_RANGE = 5;
static constexpr int ATTACK_POWER = 35;
static constexpr double REFRESH_RATE = 0.5;
static constexpr int MAX_ATTACK_LOCKOUT = 10;

static constexpr int PLAYER_HEALTH_LOSS = 26;
static constexpr int ENEMY_HEALTH_LOSS = 52;


Frame makeFrame(InputState input, Player *player, std::vector<Character> enemies)
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
	bool playerAttacking = false;
	if (input[ONE].isPressed)
	{
		//attack if in normal mode
		if (!player.isRechargeMode)
		{
			//attack
			if (player.attackLockOut == 0)
			{
				playerAttacking = true;
				player.attackLockOut = MAX_ATTACK_LOCKOUT;
			}
		}
	}
	int numEnemies = enemies.size();
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].location == player->location) {
			if (!player->isRechargeMode && playerAttacking) {
				enemies[i].hp -= ENEMY_HEALTH_LOSS;
				if (enemies[i].hp <= 0) {
					enemies.erase(enemies.begin() + i);
					numEnemies -= 1;
					i -= 1;
				}
			}
			else if (!player->isRechargeMode && !playerAttacking) {
				player.hp -= PLAYER_HEALTH_LOSS;
			}
			else if (player->isRechargeMode) {
				player.hp = 0;
				//TODO death
			}
		}
	}

    if (input[TWO].isPressed)
    {
		player.isRechargeMode = !player.isRechargeMode;
    }
    else if (input[B].isHeld) 
    {
        //recharging
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

void doOneFrame(Player *player, std::vector<Character> enemies) {
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
	Player player{ PLAYER_START_LOCATION, PLAYER_START_HP, false, 0 };
	std::vector<Character> enemies;
	
	
	while (true) {
		doOneFrame(&player, enemies);
		int sleepTimeInMilli = 100;
		usleep(sleepTimeInMilli); //so that frames only update once a second
	}
}
