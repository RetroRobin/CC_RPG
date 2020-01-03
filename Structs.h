#pragma once
//Contains additional structures needed for game
#include <string>
using namespace std;

enum TARGET { SINGLE, ALL, ADJACENT, RANDOM, SELF, FRIEND };
enum atkType { SLH, FRC, FIR, ICE, ELC, WND, SON, LIF, NEC, ELD, WPNTYPE1, WPNTYPE2 };
enum atkMeth { MELEE, PROJECTILE, ENERGY, WEAPON };
enum atkSPC { UNKNOWN, SPELL, WEAPON_STR, WEAPON_USE }; //Special rules to the attacks
enum TRIGGER { BORED, CLOSE, ENERGY2, SIN_ATTACK, DAMAGE, TURNUP};

void cleanup();
void sleep(float);

class attack
{
public:
	float mult;
	int amount; //Amount of times an attack connects. Also used to see whether or not a healing ability can heal statuses
	//HEALING INDEX: 0 = only health  1 = resurrection
	int MPcost;
	int STAMcost;
	TARGET victim;
	bool magic;
	bool ATK;
	bool support;
	int accuracy;
	int statEffect = 0; //0 = nothing/SCAN, 1 = PATK, 2 = MATK, 3 = PDEF, 4 = MDEF,
	atkType type1;
	atkType type2;
	atkMeth delivery;
	atkSPC rules;
	string name;
	string TAG;
	string DESC;
	//int animNum;
public:
	attack();
	attack(int);
	void describe();
	void printOut();
};

class reaction
{
public:
	int TarNum = -1;
	TARGET victim;
	TRIGGER activate;
	int effect; //-1 = INVALID, 0 = use skill, 1 = defend, 2 = absorb, 3 = dual tech, 4 = special use
	float mult; //effectiveness multiplier for succeeding
	int special; //For selecting an item. Stores the address of the item in the array.
	attack Skill;
	string name;
	string TAG;
	string DESC;
public:
	reaction();
	reaction(int);
	void describe();
};

class weapon
{
public:
	int ATKpow;
	int Weight; //affects STAM cost
	int USER; // 0=Eric 1=Chloe 2=Abigail 3=Andrew 4=Jasper 5=Rick	6=Enemy
	string name;
	atkType elem1;
	atkType elem2;
	atkMeth strike;
public:
	weapon();
	weapon(int);
};

class item
{
public:
	string name;
	int maxAmount;
	int currAmount;
	int UseEffort; //STAM cost to use
	int effect; //0 = HP, 1 = MP, 2 = STAM, 3 = Revive, 4 = STATUS 2, ect
	int potency; //points it heals or hurts
	int ID;
	bool buddy; //Determines if attacking or helping a friend
	atkType elem;
	atkMeth usage;
	string DESC;
public:
	item();
	item(int);
	void describe();
};

void SetMove(int, attack[10], reaction[8]);