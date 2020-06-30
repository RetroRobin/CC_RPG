#pragma once
//All entities and functions required for combat are here.
#include "Structs.h"
#include <string>
using namespace std;

enum BADSTATUS { FINE, DEAD, N_A, TIRED};
enum GOODSTATUS { NONE, PFIRE1, PFIRE2, PFIRE3, PICE1, PELEC1, PWIND1, PLIFE1, PNEC1, REGEN};
enum AI {Q_Q, AGG, SUP, DEF, REAC, SMRT, PSN, BER, PAT, INS, undecided, BOSS1};
enum RESIST {WEAK, NORM, RESISTANT, IMMUNE, REFLECT, ABSORB};

class BattleEntity;
class PCharacter;
class ECharacter;
class attack;
void hurt(int, BattleEntity &, int);
bool critStrike(int, int);
bool triggerCheck(int, int, attack, reaction, int, bool);
void itemUse(item, PCharacter[], ECharacter[], bool, int);
void badChild(ECharacter &);

class BattleEntity
{
public:
	string name;
	int HP;
	int EXP = 0;
	int MP;
	int STAM;
	int MORALE;
	int PATK;
	int MATK;
	int PDEF;
	int MDEF;
	int SPD;
	int VAR;
	int CRIT;
	int totalStorage[10]; // 0-HP  1-MP  2-STAM  3-PATK  4-MATK  5-PDEF  6-MDEF  7-SPD  8-VAR  9-CRIT
	int turnTimer = 0;
	int evadeNum;
	int defenseValue = 2;
	int damageDone = 0;
	bool defend = false;
	bool prepared = false;
	bool good;
	BADSTATUS StateB;
	GOODSTATUS StateG;
	reaction activeReac;
	weapon stick;
	RESIST resist[9]{ NORM, NORM, NORM, NORM, NORM, NORM, NORM, NORM, NORM };//SLH, FRC, FIR, ICE, ELC, WND, SON, LIF, NEC
	attack Basic;
	attack moveset[10];
	reaction react[8];
public:
	BattleEntity();
	void respite();
	bool timeTick();
	void strike(BattleEntity &, attack, bool);
	void help(BattleEntity &, attack);
	bool activate(reaction, BattleEntity *, BattleEntity *, attack);
};

class PCharacter:public BattleEntity
{
public:
	int LV;
	int STATstorage[6]; //0-STR 1-HAR 2-INT 3-CON 4-AGI 5-LCK
	int STATprogress[10] = { 0 };
	float STATmultipliers[10];
	int STATcounter = 0;
	//Armor slot
	//Accessory 1 slot
	//Accessory 2 slot
public:
	PCharacter();
	PCharacter(int);
	void display();
	attack displaySkill();
	reaction displayReact();
	item openBag(item[]);
	void reset();
	int targetATK(ECharacter[], TARGET);
	int targetSUP(PCharacter[], TARGET);
	bool takeTurn(PCharacter[], ECharacter[], item[]);

	void LEVELUP();
	void resetStats();
};
void loadStats(PCharacter &);

class ECharacter:public BattleEntity
{
public:
	string graphic[5]; 
	int STATcounter = 0;
	int DANGERamt;
	bool DANGER = false;
	int mode = 0; //Used to swap AI attack modes
	int counter = 0; //Used to keep track of previous turns and actions
	AI Acting;
	atkType Type;
public:
	ECharacter();
	ECharacter(int);
	void display();
	int target(PCharacter[], ECharacter[]);
	attack moveSelect();
	reaction reactSelect(int);
	void takeTurn(PCharacter[], ECharacter[]);
};

class boss
{
public:
	ECharacter Entity;
	ECharacter subEntity[4];
	int targets;
	int subEntPos[5]{-1,-1,-1,-1,-1};
	int triggerPoint[3];
	bool TRIGGER1;
	bool TRIGGER2;
	bool TRIGGER3;
public:
	void setBossInts();
	void triggered(); //Responds to Boss trigger points and activates cutscenes/dialogues/gameplay changes
};


void loadEnemy(int, ECharacter[]);
void loadStats(ECharacter &);
void clearEnemy(ECharacter[]);

class bag
{

	//For storing and using items. There will be an item limit, but not a limit for how many different kinds
};