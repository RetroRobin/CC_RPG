#include "stdafx.h"
#include "GameState.h"
#include "Combat.h"
#include "Structs.h"
#include "Field.h"
#include <iostream>
#include <string>
using namespace std;

//This document contains the main functions for controlling the flow of the game and setting up combat and exploration

//Sets the slots in the Bag array to correspond with the created item's ID values
void stateController::setBag()
{
	for (int i = 0; i < 10; /*or whatever the bag limit becomes*/ i++)
	{
		this->Bag[i] = item(i);
		this->Bag[i].currAmount = 0;
	}
	//Item allocation for testing
	this->Bag[0].currAmount = 5;
	this->Bag[1].currAmount = 5;
	this->Bag[2].currAmount = 5;
	this->Bag[3].currAmount = 2;
	this->Bag[4].currAmount = 3;
}

//Averages the total speed of combatants for turn order calculations
int stateController::SPDavg() 
{
	int avg = 0;
	int combatants = 0;
	for (int i = 0; i < 4; i++)
	{
		if (this->Pparty[i].StateB != N_A && this->Pparty[i].StateB != DEAD)
		{
			avg = avg + this->Pparty[i].SPD;
			combatants++;
		}	
	}
	for (int i = 0; i < 5; i++)
	{
		if (this->Eparty[i].StateB == N_A || this->Eparty[i].StateB == DEAD)
			break;
		avg = avg + this->Eparty[i].SPD;
		combatants++;
	}

	avg = avg / combatants;
	return avg;
}

