#include "stdafx.h"
#include "Combat.h"
#include "Structs.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

/* This file contains data on the different characters/enemies and their stats.
   It also includes functions to prepare these entities for battle. */
//This file currently houses AI functions as well.

PCharacter::PCharacter()
{
	name = "NONAME";
	HP = 0;
	PATK = 0;
	PDEF = 0;
	VAR = 0;
	SPD = 0;
	StateB = N_A;
	damageDone = -1;
}

PCharacter::PCharacter(int caseNum)
{
	switch (caseNum)
	{
	default:
		break;
	case 0:
	{
		name = "Eric";
		LV = 1;
		HP = 30;
		MP = 10;
		STAM = 50;
		PATK = 5;
		MATK = 5;
		PDEF = 4;
		MDEF = 4;
		SPD = 5;
		VAR = 3;
		CRIT = 3;
		STATstorage[0] = 5;	STATstorage[1] = 5;	STATstorage[2] = 5;	STATstorage[3] = 5;	STATstorage[4] = 5;	STATstorage[5] = 5;
		STATmultipliers[0] = 5; STATmultipliers[1] = 3.5; STATmultipliers[2] = .75; STATmultipliers[3] = 1.5; STATmultipliers[4] = 1.5;
		STATmultipliers[5] = 1.5; STATmultipliers[6] = 1.5; STATmultipliers[7] = 1; STATmultipliers[8] = 1; STATmultipliers[9] = 1;
		StateB = FINE;
		StateG = NONE;
		Basic = attack(0);
		SetMove(0, moveset, react);
		stick = weapon(0);
		break;
	}
	case 1:
	{
		name = "Chloe";
		LV = 2;
		HP = 30;
		MP = 17;
		STAM = 45;
		PATK = 5;
		MATK = 8;
		PDEF = 6;
		MDEF = 9;
		SPD = 6;
		VAR = 7;
		CRIT = 4;
		STATstorage[0] = 4;	STATstorage[1] = 5;	STATstorage[2] = 7;	STATstorage[3] = 8;	STATstorage[4] = 5;	STATstorage[5] = 6;
		STATmultipliers[0] = 4; STATmultipliers[1] = 4.5; STATmultipliers[2] = .5; STATmultipliers[3] = .75; STATmultipliers[4] = 1.5;
		STATmultipliers[5] = 2.5; STATmultipliers[6] = 4; STATmultipliers[7] = 1; STATmultipliers[8] = 1.5; STATmultipliers[9] = .5;
		StateB = FINE;
		StateG = NONE;
		Basic = attack(0);
		SetMove(1, moveset, react);
		stick = weapon(1);
		break;
	}
	}
}

void PCharacter::reset()
{
	damageDone = 0;

	STAM = totalStorage[2];
	PATK = totalStorage[3];
	MATK = totalStorage[4];
	PDEF = totalStorage[5];
	MDEF = totalStorage[6];
	SPD = totalStorage[7];
	VAR = totalStorage[8];
	CRIT = totalStorage[9];
}


/*     LEVEL UP FUNCTION     */

