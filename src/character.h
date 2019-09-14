struct Character
{
	int location;
	int hp;
};

struct Player : public Character {
	bool isRechargeMode;
	int attackLockOut;
};