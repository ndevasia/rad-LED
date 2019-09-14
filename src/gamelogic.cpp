#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <cstring>
#include <map>
#include "gamelogic.h"
#include "render.h"
#include "input.h"
#include "character.h"
#include "globals.h"

using std::map;

int currCol = 0;

static constexpr int PLAYER_START_LOCATION = 0;
static constexpr int PLAYER_START_HP = 50; //max hp is 100
static constexpr int PLAYER_MAX_HP = 255;
static constexpr int ENEMY_START_HP = 255;
static constexpr double ENEMY_PROBABILITY_PERCENT = 50;
static constexpr int ENEMY_DISTANCE_RANGE = 5;
static constexpr int ATTACK_POWER = 35;
static constexpr double REFRESH_RATE = 0.5;
static constexpr int MAX_ATTACK_LOCKOUT = 10;
static constexpr int MAX_ENEMY_COUNT = 3;
static constexpr int BOUNCE_DISTANCE = 2;

static constexpr int PLAYER_HEALTH_LOSS = 26;
static constexpr int ENEMY_HEALTH_LOSS = 52;
static constexpr int RECHARGE_AMOUNT = 26;


Frame makeFrame(InputState input, Player *player, std::vector<Character> enemies)
{
	bool endGame = false;
	bool dead = false;
    
	
	//player movement
    if (input[RIGHT].isHeld && player->location < cols-1)
    {
        player->location += 1;
        
    }
    else if(input[LEFT].isHeld && player->location > 0)
    {
        player->location -= 1;
    }

	//fighting
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
	bool playerHit = false;
	int numEnemies = enemies.size();
	for (int i = 0; i < enemies.size(); i++)
	{
		if (enemies[i].location == player->location) 
		{
			if (!player->isRechargeMode && playerAttacking) 
			{
				enemies[i].hp -= ENEMY_HEALTH_LOSS;
				if (enemies[i].hp <= 0) 
				{
					enemies.erase(enemies.begin() + i);
					numEnemies -= 1;
					i -= 1;
				}
			}
			else if (!player->isRechargeMode && !playerAttacking) 
			{
				player.hp -= PLAYER_HEALTH_LOSS;
				playerHit = true;
			}
			else if (player->isRechargeMode) 
			{
				player.hp = 0;
				endGame = true;
				dead = true;
			}
			if (player->location > 0)
			{
				player->location -= BOUNCE_DISTANCE;
			}
			if (enemies[i].location < col - 1)
			{
				enemies[i].location += BOUNCE_DISTANCE;
			}
		}
	}

	boolean rechargingAllowed = true;
	//switch recharge mode
    if (input[TWO].isPressed)
    {
		player->isRechargeMode = !player->isRechargeMode;
		rechargingAllowed = false;
    }
    
	//player recharging
	if (input[B].isPressed && player->isRechargeMode && rechargingAllowed) 
	{
		player->hp += RECHARGE_AMOUNT;
	}

	//enemy movement
	for (int i = 0; i < enemies.size(); i++) 
	{
		int enemyMovement = (rand() % 2) * 2 - 1;
		enemies[i].location += enemyMovement;
	}
	
	//enemy creation
	bool createEnemy = (rand() % 100) < ENEMY_PROBABILITY_PERCENT;
	if (createEnemy && enemies.size() < MAX_ENEMY_COUNT) 
	{
		int startLocation = player->location + 1 + (rand() % ENEMY_DISTANCE_RANGE);
		Character enemy{ startLocation, ENEMY_START_HP };
		enemies.push_back(enemy);
	}

	if (player->location == cols - 1) 
	{
		endGame = true;
		dead = false;
	}


    return frameFromPixels(&player, enemies, endGame, dead, playerHit); 
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

Frame frameFromPixels(Player *player, std::vector<Character> enemies, bool endGame, bool dead, bool playerHit) {
	Frame frame;
	memset(frame.data(), 0, sizeof frame);

	if (endGame && dead) 
	{
		//all red
		for (int i = 0; i < cols; i++) 
		{
			frame[currCol] = { 255, 0, 0 };
		}
	}
	else if (endGame && !dead) 
	{
		//all green
		for (int i = 0; i < cols; i++) 
		{
			frame[currCol] = { 0,255, 0 };
		}
	}
	else {
		//player
		if (!player->isRechargeMode && !playerHit) 
		{
			frame[player->location] = { 0, 0, 255 };
		}
		else 
		{
			frame[player->location] = { 255 - player->hp, player->hp, 0 };
		}

		//enemies
		for (int i = 0; i < enemies.size(); i++) 
		{
			int enemyHealth = enemies[i].hp;
			frame[enemies[i].location] = { enemyHealth, enemyHealth, enemyHealth };
		}

		//end square
		frame[cols - 1] = { 0, 255, 0 };
	}
	return frame;
}

void doOneFrame(Player *player, std::vector<Character> enemies) 
{
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

void newGame() 
{
	Player player{ PLAYER_START_LOCATION, PLAYER_START_HP, false, 0 };
	std::vector<Character> enemies;
	
	
	while (true) 
	{
		doOneFrame(&player, enemies);
		int sleepTimeInMilli = 100;
		usleep(sleepTimeInMilli); //so that frames only update once a second
	}
}
