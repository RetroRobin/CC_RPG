#pragma once
// The state of the game is controlled via these functions and classes

#include "Combat.h"
#include "Field.h"
#include <string>
using namespace std;

//This document contains headers for GameState.cpp and GameAnim.cpp

class stateController {
public:
	PCharacter Pparty[4];
	ECharacter Eparty[5];
	BattleEntity ALLPLAYER[10];
	boss BOSS;
	item Bag[20];
	int turnOrder[15]{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,};
	bool Plife = true;
	bool Elife = true;

	Level currLevel;
	Occupant player;
	Tile map[500];
	int currMap = -1;
	int currTile = -1;
	int tempStorage1[50]{ 0 }; //For storing tiles that need to be edited
	int tempStorage2[50]{ 0 }; //For storing the edits to perform on the tiles
public:
	void setBag();
	void drawCField();
	void loadPlayer(int);
	void loadBattleArray();
};

void GameState();
bool combatStart(stateController &, int);
int exploreStart(stateController &, int, bool, int);
void SPDcalc(stateController &);
void nextTurn(stateController &, int);
bool occCollide(Tile *, int, Level &, bool &); 
bool exploreAction(Tile, stateController &); //Unimplemented, for determining what happens when choosing to interact

//For the animation file
void startupAnim();
void screenAdjust();

void HTP();
void cutscene(int);

void cutscenePlay(string);

/*MC stats
HP: 30
PATK: 5
PDEF: 4
MP:
MATK:
MDEF:
SPD:
VAR:


0>		Squirrel

)0		Bird

03		Rabbit

]0}		Owl

<00{	Deer

('v')	(-$-)
 | |->  Hollow Geist
/   \

 /\8  
|  {, 
 )0 {,	Shub-Niggurath
/===0\
|=0==|		|=Q==|

*/

