struct Character
{
	int location;
	int hp;

    Character(int locationValue, int hpValue)
        : location(locationValue)
        , hp(hpValue)
    { }
};

struct Player : public Character {
	bool isRechargeMode;
	int attackLockOut;

    Player (int location, int hp, bool isRechargeModeValue, int attackLockOutValue)
        : Character(location, hp)
        , isRechargeMode(isRechargeModeValue)
        , attackLockOut(attackLockOutValue)
    { }
};
