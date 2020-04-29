#include "stdafx.h"
#include "Combat.h"
#include "Structs.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

//This file includes all the code for the enemy AI

int ECharacter::target(PCharacter party[], ECharacter eParty[])
{
	switch (this->Acting - 1)
	{
	default:
	{
		return -1;
	}
	case 0: //AGGRESSIVE
	{
		/*NOTES ON TARGETING
		Will target heroes only. Determines target by using DamageDone int from Player. Whoever is the most *dangerous* is prioritized.
		In danger, will try to kill lowest health party member*/
		int MAX = -1;
		int most = -1;
		int index = 0;
		bool over = false;
		int limit;
		for (int i = 0; i < 4; i++)
		{
			if (party[i].StateB != DEAD && party[i].StateB != N_A)
				index++;
		}
		switch (index)
		{
		case 1:
			limit = 0;
			break;
		case 2:
			limit = 3;
			break;
		case 3:
			limit = 7;
			break;
		case 4:
			limit = 11;
			break;
		}
		index = 0;
		int LOTTERY[12]{ -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1 };  //Alter for different party member totals
		if (this->DANGER == true)
		{
			MAX = 999;
			for (int i = 0; i < 4; i++)
			{
				if (party[i].StateB == N_A || party[i].StateB == DEAD)
					break;
				if (party[i].HP < MAX)
				{
					index = i;
					MAX = party[i].HP;
				}
			}
			return index;
		}
		for (int i = 0; i < 4; i++)
		{
			if (party[i].StateB == DEAD)
				i++;
			if (party[i].StateB == N_A)
				break;
			if (MAX == party[i].damageDone)
			{
				LOTTERY[index] = i;
				index++;
				if (index > limit)
				{
					index = 0;
					over = true;
				}
			}
			if (MAX < party[i].damageDone)
			{
				MAX = party[i].damageDone;
				most = i;
				LOTTERY[index] = i;
				index++;
				if (index > limit)
				{
					index = 0;
					over = true;
				}
			}
			LOTTERY[index] = most;
			index++;
			if (index > limit)
			{
				index = 0;
				over = true;
			}
			if (party[i].StateB != DEAD)
			{
				LOTTERY[index] = i;
				index++;
				if (index > limit)
				{
					index = 0;
					over = true;
				}
			}
		}
		if (over == true)
			return LOTTERY[rand() % (limit + 1)];
		else
			return LOTTERY[rand() % index];
	}
	case 1: //SUPPORTIVE
	{
		/*NOTES ON TARGETING
		Keeps track of 'last helped' by saving their array number into the COUNTER. If any of their targets stats are
		higher than the default, they are considered 'helped'. If their target is in DANGER mode, will immediately swap to Mode 2 and heal them.
		Otherwise, will use buff moves on the party in Mode 0.
		NOT ADDED YET: If a friend has the DEAD status, and there is an ability in slot 10, use that ability.
		If everyone aside from self has been 'helped', then swap to mode 1 and pick the enemy with the lowest health.*/
		this->mode = 0;
		if (this->DANGER == true)
		{
			this->mode = 2;
			return this->counter;
		}
		int randos[5]{ -1, -1, -1, -1, -1 };
		bool copy = true;
		while (copy == true) //Randomly allocates a checking order
		{
			int lotto = (rand() % 5);
			for (int j = 0; j < 5; j++)
			{
				if (randos[j] == lotto)
					break;
				if (randos[j] == -1)
				{
					randos[j] = lotto;
					break;
				}
			}
			if (randos[4] != -1)
				copy = false;
		}

		for (int i = 0; i < 5; i++) //Tests each teammate in checking order for LOW HEALTH then STAT CHANGES
		{
			copy = false;
			if (eParty[randos[i]].StateB != N_A)
			{
				if (randos[i] != this->counter)
				{
					if (eParty[randos[i]].StateB == DEAD) //Is my friend dead?
					{
						if (this->moveset[9].accuracy != -1) //Do I have a resurrection ability?
						{
							this->mode = 3;
							return randos[i];
						}
						else
						{
							copy = true;
						}
					}
					if (eParty[randos[i]].DANGER == true) //Is my friend low on health?
					{
						this->mode = 2;
						return randos[i];
					}
					//Tests stats. Will make FOR loop if I restructure the core stats for both Player and Enemy.
					if (eParty[randos[i]].PATK > eParty[randos[i]].totalStorage[3])
					{
						copy = true;
					}
					if (eParty[randos[i]].MATK > eParty[randos[i]].totalStorage[4])
					{
						copy = true;
					}
					if (eParty[randos[i]].PDEF > eParty[randos[i]].totalStorage[5])
					{
						copy = true;
					}
					if (eParty[randos[i]].MDEF > eParty[randos[i]].totalStorage[6])
					{
						copy = true;
					}
					if (eParty[randos[i]].SPD > eParty[randos[i]].totalStorage[7])
					{
						copy = true;
					}

					if (copy == false)
						return randos[i];
				}
			}
		}

		this->mode = 1;
		int index;
		int MAX = 999;
		for (int i = 0; i < 4; i++)
		{
			if (party[i].StateB == DEAD || party[i].StateB == N_A)
				break;
			if (party[i].HP < MAX)
			{
				index = i;
				MAX = party[i].HP;
			}
		}
		return index;
	}
	case 2: //DEFENSIVE
	{
		/*NOTES ON TARGETING
		Flips between "Attack" and "Defend" mode. Depending on the mode, it will either target one of its own allies...
		Or a random enemy that is not defending or preparing.
		Priority for targeting friends: Self danger > In danger > Supportive > lowest health
		If your friends are dead, trigger mode 2 and target the enemy with the highest damage done.
		  MODE 0: Defend an ally
		  MODE 1: Attack an enemy
		  MODE 2: Berserk
		  MODE 3: Danger Mode. Because. */

		int counting = 0;
		for (int i = 0; i < 5; i++) //See how many teammates are alive
		{
			if (eParty[i].StateB != N_A)
			{
				if (eParty[i].StateB != DEAD)
					counting++;
			}
		}
		if (counting == 1) //If it's just you, time to go to mode 2! Berserk mode!
		{
			cout << this->name << " is mad!\n";
			sleep(1);
			mode = 2;
			int DD = 0;
			for (int i = 0; i < 4; i++)
			{
				if (DD < party[i].damageDone)
				{
					DD = party[i].damageDone;
					counting = i;
				}
			}
			return counting;
		}

		if (mode == 1) //Reset if at "attack" mode
		{
			counter = 0;
			mode = 0;
		}
		else //Check to see if we go to "attack" mode!
		{
			counter++;
			if (DANGER != true) 
			{
				if (mode == 3) //Reset if in Danger mode
					mode = 0;
				int test = rand() % 10; //May tweak it to adjust frequency of attacking
				if (counter + test > 6)
					mode = 1;
			}
		}

		if (DANGER == true) //Target self if in danger
		{
			mode = 3;
			for (int i = 0; i < 5; i++)
			{
				if (eParty[i].name == this->name)
				{
					return i;
				}
			}
		}
		//IF MODE 0: Check the priority. Targets in danger? Supportive enemies around? Who has lowest health?
		if (mode == 0)
		{
			for (int i = 0; i < 5; i++)
			{
				if (eParty[i].StateB != N_A || eParty[i].StateB != DEAD)
				{
					if (eParty[i].DANGER == true)
						return i;
				}
			}
			for (int i = 0; i < 5; i++)
			{
				if (eParty[i].StateB != N_A || eParty[i].StateB != DEAD)
				{
					if (eParty[i].Acting == SUP)
						return i;
				}
			}
			int backUp = 99999;
			int CHOOSE;
			for (int i = 0; i < 5; i++)
			{
				if (eParty[i].StateB != N_A || eParty[i].StateB != DEAD)
				{
					if (eParty[i].HP < backUp)
					{
						CHOOSE = i;
						backUp = eParty[i].HP;
					}
				}
			}
			return CHOOSE;
		}
		//IF MODE 1: Target priority on the person with the highest defence. These enemies hit with hard single attacks.
		if (mode == 1)
		{
			int backUp = 0;
			int CHOOSE;
			for (int i = 0; i < 4; i++)
			{
				if (party[i].PDEF + party[i].MDEF > backUp)
				{
					CHOOSE = i;
					backUp = party[i].PDEF + party[i].MDEF;
				}
			}
			return CHOOSE;
		}
	}
	case 3: //REACTIVE
	{

	}
	case 4: //INTELLIGENT
	{

	}
	case 5: //POISONOUS
	{

	}
	case 6: //BERSERK
	{

	}
	case 7: //PATIENT
	{

	}
	case 8: //INSANE
	{

	}
	case 9: //???
	{

	}
	}
	return 0;
}