//Determines the slowest combatant for turn order calculations
int stateController::SPDlow() 
{
	int lowest = 999;
	for (int i = 0; i < 4; i++)
	{
		if (this->Pparty[i].StateB != N_A && this->Pparty[i].StateB != DEAD)
		{
			if (this->Pparty[i].SPD < lowest)
				lowest = this->Pparty[i].SPD;
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (this->Eparty[i].StateB == N_A || this->Eparty[i].StateB == DEAD)
			break;
		if (this->Eparty[i].SPD < lowest)
			lowest = this->Eparty[i].SPD;
	}
	return lowest;
}

//Determines order of combatants based on speed data
void stateController::SPDorder(int spdAVG, int spdLOW) 
{
	int SPDcomp = 999; //Used to ignore combatants who have already been sorted
	int SPDinsert = 0;
	int tieARR[9];
	int tieCount = 0;
	int change = 0;
	int combatants = 0;

	while (change >= 0)
	{
		change = -1;
		for (int i = 0; i < 4; i++) //Checks highest speed [PARTY] Takes slots [0, 1, 2, 3]
		{
			if (this->Pparty[i].StateB != N_A && this->Pparty[i].StateB != DEAD)
			{
				if (this->Pparty[i].SPD < SPDcomp)
					if (this->Pparty[i].SPD > SPDinsert)
					{
						SPDinsert = this->Pparty[i].SPD;
						change = i;
					}
					else
					{
						if (this->Pparty[i].SPD == SPDinsert) //Tie for highest speed?
						{
							tieARR[tieCount] = i;
							tieCount++;
						}
					}
			}
		}
			
		for (int i = 0; i < 5; i++) //Checks highest speed [ENEMY] Takes slots [4, 5, 6, 7, 8]
		{
			if (this->Eparty[i].StateB != N_A && this->Eparty[i].StateB != DEAD)
			{
				if (this->Eparty[i].SPD < SPDcomp)
					if (this->Eparty[i].SPD > SPDinsert)
					{
						SPDinsert = this->Eparty[i].SPD;
						change = i + 4;
					}
					else
					{
						if (this->Eparty[i].SPD == SPDinsert)
						{
							tieARR[tieCount] = i + 4;
							tieCount++;
						}
					}
			}
		}
		if (change >= 0)
		{
			this->turnOrder[combatants] = change + 1;
			combatants++;
		}
		if (tieCount > 0)
		{
			for (int i = 0; i < tieCount; i++)
			{
				this->turnOrder[combatants] = tieARR[i] + 1;
				combatants++;
			}
		}
		tieCount = 0;
		SPDcomp = SPDinsert;
		SPDinsert = 0;

		
	}
	
}

//Creates graphics for the battle plane based on symbols attached to character objects
void stateController::drawCField() 
{
	int Pcombatants = 0;
	int Ecombatants = 0;
	bool eDead[5] = { false, false, false, false, false };
	bool pDead[4] = { false, false, false, false };
	string enemy1 = "       ", enemy2 = "       ", enemy3 = "       ", enemy4 = "       ", enemy5 = "       ";
	string player1 = "         ", player2 = "         ", player3 = "         ", player4 = "         ", player5 = "         ";
	string boss1 = "        ", boss2 = "        ", boss3 = "        ";
	string prep[5];
	for (int i = 0; i < 4; i++) //What player characters are active?
	{
		if (this->Pparty[i].StateB == N_A)
			break;
		if (this->Pparty[i].StateB == DEAD)
			pDead[i] = true;
		Pcombatants++;
	}

	for (int i = 0; i < 5; i++) //What enemy characters are active?
	{
		if (this->Eparty[i].StateB == N_A)
			break;
		if (this->Eparty[i].StateB == DEAD)
			eDead[i] = true;
		Ecombatants++;
	}

	for (int i = 0; i < Ecombatants; i++) //Graphics for preparing
	{
		prep[i] = " ";
		if (Eparty[i].DANGER == true)
			prep[i] = "\"";
		if (Eparty[i].prepared == true)
			prep[i] = "*";
	}

	if (BOSS.Entity.StateB != N_A) //Boss field code, untested
	{
		if (BOSS.Entity.graphic[3] == "")
		{
			boss1 = "  " + BOSS.Entity.graphic[0];
			boss2 = "1" + prep[0] + BOSS.Entity.graphic[1];
			boss3 = "  " + BOSS.Entity.graphic[2];
		}
		else
		{
			enemy2 = BOSS.Entity.graphic[0];
			boss1 = BOSS.Entity.graphic[1];
			boss2 = BOSS.Entity.graphic[2];
			boss3 = BOSS.Entity.graphic[3];
			enemy4 = BOSS.Entity.graphic[4];
		}
		for (int i = 0; i < 5; i++)
		{
			if (BOSS.subEntity[i].StateB != N_A && eDead[i+1] != true)
			{
				switch (BOSS.subEntPos[i])
				{
				case(0):
					enemy2 = "2 " + BOSS.subEntity[i].graphic[0];
					break;
				case(1):
					boss1 = "2 " + BOSS.subEntity[i].graphic[0];
					break;
				case(2):
					boss2 = "2 " + BOSS.subEntity[i].graphic[0];
					break;
				case(3):
					boss3 = "2 " + BOSS.subEntity[i].graphic[0];
					break;
				case(4):
					enemy4 = "2 " + BOSS.subEntity[i].graphic[0];
					break;
				}
			}
		}
	}
	else 	
	{
		switch (Ecombatants) { //This needs disabling for Bosses
		case 1:
		{
			if (eDead[0] == true)
				enemy3 = "       ";
			else
			{
				enemy3 = "1" + prep[0] + Eparty[0].graphic[Eparty[0].mode];
			}
			break;
		}
		case 2:
		{
			if (eDead[0] == true)
				enemy2 = "       ";
			else
			{
				enemy2 = "1" + prep[0] + Eparty[0].graphic[Eparty[0].mode];
			}
			if (eDead[1] == true)
				enemy4 = "       ";
			else
			{
				enemy3 = "2" + prep[1] + Eparty[1].graphic[Eparty[1].mode];
			}
			break;
		}
		case 3:
		{
			if (eDead[0] == true)
				enemy1 = "       ";
			else
			{
				enemy1 = "1" + prep[0] + Eparty[0].graphic[Eparty[0].mode];
			}
			if (eDead[1] == true)
				enemy3 = "       ";
			else
			{
				enemy3 = "2" + prep[1] + Eparty[1].graphic[Eparty[1].mode];
			}
			if (eDead[2] == true)
				enemy5 = "       ";
			else
			{
				enemy5 = "3" + prep[2] + Eparty[2].graphic[Eparty[2].mode];
			}
			break;
		}
		case 4:
		{
			if (eDead[0] == true)
				enemy1 = "       ";
			else
			{
				enemy1 = "1" + prep[0] + Eparty[0].graphic[Eparty[0].mode];
			}
			if (eDead[1] == true)
				enemy2 = "       ";
			else
			{
				enemy2 = "2" + prep[1] + Eparty[1].graphic[Eparty[1].mode];
			}
			if (eDead[2] == true)
				enemy4 = "       ";
			else
			{
				enemy4 = "3" + prep[2] + Eparty[2].graphic[Eparty[2].mode];
			}
			if (eDead[3] == true)
				enemy5 = "       ";
			else
			{
				enemy5 = "4" + prep[3] + Eparty[3].graphic[Eparty[3].mode];
			}
			break;
		}
		case 5:
		{
			if (eDead[0] == true)
				enemy1 = "       ";
			else
			{
				enemy1 = "1" + prep[0] + Eparty[0].graphic[Eparty[0].mode];
			}
			if (eDead[1] == true)
				enemy2 = "       ";
			else
			{
				enemy2 = "2" + prep[1] + Eparty[1].graphic[Eparty[1].mode];
			}
			if (eDead[2] == true)
				enemy3 = "       ";
			else
			{
				enemy3 = "3" + prep[2] + Eparty[2].graphic[Eparty[2].mode];
			}
			if (eDead[3] == true)
				enemy4 = "       ";
			else
			{
				enemy4 = "4" + prep[3] + Eparty[3].graphic[Eparty[3].mode];
			}
			if (eDead[4] == true)
				enemy5 = "       ";
			else
			{
				enemy5 = "5" + prep[4] + Eparty[4].graphic[Eparty[4].mode];
			}
		}
		}
	}

	switch (Pcombatants) {
	case 1:
	{
		if (pDead[0] == true)
			player3 = "<(x x<) 1";
		else
			player3 = "<(' '<) 1";
		break;
	}
	case 2:
	{
		if (pDead[0] == true)
			player2 = "<(x x<) 1";
		else
			player2 = "<(' '<) 1";
		if (pDead[1] == true)
			player4 = "<(x x<) 2";
		else
			player4 = "<(' '<) 2";
		break;
	}
	case 3:
	{
		if (pDead[0] == true)
			player1 = "<(x x<) 1";
		else
			player1 = "<(' '<) 1";
		if (pDead[1] == true)
			player3 = "<(x x<) 2";
		else
			player3 = "<(' '<) 2";
		if (pDead[2] == true)
			player5 = "<(x x<) 3";
		else
			player5 = "<(' '<) 3";
		break;
	}
	case 4:
	{
		if (pDead[0] == true)
			player1 = "<(x x<) 1";
		else
			player1 = "<(' '<) 1";
		if (pDead[1] == true)
			player2 = "<(x x<) 2";
		else
			player2 = "<(' '<) 2";
		if (pDead[2] == true)
			player4 = "<(x x<) 3";
		else
			player4 = "<(' '<) 3";
		if (pDead[3] == true)
			player5 = "<(x x<) 4";
		else
			player5 = "<(' '<) 4";
		break;
	}
	}

	cout << "________________________________\n                                       COMMANDS\n" <<
		"       " << enemy1 << "         " << player1 <<
		"    1: Attack\n"  << enemy2 << "                             2: Skills\n" <<
		" " << boss1 << "              " << player2 << "    3: Reactions\n" <<
		" " << boss2 << " " << enemy3 << "      " << player3 << "    4: Items\n" <<
		" " << boss3 << "              " << player4 << "    5: SPECIAL(N/A)\n" <<
		" " << enemy4 << "                            6: Defend\n" <<
		"       " << enemy5 << "         " << player5 << "    7: Flee(N/A)\n" <<
		"________________________________\n\n";
	int i = 0;
	while (Pparty[i].StateB != N_A)
	{
		cout << i + 1 <<  ": " << Pparty[i].name << "    HP: " << Pparty[i].HP << "/" << Pparty[i].totalStorage[0] <<
			"   MP: " << Pparty[i].MP << "   ST: " << Pparty[i].STAM << "\n";
		i++;
	}	
}

//Initializes a playable character and puts them into the Party array 
//(may need to tweak to load "saved" player data)
void stateController::loadPlayer(int playerNum)
{
	PCharacter dude(playerNum);
	loadStats(dude);
	Pparty[playerNum] = dude;
}

//Determine who goes next, an enemy or a party member
void nextTurn(stateController &DM, int player) 
{
	player--;
	bool enemy = false;
	if (player > 3)
	{
		player = player - 4;
		enemy = true;
	}
	if (enemy == false)
	{
		if (DM.Pparty[player].StateB == DEAD)
			return;
		DM.Pparty[player].respite();
		DM.drawCField();
		DM.Pparty[player].takeTurn(DM.Pparty, DM.Eparty, DM.Bag);
	}
	else
	{
		//cout << "DEBUG: Enemy #" << player + 1 << " is attacking!\n";
		DM.Eparty[player].takeTurn(DM.Pparty, DM.Eparty);
	}
}

//Determines the effect of stepping on occupied tiles in the field
//False keeps you on the field, True kicks you out to a different mode
bool occCollide(Tile *collisionSite, int direction)
{
	switch (collisionSite->tenant.type)
	{
	default:
	{
		cout << "ERROR!";
		return false;
	}
	case 2: //Horizontal log
	{
		if (direction < 2)
		{
			if (collisionSite->adjacent[direction] != NULL)
			{
				if (collisionSite->adjacent[direction]->tenant.type == 0)
				{
					collisionSite->adjacent[direction]->tenant = collisionSite->tenant;
					collisionSite->tenant = Occupant();
					return false;
				}
			}
		}
		cout << "\nThe log won't move.\n";
		sleep(2);
		break;
	}
	case 3: //Vertical log
	{
		if (direction > 1)
		{
			if (collisionSite->adjacent[direction] != NULL)
			{
				if (collisionSite->adjacent[direction]->tenant.type == 0)
				{
					collisionSite->adjacent[direction]->tenant = collisionSite->tenant;
					collisionSite->tenant = Occupant();
					return false;
				}
			}
		}
		cout << "\nThe log won't move from this side.\n";
		sleep(2);
		break;
	}
	case 4: //enemy
	{
		cout << "\nIt's an attack!\n";
		sleep(2);
		return true;
	}
	case 5: //water
	{
		cout << "You can't swim, so you probably shouldn't go in the water...\n";
		sleep(2);
		return false;
	}
	case 7: //Transition
	{
		cout << "\n\n\nThis tile will eventually take you to another map. \nFor right now, it will take you back to the main menu.\n\n";
		sleep(3);
		cout << "Sending you back to the main menu...\n";
		sleep(2);
		return true;
	}
	}
	return false;
}

//Interacts with a tile's type when the Examine command is used
void exploreAction(Tile examine)
{
	switch (examine.type)
	{
	default:
	{
		break;
	}
	case 1: //Empty Tile
	{
		cout << "\nNothing here.\n";
		sleep(2);
		break;
	}
	case 2: //Vine/switch
	{
		//Need some way of altering blocked tiles or changing tile types here...
		cout << "\nLooks like a switch of some kind. Too bad you can't interact with it yet.\n";
		sleep(3);
		break;
	}
	case 3: //Save point
	{
		//Saving function. Mostly a lot of stuff in the stateController that needs to be saved somehow.
		cout << "\nHere you can SAVE your game. But that may take time to build.\n";
		sleep(3);
		break;
	}
	case 4: //Treasure box
	{
		//Spawn an item based off the EXTRA value of the tile, then add it to the DM.bag
		cout << "\nOoh, it looks like there may be an item there eventually! ...But not now.\n";
		sleep(3);
		break;
	}
	case 5: //water
	{
		cout << "\nI don't know how you're standing on this tile. It should be literally impossible.\n";
		sleep(100);
		break;
	}
	case 6: //Text box
	{
		//Hoo boy, GameText.cpp is about to get bigger...
		cout << "\nThis tile is special. It means there is specific info here that will be of use to you.\n";
		sleep(3);
		break;
	}
	}
}

//Resets turn order and aggregates the speed calculations into one function
void SPDcalc(stateController &DM)
{
	int i = 0;
	while (DM.turnOrder[i] >= 0)
	{
		DM.turnOrder[i] = -1;
		i++;
	}
	int avg = DM.SPDavg();
	//cout << "SPD average = " << avg << "\n";   //DEBUG NOTES
	int lowest = DM.SPDlow();
	//cout << "SPD lowest = " << lowest << "\n";
	DM.SPDorder(avg, lowest);
}

//Master control for Combat. Sets up combatants and controls all Combat functions
//See CombatFuncs.cpp for more info on individual functions
bool combatStart(stateController &DM, int group)
{
	cleanup();
	loadEnemy(group, DM.Eparty);
	int turnCount = 0;

	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	if (DM.Eparty[0].Acting > 10)
	{
		DM.BOSS.Entity = DM.Eparty[0];
		for (int i = 0; i < 4; i++)
			DM.BOSS.subEntity[i] = DM.Eparty[i + 1];
		DM.BOSS.targets = 2; //setTargetAmount function in the future
		DM.BOSS.subEntPos[0] = 1;
		cout << "Boss " << DM.Eparty[0].name << " attacks!\n";
	}
	else 
	{
		for (int i = 0; i < 5; i++)
		{
			if (DM.Eparty[i].StateB != N_A)
			{
				cout << "Enemy " << DM.Eparty[i].name << " appears!   " << DM.Eparty[i].graphic[0] << "\n";
			}
		}
	}
	
	while ((DM.Plife == true) && (DM.Elife == true))
	{
		SPDcalc(DM);
		int i = 0;
		/*while (DM.turnOrder[i] >= 0)
		{
			cout << DM.turnOrder[i] << "\n";
			i++;
		}*/

		int playernum = 0;
		while (DM.turnOrder[playernum] >= 0)
		{
			nextTurn(DM, DM.turnOrder[playernum]);
			playernum++;
			int allDead = 0;
			for (int i = 0; i < 4; i++)
			{
				if (DM.Pparty[i].StateB == DEAD || DM.Pparty[i].StateB == N_A)
					allDead++;
			}
			if (allDead == 4)
			{
				DM.Plife = false;
				break;
			}
			allDead = 0;
			for (int i = 0; i < 5; i++)
			{
				if (DM.Eparty[i].StateB == N_A || DM.Eparty[i].StateB == DEAD)
					allDead++;
			}
			if (allDead == 5)
			{
				DM.Elife = false;
				break;
			}
		}
		turnCount++;
		//Include a STATcounter check here to reset status buffs/debuffs
		//The STATcounter resets every time that a new buff or debuff is cast, which can make an interesting strategy
    }
	if (DM.Elife == false)
	{
		cout << "\nYou win!\n";
		sleep(3);

		int reward = 0;
		for (int i = 0; i < 5; i++)
		{
			if (DM.Eparty[i].StateB != N_A)
			{
				DM.Pparty[i].respite();
				DM.Pparty[i].respite();
				reward = reward + DM.Eparty[i].EXP;
			}
		}
		cout << "The party gets " << reward << " EXP!\n";
		sleep(2);
		for (int i = 0; i < 4; i++)
		{
			if (DM.Pparty[i].StateB != N_A)
			{
				DM.Pparty[i].resetStats();
				DM.Pparty[i].EXP = DM.Pparty[i].EXP + reward;
				if (DM.Pparty[i].EXP >= (DM.Pparty[i].LV * 3) * DM.Pparty[i].LV) //FORMULA WON'T WORK FOR GAME AS WHOLE, ALTER IT [LV^2 * 3?]
					DM.Pparty[i].LEVELUP();
			}
		}

		DM.Elife = true;
		clearEnemy(DM.Eparty);
		return false;
	}
	if (DM.Plife == false)
	{
		cout << "\nYou lose...\n";
		sleep(3);
		return true;
	}
}

//Master control for Field Exploration. Cleans the command window and controls the field state.
//See Field.cpp for more info on individual functions
int exploreStart(stateController &DM, int thisMap, bool resume, int restartHere)
{
	cleanup();
	Tile *locale;
	if (resume == true) //Are we returning from a battle/save?
	{
		locale = loadMap(thisMap, false, restartHere, DM.tempStorage2, DM.tempStorage1);
		locale->tenant = DM.player;
	}
	else
	{
		locale = loadMap(thisMap, false, -1, NULL, NULL);
		for (int i = 0; i < 4; i++)
		{
			int mod;
			if (i % 2 == 0)
				mod = 1;
			else
				mod = -1;
			locale->adjacent[i]->adjacent[i + mod] = locale;
		}
		cutscene(thisMap);
	}


	DM.player = locale->tenant;
	int mapHere = thisMap;
	bool winCondition = false;
	bool battle = false;
	char choice;

	while (winCondition == false) 
	{
		mapDraw(*locale);
		cin >> choice;
		switch (choice)
		{
		default:
		{
			cout << "\nINVALID\n";
			sleep(1);
			break;
		}
		case 101: //ASCII for "e" [Examine]
		{
			exploreAction(*locale);
			break;
		}
		case 49: //ASCII for "1" [North]
		{
			if (locale->adjacent[0] == NULL)
			{
				cout << "\nNowhere to go there...\n";
				sleep(1);
				break;
			}
			if (locale->adjacent[0]->tenant.type == 0)
			{
				locale->tenant = Occupant();
				locale = locale->adjacent[0];
				locale->tenant = DM.player;
				DM.player.location = locale->location;
			}
			else
			{
				if (locale->adjacent[0]->editNum != -1)
				{
					DM.tempStorage1[locale->adjacent[0]->editNum] = locale->adjacent[0]->type;
					DM.tempStorage2[locale->adjacent[0]->editNum] = locale->adjacent[0]->location;
				}
				battle = occCollide(locale->adjacent[0], 0);
				if (locale->adjacent[0]->tenant.type == 0)
				{
					locale->adjacent[0]->adjacent[0]->editNum = locale->adjacent[0]->editNum;
					locale->adjacent[0]->editNum = -1;
					DM.tempStorage2[locale->adjacent[0]->editNum] = locale->adjacent[0]->adjacent[0]->location;
				}
			}
			break;
		}
		case 50: //ASCII for "2" [South]
		{
			if (locale->adjacent[1] == NULL)
			{
				cout << "\nNowhere to go there...\n";
				sleep(1);
				break;
			}
			if (locale->adjacent[1]->tenant.type == 0)
			{
				locale->tenant = Occupant();
				locale = locale->adjacent[1];
				locale->tenant = DM.player;
				DM.player.location = locale->location;
			}
			else
			{
				if (locale->adjacent[1]->editNum != -1)
				{
					DM.tempStorage1[locale->adjacent[1]->editNum] = locale->adjacent[1]->type;
					DM.tempStorage2[locale->adjacent[1]->editNum] = locale->adjacent[1]->location;
				}
				battle = occCollide(locale->adjacent[1], 1);
				if (locale->adjacent[1]->tenant.type == 1)
				{
					locale->adjacent[1]->adjacent[1]->editNum = locale->adjacent[1]->editNum;
					locale->adjacent[1]->editNum = -1;
					DM.tempStorage2[locale->adjacent[1]->editNum] = locale->adjacent[1]->adjacent[1]->location;
				}
			}
			break;
		}
		case 51: //ASCII for "3" [East]
		{
			if (locale->adjacent[3] == NULL)
			{
				cout << "\nNowhere to go there...\n";
				sleep(1);
				break;
			}
			if (locale->adjacent[3]->tenant.type == 0)
			{
				locale->tenant = Occupant();
				locale = locale->adjacent[3];
				locale->tenant = DM.player;
				DM.player.location = locale->location;
			}
			else
			{
				if (locale->adjacent[3]->editNum != -1)
				{
					DM.tempStorage1[locale->adjacent[3]->editNum] = locale->adjacent[3]->type;
					DM.tempStorage2[locale->adjacent[3]->editNum] = locale->adjacent[3]->location;
				}
				battle = occCollide(locale->adjacent[3], 3);
				if (locale->adjacent[3]->tenant.type == 3)
				{
					locale->adjacent[3]->adjacent[3]->editNum = locale->adjacent[3]->editNum;
					locale->adjacent[3]->editNum = -1;
					DM.tempStorage2[locale->adjacent[3]->editNum] = locale->adjacent[3]->adjacent[3]->location;
				}
			}

			break;
		}
		case 52: //ASCII for "4" [West]
		{
			if (locale->adjacent[2] == NULL)
			{
				cout << "\nNowhere to go there...\n";
				sleep(1);
				break;
			}
			if (locale->adjacent[2]->tenant.type == 0)
			{
				locale->tenant = Occupant();
				locale = locale->adjacent[2];
				locale->tenant = DM.player;
				DM.player.location = locale->location;
			}
			else
			{
				if (locale->adjacent[2]->editNum != -1)
				{
					DM.tempStorage1[locale->adjacent[2]->editNum] = locale->adjacent[2]->type;
					DM.tempStorage2[locale->adjacent[2]->editNum] = locale->adjacent[2]->location;
				}
				battle = occCollide(locale->adjacent[2], 2);
				if (locale->adjacent[2]->tenant.type == 0)
				{
					locale->adjacent[2]->adjacent[2]->editNum = locale->adjacent[2]->editNum;
					locale->adjacent[2]->editNum = -1;
					DM.tempStorage2[locale->adjacent[2]->editNum] = locale->adjacent[2]->adjacent[2]->location;
				}
			}
			break;
		}

		}
		if (battle == true)
		{
			int direction = choice - 49;
			if (direction == 2)
				direction++;
			else
			{
				if (direction == 3)
					direction--;
			}
			int group = locale->adjacent[direction]->tenant.extra;
			DM.currTile = locale->location;
			DM.currMap = mapHere;
			DM.tempStorage1[locale->adjacent[direction]->editNum] = locale->adjacent[direction]->tenant.type;
			DM.tempStorage2[locale->adjacent[direction]->editNum] = -1;

			return group;
		}
	}

}

//Main Menu. This is the main function that controls all other functions, and can call in different states.
void GameState() 
{
	stateController DM;

	

	int battleGroup;
	bool check = false;
	bool menuBreak = false;
	int map = 0;
	int tile = -1;
	bool resume = false;

	while (check == false)
	{
		DM.loadPlayer(0);

		DM.setBag();

		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nMAIN MENU\n\n1: Start Game\n2: How to Play\n3: Map Test\n4: Shut down\n";
		int i;
		cin >> i;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
		}
		switch (i)
		{
		default:
			cout << "Please choose an option.\n";
		case 1:
			cout << "Prepare for the combat gauntlet!\n";
			sleep(2);
			cleanup();
			cout << "ROUND 1: YOUR FIRST FIGHT\n";
			sleep(1.5);
			combatStart(DM, 0);
			cout << "A friend has come to help you!\n";
			sleep(1.5);
			cout << "ROUND 2: AGGRESSIVE ATTACKERS\n";
			sleep(1.5);
			DM.loadPlayer(1);
			combatStart(DM, 1);
			cleanup();
			cout << "ROUND 3: SUPPORTIVE FRIEND\n";
			sleep(1.5);
			combatStart(DM, 2);
			cleanup();
			cout << "ROUND 4: WORKING TOGETHER\n";
			sleep(1.5);
			combatStart(DM, 3);
			cout << "The Gauntlet is completed, for now...\n";
			sleep(2);
			cleanup();
			break;
		case 2:
			HTP();
			break;
		case 3:
			//Include a "name your own character" feature before jumping in to anything.
			DM.loadPlayer(1);
			while (menuBreak == false)
			{
				int battleGroup;
				battleGroup = exploreStart(DM, map, resume, tile);
				if (battleGroup == -1)
				{
					for (int i = 0; i < 50; i++)
					{
						DM.tempStorage1[i] = 0;
					}
					break;
				}
				menuBreak = combatStart(DM, battleGroup);
				resume = true;
				map = DM.currMap;
				tile = DM.currTile;
			}
			break;
		case 4:
			check = true;
			break;
		case 5:
			for (int i = 0; i < 20; i++)
			{
				DM.Pparty[0].LEVELUP();
				combatStart(DM, 4);
			}
		}
	}



}


