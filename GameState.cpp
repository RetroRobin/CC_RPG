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

void stateController::loadBattleArray()
{
	int counter = 0;
	for (int i = 0; i < 4; i++)
	{
		Pparty[i].turnTimer = 0;
		ALLPLAYER[counter] = Pparty[i];
		counter++;
	}
	for (int i = 0; i < 5; i++) //May alter depending on enemy count
	{
		Eparty[i].turnTimer = 0;
		ALLPLAYER[counter] = Eparty[i];
		counter++;
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
//Determine if we still need this function
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
		//While loop here, so that the field gets redrawn
		bool loop = false;
		while (loop == false)
		{
			DM.drawCField();
			loop = DM.Pparty[player].takeTurn(DM.Pparty, DM.Eparty, DM.Bag);
		}
	}
	else
	{
		//cout << "DEBUG: Enemy #" << player + 1 << " is attacking!\n";
		DM.Eparty[player].takeTurn(DM.Pparty, DM.Eparty);
	}
}

//Determines the effect of stepping on occupied tiles in the field
//False keeps you on the field, True kicks you out to a different mode
bool occCollide(Tile *collisionSite, int direction, Level &currLevel, bool &transition)
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
					currLevel.currRoom.editCode[collisionSite->adjacent[direction]->location + 1] = 55;
					collisionSite->tenant = Occupant();
					currLevel.currRoom.editCode[collisionSite->location + 1] = 49;
					return false;
				}
			}
		}
		cout << "\nThe log won't move from this side.\n";
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
					currLevel.currRoom.editCode[collisionSite->adjacent[direction]->location + 1] = 56;
					collisionSite->tenant = Occupant();
					currLevel.currRoom.editCode[collisionSite->location + 1] = 49;
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
		currLevel.currRoom.editCode[collisionSite->location + 1] = 49;
		currLevel.currRoom.editCode[collisionSite->location + 2] = 0;
		return true;
	}
	case 5: //water
	{
		cout << "\nA body of water blocks your path, flowing swiftly. You see no way of crossing it...\n";
		sleep(3);
		return false;
	}
	case 7: //Transition
	{
		//Oh boy, BIG fixes here
		cleanup();
		//ASCII image here?
		string tranText = currLevel.roomChange + "\nWould you like to keep going?\n\n";
		cutscenePlay(tranText);
		cout << "1 - YES\n2 - NO\n";
		int choice;
		cin >> choice;
		if (choice != 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			break;
		}
		cleanup();
		cout << " N O W   L O A D I N G . . .";
		sleep(3);

		transition = true;
		break;
	}
	//Case for cutscene triggers
	}
	return false;
}

//Interacts with a tile's type when the Examine command is used
bool exploreAction(Tile examine, stateController &DM)
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
		//This will require a base edit of the room to remove the switch and leave its effects.
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
		string tranText = DM.currLevel.boxOpen + "\n\n";
		cutscenePlay(tranText);
		cout << "1 - YES\n2 - NO\n";
		int choice;
		cin >> choice;
		if (choice != 1)
		{
			cin.clear();
			cin.ignore(1024, '\n');
			return false;
		}

		bool canPick = false;
		int identifier = 0;
		for (int i = 0; i < 20; i++)
		{
			if(DM.Bag[i].ID == examine.extra)
			{
				DM.Bag[i].currAmount++;
				if(DM.Bag[i].currAmount > DM.Bag[i].maxAmount)
				{
					DM.Bag[i].currAmount--;
					break;
				}
				canPick = true;
				break;
			}
			if(DM.Bag[i].effect == -1)
			{
				DM.Bag[i] = item(i);
				DM.Bag[i].currAmount = 1;
				canPick = true;
				break;
			}
			identifier++;
		}
		tranText = "You got a " + DM.Bag[identifier].name + "!";
		cutscenePlay(tranText);
		sleep(1);
		if (canPick == true)
		{
			//Detonate the box
			DM.currLevel.tweasure[DM.currLevel.currRoom.treasures[examine.editNum]] = false;
			DM.currLevel.currRoom.editCode[examine.location + 1] = 49;
			DM.currLevel.currRoom.editCode[examine.location + 2] = 0;
			DM.currLevel.currRoom.editCode[examine.location + 3] = 0;
			return true;
		}
		else
		{
			tranText = "...But you can't carry it with you...\n";
			cutscenePlay(tranText);
			sleep(1);
		}
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
	return false;
}

