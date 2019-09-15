struct Character
{
	int location;
	int hp;
	bool hit;

    Character(int locationValue, int hpValue, bool hitValue)
        : location(locationValue)
        , hp(hpValue)
		, hit(hitValue)
    { }
};

struct Player : public Character {
	bool isRechargeMode;
	int attackLockOut;

    Player (int location, int hp, bool hit, bool isRechargeModeValue, int attackLockOutValue)
        : Character(location, hp, hit)
        , isRechargeMode(isRechargeModeValue)
        , attackLockOut(attackLockOutValue)
    { }
};