attack ECharacter::moveSelect()
{
	attack choice;
	switch (this->Acting - 1)
	{
	default:
	{
		return choice;
	}
	case 0: //AGGRESSIVE
	{
		/*NOTES ON ATTACKS
		MODE 0: Weaker basic attacks, perhaps more multihits in harder AGGRESSIVE enemies
		MODE 1: Uses their most dangerous attacks
		MODE SWITCH: Chance increases as turns go on
		*/
		while (choice.accuracy == -1)
		{
			int roulette = rand() % 11;
			roulette--;
			if (this->mode == 0)
			{
				if (roulette == -1)
				{
					choice = this->Basic;
					this->counter++;
					if ((rand() % 6) < this->counter)
					{
						this->mode = 1;
						this->counter = 0;
					}
					return choice;
				}
				else
				{
					if ((roulette % 2) == 0)
						roulette++;
				}
			}
			else
			{
				if ((roulette % 2) != 0)
					roulette--;
				if (roulette < 0)
					roulette = 0;
			}
			choice = this->moveset[roulette];
		}
		if (this->mode == 0)
		{
			this->counter++;
			if ((rand() % 6) < this->counter) //Should be mod 6
			{
				this->mode = 1;
				this->counter = 0;
			}
		}
		else
			this->mode = 0;

		break;
	}
	case 1: //SUPPORTIVE
	{
		/*NOTES ON ATTACKS
		If in Mode 0, picks moves 2 - 8
		If in Mode 1, picks move 1 or Basic
		If in Mode 2, picks moves 3 - 9
		If in Mode 3 and move 10 is an option, picks move 10*/
		while (choice.accuracy == -1)
		{
			int selection = rand() % 4;
			switch (this->mode)
			{
			default:
			{
				cout << "ERROR\n";
				return this->Basic;
			}

			case 0:
			{
				selection = (selection * 2) + 1;
				break;
			}
			case 1:
			{
				selection = selection % 2;
				if (selection == 1)
					return this->Basic;
				break;
			}
			case 2:
			{
				selection = (selection * 2) + 2;
				break;
			}
			case 3:
			{
				selection = 9;
				break;
			}
			}
			choice = this->moveset[selection];
		}
		break;
	}
	case 2: //DEFENSIVE
	{
		// 0: DEFEND TARGET   1: ATTACK TARGET   2: BERSERK TARGET   3: IN DANGER! DEFEND!
		while (choice.accuracy == -1)
		{
			
			int selection = rand() % 24;
			switch (this->mode)
			{
				default:
				{
					cout << "ERROR\n";
					return this->Basic;
				}
				case 0: //Defend! [SLOTS 0 - 3] (weighted with 0 and 1 being more likely)
				{
					selection = selection / 4;
					selection = selection % 4;
					break;
				}
				case 1: //Attack!
				{
					selection = selection / 3;
					selection = selection - 1; 
					if (selection < 0)
						selection = 0;
					selection = selection % 4;
					selection = selection + 3; //That should get us either 3, 4, 5, or 6
					if (selection == 3) //Weighted toward 3, so as to get us a basic attack easily enough
					{
						choice = this->Basic;
						return choice;
					}
					break;
				}
				case 2: //Everyone's dead! BURN DOWN THEIR HOUSES!!!
				{
					selection = selection % 4;
					selection = selection % 3;
					selection = selection + 7;
					break;
				}
				case 3: //I'm hurt! FALL BACK!!!
				{
					selection = 2; //2 will always be DEFEND for defensives, or an appropriate reaction, or perhaps a healing spell. Self-targeted. Or a flee.
					break;
				}
			}
			choice = this->moveset[selection];
		}
	}
	case 3: //REACTIVE
	{

	}
	case 4: //INTELLIGENT
	{

	}
	case 5: //POISONOUS
	{

	}
	case 6: //BERSERK
	{

	}
	case 7: //PATIENT
	{

	}
	case 8: //INSANE
	{

	}
	case 9: //???
	{

	}
	}
	return choice;
}

