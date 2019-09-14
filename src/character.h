#pragma once
final int PLAYER_START_LOCATION = 0;
final int PLAYER_START_HP = 50; //max hp is 100
final int PLAYER_MAX_HP = 255;
final int ENEMY_START_HP = 255;
final double ENEMY_PROBABILITY = .5;
final int ENEMY_DISTANCE_RANGE = 5;
final int ATTACK_POWER = 35;
final double REFRESH_RATE = 0.5;

struct Character {
	int location;
	int HP;
}