void PCharacter::LEVELUP()
{
	cleanup();
	this->LV++;
	cout << this->name << " has become stronger, and is now level " << this->LV << "!\n";
	sleep(2);
	int choice;
	int counter = 0;
	cout << "Type the numbers of the four abilities you wish to improve.\n" <<
		"(1) STRENGTH: " << this->STATstorage[0] << 
		"\n(2) TOUGHNESS: " << this->STATstorage[1] << 
		"\n(3) INTELLIGENCE: " << this->STATstorage[2] <<
		"\n(4) CONCENTRATION: " << this->STATstorage[3] <<
		"\n(5) AGILITY: " << this->STATstorage[4] <<
		"\n(6) LUCK: " << this->STATstorage[5] << "\n";

	while (counter < 4)
	{
		cin >> choice;
		if (cin.fail())
		{
			cout << "Please do not type in letters. That is an\n";
			cin.clear();
			cin.ignore(1024, '\n');
		}
		switch (choice)
		{
		default:
		{
			cout << "INVALID SYMBOL, please try again.\n";
			break;
		}
		case 1:
		{
			this->STATstorage[0] = this->STATstorage[0] + 1;
			this->STATprogress[2] = this->STATprogress[2] + 30;
			this->STATprogress[3] = this->STATprogress[3] + 30;
			counter++;
			break;
		}
		case 2:
		{
			this->STATstorage[1] = this->STATstorage[1] + 1;
			this->STATprogress[0] = this->STATprogress[0] + 30;
			this->STATprogress[5] = this->STATprogress[5] + 30;
			counter++;
			break;
		}
		case 3:
		{
			this->STATstorage[2] = this->STATstorage[2] + 1;
			this->STATprogress[1] = this->STATprogress[1] + 30;
			this->STATprogress[4] = this->STATprogress[4] + 30;
			counter++;
			break;
		}
		case 4:
		{
			this->STATstorage[3] = this->STATstorage[3] + 1;
			this->STATprogress[6] = this->STATprogress[6] + 30;
			this->STATprogress[8] = this->STATprogress[8] + 30;
			counter++;
			break;
		}
		case 5:
		{
			this->STATstorage[4] = this->STATstorage[4] + 1;
			this->STATprogress[7] = this->STATprogress[7] + 30;
			this->STATprogress[9] = this->STATprogress[9] + 30;
			counter++;
			break;
		}
		case 6:
		{
			this->STATstorage[5] = this->STATstorage[5] + 1;
			int a = rand() % 10;
			int b = rand() % 10;
			this->STATprogress[a] = this->STATprogress[a] + 50;
			this->STATprogress[b] = this->STATprogress[b] + 50;
			counter++;
			break;
		}
		}
	}
	cin.clear();
	cin.ignore(1024, '\n');
	
	int statOrg[6]{7,7,7,7,7,7 };
	for (int i = 0; i < 6; i++) //Organize all the stats from highest to lowest. Maybe this should be its own function...?
	{
		if (statOrg[4] == 7) //Is nothing in here?
		{
			statOrg[4] = i;
		}
		else
		{
			if (STATstorage[i] >= STATstorage[statOrg[4]]) //Are you bigger than the smallest?
			{
				statOrg[5] = statOrg[4];
				statOrg[4] = i;
				for (int j = 0; j < 4; j++)
				{
					if (STATstorage[statOrg[3 - j]] <= STATstorage[statOrg[4 - j]])
					{
						int k = statOrg[4 - j];
						statOrg[4 - j] = statOrg[3 - j];
						statOrg[3 - j] = k;
					}
				}
			}
			else
			{
				statOrg[5] = i;
			}
		}
		if (statOrg[0] == 7 && statOrg[5] != 7) //Shifts the stats up
		{
			for (int j = 0; j < 5; j++)
				statOrg[j] = statOrg[j + 1];
			statOrg[5] = 7;
		}
	}

	int progStorage[10]{ 0 };
	for (int i = 0; i < 6; i++)
	{
		double fract = STATstorage[statOrg[i]];
		fract /= STATstorage[statOrg[0]];
		int insert = fract * 100; 
		switch (statOrg[i])
		{
		default:
		{
			cout << "EeRRrORrERoROrREeRRrORrERoROrR\n";
			break;
		}
		case 0:
		{
			progStorage[2] = progStorage[2] + insert;
			progStorage[3] = progStorage[3] + insert;
			break;
		}
		case 1:
		{
			progStorage[0] = progStorage[0] + insert;
			progStorage[5] = progStorage[5] + insert;
			break;
		}
		case 2:
		{
			progStorage[1] = progStorage[1] + insert;
			progStorage[4] = progStorage[4] + insert;
			break;
		}
		case 3:
		{
			progStorage[6] = progStorage[6] + insert;
			progStorage[8] = progStorage[8] + insert;
			break;
		}
		case 4:
		{
			progStorage[7] = progStorage[7] + insert;
			progStorage[9] = progStorage[9] + insert;
			break;
		}
		case 5:
		{
			int a = rand() % 10;
			int b = rand() % 10;
			progStorage[a] = progStorage[a] + (insert / 2);
			progStorage[b] = progStorage[b] + (insert / 2);
			break;
		}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		progStorage[i] = progStorage[i] * this->STATmultipliers[i];
		STATprogress[i] = STATprogress[i] + progStorage[i];
		totalStorage[i] = totalStorage[i] + (STATprogress[i] / 100);
		STATprogress[i] = STATprogress[i] % 100;
		cout << totalStorage[i] << "  ";
	}
	cout << "\nHP  MP  ST  PA MA PD MD SP VA CR\nPress any key to continue.\n";
	cin.get();
}



void loadStats(PCharacter &entity)
{
	entity.totalStorage[0] = entity.HP;
	entity.totalStorage[1] = entity.MP;
	entity.totalStorage[2] = entity.STAM;
	entity.totalStorage[3] = entity.PATK;
	entity.totalStorage[4] = entity.MATK;
	entity.totalStorage[5] = entity.PDEF;
	entity.totalStorage[6] = entity.MDEF;
	entity.totalStorage[7] = entity.SPD;
	entity.totalStorage[8] = entity.VAR;
	entity.totalStorage[9] = entity.CRIT;

	entity.Basic.delivery = entity.stick.strike;
}



ECharacter::ECharacter()
{
	name = "NONAME";
	HP = 0;
	PATK = 0;
	MATK = 0;
	PDEF = 0;
	MDEF = 0;
	VAR = 0;
	SPD = 0;
	StateB = N_A;
	graphic[0] = " 0>  ";
	graphic[1] = "      ";
	graphic[2] = "      ";
	graphic[3] = "      ";
	graphic[4] = "      ";
}

ECharacter::ECharacter(int casenum) // Here be all the different types of enemies until I find a more elegant solution
{
	switch (casenum)
	{
	default:
		break;
	case 0:
	{
		name = "Squirrel";
		EXP = 4;
		HP = 25;
		MP = 100;
		STAM = 30;
		PATK = 8;
		MATK = 5;
		PDEF = 2;
		MDEF = 4;
		SPD = 4;
		VAR = 2;
		CRIT = 4;
		StateB = FINE;
		StateG = NONE;
		Basic = attack(0);
		Stick = weapon(2);
		resist[2] = 1.5; resist[8] = .5;
		Acting = AGG;
		DANGERamt = 8;
		graphic[0] = " 0>  "; graphic[1] = " O>  ";
		SetMove(2, this->moveset, this->react);
		break;
	}
	case 1:
	{
		name = "Songbird";
		EXP = 7;
		HP = 15;
		MP = 100;
		STAM = 20;
		PATK = 6;
		MATK = 8;
		PDEF = 0;
		MDEF = 8;
		SPD = 6;
		VAR = 4;
		CRIT = 4;
		StateB = FINE;
		StateG = NONE;
		Basic = attack(0);
		Stick = weapon(2);
		resist[3] = 1.5; resist[4] = 1.5; resist[5] = .5; resist[6] = .5;
		Acting = SUP;
		DANGERamt = 10;
		graphic[0] = " )0  "; graphic[1] = " )0  "; graphic[2] = " )0  ";
		SetMove(3, this->moveset, this->react);
		break;
	}
	case 2:
	{
		name = "Rabbit";
		HP = 30;
		MP = 100;
		STAM = 30;
		PATK = 6;
		MATK = 2;
		PDEF = 16;
		MDEF = 0;
		SPD = 4;
		VAR = 5;
		CRIT = 10;
		StateB = FINE;
		StateG = NONE;
		Basic = attack(0);
		Stick = weapon(3);
		resist[1] = .5; resist[2] = .5; resist[3] = 1.5; resist[6] = 1.5;
		Acting = DEF;
		DANGERamt = 10;
		graphic[0] = " 03  "; graphic[1] = " O3  "; graphic[2] = " }03 ";
		SetMove(4, this->moveset, this->react); //Check this out later, ensure correct moves
		break;
	}
	case 3:
	{
		name = "Owl";
		//WILL DETERMINE LATER
		HP = 20;
		MP = 100;
		STAM = 50;
		PATK = 8;
		MATK = 5;
		PDEF = 2;
		MDEF = 5;
		SPD = 5;
		VAR = 3;
		//END OF DETERMINING LATER
		StateB = FINE;
		StateG = NONE;
		Basic = attack(0);
		Stick = weapon(2);
		resist[3] = 1.5; resist[4] = 1.5; resist[5] = .5; resist[6] = .5;
		Acting = SUP;
		DANGERamt = 10;
		graphic[0] = " )0  "; graphic[1] = " }0  ";
		SetMove(3, this->moveset, this->react);
		break;
	}
	case 4:
	{
		name = "Deer";
		//WILL DETERMINE LATER
		HP = 20;
		MP = 100;
		STAM = 50;
		PATK = 8;
		MATK = 5;
		PDEF = 2;
		MDEF = 5;
		SPD = 5;
		VAR = 3;
		//END OF DETERMINING LATER
		StateB = FINE;
		StateG = NONE;
		Basic = attack(0);
		Stick = weapon(2);
		resist[3] = 1.5; resist[4] = 1.5; resist[5] = .5; resist[6] = .5;
		Acting = SUP;
		DANGERamt = 10;
		graphic[0] = " )0  "; graphic[1] = " }0  ";
		SetMove(3, this->moveset, this->react);
		break;
	}
	case 5:
	{
		name = "Hollow Geist";
		HP = 256;
		MP = 100;
		STAM = 70;
		PATK = 20;
		MATK = 16;
		PDEF = 32;
		MDEF = 20;
		SPD = 10;
		VAR = 12;
		CRIT = 12;
		StateB = FINE;
		StateG = NONE;
		Basic = attack(1);
		Acting = BOSS1;
		DANGERamt = 60;
		graphic[0] = "('$-) ";
		graphic[1] = " | |-E";
		graphic[2] = "/   \ ";
		break;
	}
	case 6:
	{
		name = "Hollow Mask";
		HP = 104;
		MP = 0;
		STAM = 0;
		PATK = 0;
		MATK = 0;
		PDEF = 20;
		MDEF = 10; 
		SPD = 10;
		VAR = 0;
		CRIT = 0;
		StateB = FINE;
		StateG = NONE;
		Basic = attack(1);
		Acting = Q_Q;
		DANGERamt = 0;
		graphic[0] = "('v') ";
		break;
	}
	}
}

void ECharacter::display()
{
	string atktype;
	string weakness = "";
	switch (Acting)
	{
	default:
		atktype = "Aggressive";
		break;
	case 1:
		atktype = "Aggressive";
		break;
	case 2:
		atktype = "Supportive";
		break;
	case 3:
		atktype = "Defensive";
		break;
	case 4:
		atktype = "Reactionary";
		break;
	case 5:
		atktype = "Intelligent";
		break;
	case 6:
		atktype = "Poisonous";
		break;
	case 7:
		atktype = "Berserker";
		break;
	case 8:
		atktype = "Patient";
		break;
	case 9:
		atktype = "Insane";
		break;
	}
	if (resist[0] == 2)
		weakness = weakness + " SLASH";
	if (resist[1] == 2)
		weakness = weakness + " FORCE";
	if (resist[2] == 2)
		weakness = weakness + " FIRE";
	if (resist[3] == 2)
		weakness = weakness + " ICE";
	if (resist[4] == 2)
		weakness = weakness + " ELECTRIC";
	if (resist[5] == 2)
		weakness = weakness + " WIND";
	if (resist[6] == 2)
		weakness = weakness + " SONIC";
	if (resist[7] == 1)
		weakness = weakness + " LIFE";
	if (resist[8] == 2)
		weakness = weakness + " NECROTIC";
	cout << "Name: " << name << "\nTotal health: " << totalStorage[0] <<
		"\nCombat Style: " << atktype << "\nWeaknesses: " << weakness << "\n\n";
}

void loadStats(ECharacter &entity)
{
	entity.totalStorage[0] = entity.HP;
	entity.totalStorage[1] = entity.MP;
	entity.totalStorage[2] = entity.STAM;
	entity.totalStorage[3] = entity.PATK;
	entity.totalStorage[4] = entity.MATK;
	entity.totalStorage[5] = entity.PDEF;
	entity.totalStorage[6] = entity.MDEF;
	entity.totalStorage[7] = entity.SPD;
	entity.totalStorage[8] = entity.VAR;
	entity.totalStorage[9] = entity.CRIT;

	entity.Basic.delivery = entity.Stick.strike;
}

void loadEnemy(int choice, ECharacter eParty[])
{
	//Decide enemy groups
	switch (choice) {
	case 0:
	{
		eParty[0] = ECharacter(0);
		loadStats(eParty[0]);
		break;
	}
	case 1:
	{
		cout << "LOADING SQUIRRELS THREE\n";
		eParty[0] = ECharacter(0);
		loadStats(eParty[0]);
		eParty[0].name = eParty[0].name + " 1";
		eParty[1] = ECharacter(0);
		loadStats(eParty[1]);
		eParty[1].name = eParty[1].name + " 2";
		eParty[2] = ECharacter(0);
		loadStats(eParty[2]);
		eParty[2].name = eParty[2].name + " 3";
		break;
	}
	case 2:
	{
		cout << "LOADING THE BIRD FIEND\n";
		eParty[0] = ECharacter(0);
		loadStats(eParty[0]);
		eParty[0].name = eParty[0].name + " 1";
		eParty[1] = ECharacter(1);
		loadStats(eParty[1]);
		eParty[2] = ECharacter(0);
		loadStats(eParty[2]);
		eParty[2].name = eParty[2].name + " 2";
		break;
	}
	case 3:
	{
		cout << "LOADING THE RABBIT TEST\n";
		eParty[0] = ECharacter(2);
		loadStats(eParty[0]);
		eParty[1] = ECharacter(1);
		loadStats(eParty[1]);
		eParty[2] = ECharacter(0);
		loadStats(eParty[2]);
		break;
	}
	case 4:
	{
		cout << "LOADING DA BAWSS\n";
		eParty[0] = ECharacter(5);
		loadStats(eParty[0]);
		eParty[1] = ECharacter(6);
		loadStats(eParty[1]);
		break;
	}
	case 5:
	{
		cout << "SO MANY RABBITS\n";
		eParty[0] = ECharacter(2);
		loadStats(eParty[0]);
		eParty[1] = ECharacter(2);
		loadStats(eParty[1]);
		eParty[2] = ECharacter(2);
		loadStats(eParty[2]);
		break;
	}
	}

	for (int i = 0; i < 5; i++) //SUPPORT AI enemies need to know who they are quickly.
	{
		if (eParty[i].Acting == SUP)
			eParty[i].counter = i;
	}

}

void clearEnemy(ECharacter eParty[])
{
	for (int i = 0; i < 5; i++)
	{
		eParty[i] = ECharacter();
	}
}