reaction ECharacter::reactSelect(int target)
{
	reaction choice;
	switch (this->Acting - 1)
	{
	default:
	{
		return choice;
	}
	case 0: //AGGRESSIVE
	{
		//Aggressive enemies will only have the one reaction to use.
		choice = this->react[0];
		break;
	}
	case 1: //SUPPORTIVE
	{
		//(WTF do I do...? Same thing as AGGRESSIVE?)
	}
	case 2: //DEFENSIVE
	{
		//If target is all, use all target one. Else, 1 in 5 chance to use the special one versus the normal one.
		if (target == 9)
			choice = this->react[2];
		int dorp = rand() % 5;
		/*if (dorp == 4)				COMMENTED OUT FOR TESTING
			choice = this->react[1];
		else*/
		choice = this->react[0];
		break;

	}
	case 3: //REACTIVE
	{

	}
	case 4: //INTELLIGENT
	{

	}
	case 5: //POISONOUS
	{

	}
	case 6: //BERSERK
	{

	}
	case 7: //PATIENT
	{

	}
	case 8: //INSANE
	{

	}
	case 9: //???
	{

	}
	}
	if (choice.victim == FRIEND || choice.victim == SELF)
	{
		target = target + 4;
	}
	choice.TarNum = target;
	cout << target << "\n";
	return choice;
}