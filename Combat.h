#pragma once
//All entities and functions required for combat are here.
#include "Structs.h"
#include <string>
using namespace std;

enum BADSTATUS { FINE, DEAD, N_A, TIRED};
enum GOODSTATUS { NONE, PFIRE1, PFIRE2, PFIRE3, PICE1, PELEC1, PWIND1, PLIFE1, PNEC1, REGEN};
enum AI {Q_Q, AGG, SUP, DEF, REAC, SMRT, PSN, BER, PAT, INS, undecided, BOSS1};

class PCharacter;
class ECharacter;
class attack;
void hurt(int, PCharacter &, int);
void hurt(int, ECharacter &, int);
bool critStrike(int, int);
bool triggerCheck(int, int, attack, reaction, int, bool);
void itemUse(item, PCharacter[], ECharacter[], bool, int);

/*class BattleEntity
{
public:
	string name;
	int HP;
	int EXP = 0;
	int MP;
	int STAM
	int MORALE;
	int PATK;
	int MATK;
	int PDEF;
	int MDEF;
	int SPD;
	int VAR;
	int CRIT;
	int totalStorage[10];
	int evadeNum;
	int defenseValue = 2;
	bool defend = false;
	bool prepared = false;
	BADSTATUS StateB;
	GOODSTATUS StateG;
	reaction activeReac;
	float resist[9] {1,1,1,1,1,1,1,-1,1};
	attack Basic;
	attack moveset[11];
	reaction react[9];
public:
	BattleEntity();
	void display();
	void respite();
	void strike(BattleEntity &, attack);
	void help(BattleEntity &, attack);
	bool activate(reaction, BattleEntity *, BattleEntity *, attack);*/
class PCharacter
{
public:
	string name;
	int HP;
	int LV;
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
	int STATstorage[6]; //0-STR 1-HAR 2-INT 3-CON 4-AGI 5-LCK
	int STATprogress[10] = { 0 };
	float STATmultipliers[10];
	int evadeNum;
	int damageDone = 0;
	int defenseValue = 2;
	BADSTATUS StateB;
	GOODSTATUS StateG;
	bool defend = false;
	bool prepared = false;
	reaction activeReac;
	float resist[9]{ 1,1,1,1,1,1,1,-1,1 }; //SLH, FRC, FIR, ICE, ELC, WND, SON, LIF, NEC
	weapon stick;
	//Armor slot
	//Accessory 1 slot
	//Accessory 2 slot
	attack Basic;
	attack moveset[11];
	reaction react[9];
public:
	PCharacter();
	PCharacter(int);
	void display();
	attack displaySkill();
	reaction displayReact();
	item openBag(item[]);
	void respite();
	void reset();
	void strike(ECharacter &, attack);
	void help(PCharacter &, attack);
	int targetATK(ECharacter[], TARGET);
	int targetSUP(PCharacter[], TARGET);
	void takeTurn(PCharacter[], ECharacter[], item[]);
	bool activate(reaction, PCharacter *, ECharacter *, attack);

	void LEVELUP();
};
void loadStats(PCharacter &);

class ECharacter
{
public:
	string name;
	string graphic[5]; 
	int EXP;
	int HP;
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
	int evadeNum;
	bool defend = false;
	int defenseValue = 2;
	bool prepared = false;
	bool DANGER = false;
	int DANGERamt;
	int mode = 0; //Used to swap AI attack modes
	int counter = 0; //Used to keep track of previous turns and actions
	reaction activeReac;
	AI Acting;
	BADSTATUS StateB;
	GOODSTATUS StateG;
	float resist[9]{ 1,1,1,1,1,1,1,-1,1 }; // SLH, FRC, FIR, ICE, ELE, WND, SON, LIF, NEC
	weapon Stick;
	atkType Type;
	attack Basic;
	attack moveset[10];
	reaction react[8];
public:
	ECharacter();
	ECharacter(int);
	void display();
	void respite();
	void strike(PCharacter &, attack);
	void help(ECharacter &, attack);
	int target(PCharacter[], ECharacter[]);
	attack moveSelect();
	reaction reactSelect(int);
	void takeTurn(PCharacter[], ECharacter[]);
	bool activate(reaction, PCharacter *, ECharacter *, attack);
};

class boss
{
public:
	ECharacter Entity;
	ECharacter subEntity[5];
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