//Resets turn order and aggregates the speed calculations into one function
void SPDcalc(stateController &DM)
{
	for (int i = 0; i < 15; i++)
	{
		DM.turnOrder[i] = -1;
	}

	int i = 0;
	while (i < 7)
	{
		for (int j = 0; j < 10; j++)
		{
			if (DM.ALLPLAYER[j].StateB != N_A)
			{
				if (DM.ALLPLAYER[j].timeTick() == true)
				{
					DM.turnOrder[i] = j + 1;
					i++;
				}
			}
		}
	}
}

//Master control for Combat. Sets up combatants and controls all Combat functions
//See CombatFuncs.cpp for more info on individual functions
bool combatStart(stateController &DM, int group)
{
	cleanup();
	loadEnemy(group, DM.Eparty);
	int turnCount = 0;
	DM.loadBattleArray();

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

		//DEBUG
		/*int i = 0;
		while (DM.turnOrder[i] >= 0)
		{
			cout << DM.turnOrder[i] << "\n";
			i++;
		}*/
		//DEBUG

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
		locale = loadMap(DM.currLevel.roomNums[thisMap], false, restartHere, DM.currLevel);
		locale->tenant = DM.player;
	}
	else
	{
		locale = loadMap(DM.currLevel.roomNums[thisMap], false, -1, DM.currLevel);
		for (int i = 0; i < 4; i++)
		{
			int mod;
			if (i % 2 == 0)
				mod = 1;
			else
				mod = -1;
			if (locale->adjacent[i] != NULL)
			{
				locale->adjacent[i]->adjacent[i + mod] = locale;
			}
		}
		cutscene(thisMap);
		//Wipe old player start from the editcode using locale.location
	}


	DM.player = locale->tenant;
	int mapHere = thisMap;
	bool winCondition = false;
	bool battle = false;
	bool transition = false;
	char choice;

	while (winCondition == false) 
	{
		mapDraw(*locale, DM.currLevel.name);
		cin >> choice;
		switch (choice)
		{
		default:
		{
			cout << "\nINVALID\n";
			sleep(1);
			cin.ignore(1024, '\n');
			break;
		}
		case 114: //ASCII for "r" [restart]
		{
			DM.currTile = locale->location;
			DM.currMap = mapHere;
			return 999; //return -1;
		}
		case 101: //ASCII for "e" [Examine]
		{
			//Something's wrong here. The current level is getting corrupted.
			bool reset = exploreAction(*locale, DM);
			if (reset == true)
			{
				DM.currTile = locale->location;
				DM.currMap = mapHere;
				return 999;
			}
			break;
		}
		case 49: //ASCII for "1" [North]
		{
			if (locale->adjacent[0] == NULL)
			{
				cout << "\nNowhere to go there...\n";
				sleep(1);
				cin.ignore(1024, '\n');
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
				cin.ignore(1024, '\n');
				battle = occCollide(locale->adjacent[0], 0, DM.currLevel, transition); 
			}
			break;
		}
		case 50: //ASCII for "2" [South]
		{
			if (locale->adjacent[1] == NULL)
			{
				cout << "\nNowhere to go there...\n";
				sleep(1);
				cin.ignore(1024, '\n');
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
				cin.ignore(1024, '\n');
				battle = occCollide(locale->adjacent[1], 1, DM.currLevel, transition);
			}
			break;
		}
		case 51: //ASCII for "3" [East]
		{
			if (locale->adjacent[3] == NULL)
			{
				cout << "\nNowhere to go there...\n";
				sleep(1);
				cin.ignore(1024, '\n');
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
				cin.ignore(1024, '\n');
				battle = occCollide(locale->adjacent[3], 3, DM.currLevel, transition);
			}

			break;
		}
		case 52: //ASCII for "4" [West]
		{
			if (locale->adjacent[2] == NULL)
			{
				cout << "\nNowhere to go there...\n";
				sleep(1);
				cin.ignore(1024, '\n');
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
				cin.ignore(1024, '\n');
				battle = occCollide(locale->adjacent[2], 2, DM.currLevel, transition);
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
			/*DM.tempStorage1[locale->adjacent[direction]->editNum] = locale->adjacent[direction]->tenant.type;
			DM.tempStorage2[locale->adjacent[direction]->editNum] = -1;*/

			return group;
		}
		if (transition == true)
		{
			int direction = choice - 49;
			if (direction == 2)
				direction++;
			else
			{
				if (direction == 3)
					direction--;
			}
			int newMap = locale->adjacent[direction]->tenant.extra;
			int newTile = locale->adjacent[direction]->editNum; 

			mapHere = DM.currLevel.roomNums[newMap];
			DM.currLevel.currRoom = Room(mapHere);
			newTile = DM.currLevel.currRoom.entrances[newTile];

			
			switch (direction)
			{
			case(0):
				newTile = newTile - DM.currLevel.currRoom.width;
				break;
			case(1):
				newTile = newTile + DM.currLevel.currRoom.width;
				break;
			case(2):
				newTile++;
				break;
			case(3):
				newTile--;
				break;
			}

			locale = loadMap(mapHere, false, newTile, DM.currLevel);
			for (int i = 0; i < 4; i++)
			{
				int mod;
				if (i % 2 == 0)
					mod = 1;
				else
					mod = -1; 
				if (locale->adjacent[i] != NULL)
				{
					locale->adjacent[i]->adjacent[i + mod] = locale;
				}
			}
			DM.currTile = locale->location;
			transition = false;
			locale->tenant.type = 1;
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
	int tile = false;
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
			if (DM.Plife == false)
			{
				DM.Plife = true;
				break;
			}
			cout << "A friend has come to help you!\n";
			sleep(1.5);
			cout << "ROUND 2: AGGRESSIVE ATTACKERS\n";
			sleep(1.5);
			DM.loadPlayer(1);
			combatStart(DM, 1);
			if (DM.Plife == false)
			{
				DM.Plife = true;
				break;
			}
			cleanup();
			cout << "ROUND 3: SUPPORTIVE FRIEND\n";
			sleep(1.5);
			combatStart(DM, 2);
			if (DM.Plife == false)
			{
				DM.Plife = true;
				break;
			}
			cleanup();
			cout << "ROUND 4: WORKING TOGETHER\n";
			sleep(1.5);
			combatStart(DM, 3);
			if (DM.Plife == false)
			{
				DM.Plife = true;
				break;
			}
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
			DM.currLevel = Level(-1);
			while (menuBreak == false)
			{
				int battleGroup = -1;
				battleGroup = exploreStart(DM, map, resume, tile);
				if (battleGroup == -1)
				{
					for (int i = 0; i < 50; i++)
					{
						DM.tempStorage1[i] = 0;
					}
					menuBreak = true;
					break;
				}
				else
				{
					if (battleGroup != 999)
					{
						menuBreak = combatStart(DM, battleGroup);
					}
				}
				resume = true;
				map = DM.currMap;
				tile = DM.currTile;
			}
			break;
		case 4:
			check = true;
			break;
		case 5: //DEBUG OPTIONS
			cout << "Speed: " << DM.Pparty[0].SPD << "\n";
			sleep(2);
			for (int i = 0; i < 20; i++)
			{
				DM.Pparty[0].LEVELUP();
			}
		case 6: //MORE DEBUG
			string testOut = "This is a test string! We are testing specific commands... And making sure\nthat everything works? Let's see if it does.";
			cutscenePlay(testOut);
			sleep(10);
		}
	}



}


