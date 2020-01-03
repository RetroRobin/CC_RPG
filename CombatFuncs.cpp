#include "stdafx.h"
#include "Combat.h"
#include "Structs.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

/* This file contains all the functions the combat engine uses to run. */

void sleep(float sec)
{
	clock_t wait;
	wait = clock();
	while (clock() != wait + (sec * 1000));
}

//Damages (heals?) a player character
void hurt(int dmg, PCharacter &hero, int stat) //Alter to allow changes in STAM and MP
{
	if (stat == 0) //Affecting HP
	{
		hero.HP = hero.HP - dmg;
		if (hero.HP > hero.totalStorage[0])
		{
			hero.HP = hero.totalStorage[0];
			cout << hero.name << " is fully healed!!!\n";
			sleep(1);
		}
		if (hero.HP <= 0)
		{
			cout << hero.name << " is down!\n";
			sleep(1);
			hero.StateB = DEAD;
			hero.HP = 0;
			hero.damageDone = 0;
		}
	}
	if (stat == 1) //Affecting MP
	{
		hero.MP = hero.MP - dmg;
		if (hero.MP > hero.totalStorage[1])
		{
			hero.MP = hero.totalStorage[1];
			cout << hero.name << " is fully powered!!!\n";
			sleep(1);
		}
		if (hero.MP <= 0)
		{
			hero.MP = 0;
		}
	}
	if (stat == 2) //Affecting STAM
	{
		hero.STAM = hero.STAM - dmg;
		if (hero.STAM > hero.totalStorage[2])
		{
			hero.STAM = hero.totalStorage[2];
			cout << hero.name << " is fully energized!!!\n";
			sleep(1);
		}
		if (hero.STAM <= 0)
		{
			hero.StateB = TIRED;
			hero.PDEF = hero.PDEF - (hero.totalStorage[5] / 2);
			hero.MDEF = hero.MDEF - (hero.totalStorage[6] / 2);
			cout << hero.name << " is exhausted!\n";
			sleep(1);
		}
	}
	if (stat == 3) //REVIVAL!
	{
		dmg = dmg * -1;
		if (hero.StateB == DEAD)
		{
			hero.StateB = FINE;
			int revAmount = (hero.totalStorage[0] / (100 / dmg));
			hero.HP = revAmount;
		}
	}
}

//Damages (heals?) an enemy character
//Perhaps I can alter these so that PCharacter and ECharacter are children of a parent object...
void hurt(int dmg, ECharacter &enemy, int stat) //Alter to allow changes in STAM and MP
{
	if (stat == 0) //Affecting HP
	{
		enemy.HP = enemy.HP - dmg;
		if (enemy.HP > enemy.totalStorage[0])
		{
			enemy.HP = enemy.totalStorage[0];
			enemy.DANGER = false;
			cout << enemy.name << " is fully healed!!!\n";
			sleep(1);
		}
		if (enemy.HP <= enemy.DANGERamt)
			enemy.DANGER = true;
		else
			enemy.DANGER = false;
		if (enemy.HP <= 0)
		{
			cout << enemy.name << " has been defeated!\n";
			sleep(1);
			enemy.DANGER = false;
			enemy.StateB = DEAD;
			enemy.HP = 0;
		}
	}
	if (stat == 1) //Affecting MP
	{
		enemy.MP = enemy.MP - dmg;
		if (enemy.MP > enemy.totalStorage[1])
		{
			enemy.MP = enemy.totalStorage[1];
			cout << enemy.name << " is fully powered!!!\n";
			sleep(1);
		}
		if (enemy.MP <= 0)
		{
			cout << "AN ERROR HAS OCCURED\n";
			enemy.MP = 0;
		}
	}
	if (stat == 2) //Affecting STAM
	{
		enemy.STAM = enemy.STAM - dmg;
		if (enemy.STAM > enemy.totalStorage[2])
		{
			enemy.STAM = enemy.totalStorage[2];
			cout << enemy.name << " is fully energized!!!\n";
			sleep(1);
		}
		if (enemy.STAM <= 0)
		{
			enemy.StateB = TIRED;
			enemy.PDEF = enemy.PDEF - (enemy.totalStorage[5] / 2);
			enemy.MDEF = enemy.MDEF - (enemy.totalStorage[6] / 2);
			cout << enemy.name << " is exhausted!\n";
			sleep(1);
		}
	}
}

//Determines if we have a critical hit
bool critStrike(int CRIT, int MDEF)
{
	int CritRate = MDEF - CRIT;
	if (CritRate < 0)
		CritRate = 0;
	CritRate = CRIT - CritRate;
	if (CritRate < 0)
		CritRate = 0;

	int randos = rand() % 150;
	if (randos < CritRate)
		return true;
	return false;
}

//Uses an item and applies its effects
void itemUse(item useMe, PCharacter Party[], ECharacter eParty[], bool enemy, int target)
{
	string txt;
	switch (useMe.effect)
	{
	default:
		txt = " HP";
		break;
	case 0:
		txt = " HP";
		break;
	case 1:
		txt = " MP";
		break;
	case 2:
		txt = " STAM";
		break;
	case 3:
		if (Party[target].StateB == DEAD)
		{
			txt = " gets back up";
		}
		else
		{
			txt = " is already OK";
		}
		break;
	}
	if (enemy == false)
	{

		if (useMe.buddy == true)
		{
			if (useMe.potency > 0)
			{
				if (useMe.effect > 2)
				{
					cout << Party[target].name << txt << "!\n";
					sleep(1);
				}
				else
				{
					cout << Party[target].name << " restores " << useMe.potency << txt << "!\n";
					sleep(1);
				}
				int amount = useMe.effect;
				if (useMe.effect > 3)
					amount = amount - 4;
				hurt((useMe.potency * -1), Party[target], amount);
			}
			else
			{
				cout << "ERROR\n";
			}
		}
		else
		{
			atkType resistCheck = useMe.elem;
			int dmg = useMe.potency;
			dmg = dmg * eParty[target].resist[resistCheck];
			if (eParty[target].defend == true)
			{
				dmg = (dmg / 2);
			}
			cout << eParty[target].name << " took " << dmg << " damage!\n";
			sleep(1);
			hurt(dmg, eParty[target], 0);
		}
	}
	
}

//When a Reaction command is active, this determines if it triggers.
bool triggerCheck(int hero, int villain, attack POW, reaction thingToCheck, int targetHere, bool good)
{
	if (good != true)
	{
		targetHere = targetHere + 4;
	}
	if (thingToCheck.activate == CLOSE) //Are you attacking my target in Melee?
	{
		if (POW.delivery == MELEE)
		{
			if (thingToCheck.TarNum == targetHere)
				return true;
		}
	}
	if (thingToCheck.activate == ENERGY2) //Is this an energy attack?
	{
		if (POW.delivery == ENERGY)
		{
			if (thingToCheck.TarNum == targetHere || 9)
				return true;
		}
	}
	if (thingToCheck.activate == SIN_ATTACK) //Are you only attacking my target?
	{
		if (POW.victim == SINGLE)
		{
			if (thingToCheck.TarNum == targetHere)
			{
				return true;
			}
		}
	}
	if (thingToCheck.activate == DAMAGE) //Are you dealing damage to my target?
	{
		if (POW.ATK == true)
		{
			if (thingToCheck.TarNum == targetHere || 9)
				return true;
		}
	}
	if (thingToCheck.activate == TURNUP)
	{
		if (thingToCheck.TarNum == villain)
			return true;
	}
	return false;
}

void PCharacter::display()
{
	cout << "Name: " << name << "\nHealth: " << HP <<
		"\nAttack: " << PATK + stick.ATKpow << "\nDefense: " << PDEF << "\n";
}


/*   SELECTION SKILLS   */


//Allows you to select a special attack to use
attack PCharacter::displaySkill() //Selects Skills
{
	attack pickMe;
	while (pickMe.accuracy == -1)
	{
		int REVERSE;
		cout << "Which skill do you want to use? Type the number!\nYou can also type 0 to read a description.\n";
		int i = 0;
		while (this->moveset[i].accuracy != -1)
		{
			cout << i + 1 << ": ";
			this->moveset[i].printOut();
			i++;
		}
		cout << i + 1 << ": BACK\n";
		REVERSE = i;

		cin >> i;
		if (cin.fail())
		{
			cout << "Please do not type in letters. That is an\n";
			cin.clear();
			cin.ignore(1024, '\n');
			i = 11;
		}
		i--;
		if (i == REVERSE)
			return pickMe;
		if (i == -1)
		{
			for (int j = 0; j < 10; j++)
			{
				if (this->moveset[j].accuracy != -1)
				{
					this->moveset[j].describe();
				}
			}
			cout << "Press ENTER to continue...\n";
			cin.get();
			cin.get();
		}
		else
		{
			if (this->moveset[i].accuracy == 0)
			{
				cout << "ERROR. Please choose again.\n\n";
				sleep(2);
			}
			else
				pickMe = this->moveset[i];
		}
		if (pickMe.MPcost > this->MP)
		{
			cout << "Not enough MP!\n";
			sleep(1);
			pickMe.accuracy = -1;
		}
	}
	return pickMe;
}

//Allows you to select a reaction command to use
reaction PCharacter::displayReact() //Selects Reactions
{
	reaction pickMe;
	while (pickMe.effect == -1)
	{
		int REVERSE;
		cout << "Which reaction do you want to use? Type the number!\nYou can also type 0 to read a description.\n";
		int i = 0;
		while (this->react[i].effect != -1)
		{
			cout << i + 1 << ": " << this->react[i].TAG << "\n";
			i++;
		}
		cout << i + 1 << ": BACK\n";
		REVERSE = i;

		cin >> i;
		if (cin.fail())
		{
			cout << "Please do not type in letters. That is an\n";
			cin.clear();
			cin.ignore(1024, '\n');
			i = 9;
		}
		i--;
		if (i == REVERSE)
			return pickMe;
		if (i == -1)
		{
			cout << "Reactions are abilities that allow you to delay your turn until an enemy or friend's turn.\n"; {
				for (int j = 0; j < 8; j++)
				{
					if (this->react[j].effect != -1)
					{
						this->react[j].describe();
					}
				}
				cout << "Press ENTER to continue...\n";
				cin.get();
				cin.get();
			}
		}
		else
		{
			if (this->react[i].effect == -1)
				cout << "ERROR. Please choose again.\n\n";
			else
				pickMe = this->react[i];
		}
	}
	return pickMe;
}

//Allows you to select an item to use
item PCharacter::openBag(item Bag[])
{
	int REVERSE = 1;
	item selection;
	while (selection.currAmount == -1)
	{
		cout << "Which item would you like to use? Type the number!\nYou can also type 0 to read a description.\n";
		int i = 0; //Include "Page number marker", AKA the j value once a "page" has been printed.
		int j = 0;
		item pgSave[8];
		//bool pgNext = true;
		//bool pgPrev = false;
		while (i < 5)
		{
			if (Bag[j].currAmount > 0)
			{
				cout << i + 1 << ": " << Bag[j].name << "   " << Bag[j].currAmount << "\n";
				i++;
				pgSave[i] = Bag[j];
				REVERSE++;
			}
			j++;
			if (j == 10/*bag size*/)
			{
				i = 5;
				//pgNext = false;
			}
		}
		/*if (pgNext == true)
		{
		    cout << i + 1 << ": next page\n";
			REVERSE++;
		}*/
		cout << REVERSE << ": BACK\n";
		cin >> i;
		if (cin.fail())
		{
			cout << "Please do not type in letters. That is an\n";
			cin.clear();
			cin.ignore(1024, '\n');
			i = 99;
		}
		if (i == REVERSE)
		{
			return selection;
		}
		//Eventually figure out an item object that will be read here as a "page switch".
		if (pgSave[i].currAmount == -1)
			cout << "INVALID SELECTION. Please choose again.\n\n";
		else
			selection = pgSave[i];
	}
	Bag[selection.ID].currAmount--;
	return selection;
}

//Allows you to select an enemy to attack, assuming the ability allows you to
int PCharacter::targetATK(ECharacter Eparty[], TARGET hitme)
{
	if (hitme == ALL)
	{
		return 9;
	}

	if (hitme == RANDOM)
	{
		bool failstate = true;
		int roulette;
		while (failstate == false)
		{
			roulette = rand() % 5;
			if (Eparty[roulette].StateB == N_A || DEAD)
				failstate == false;
			else
				failstate == true;
		}
		return roulette;
	}

	ECharacter target;
	int choice;
	while (target.StateB == N_A)
	{
		cout << "Who will you target? Type their number, or type 0 to go back!\n";
		cin >> choice;
		if (cin.fail())
		{
			cout << "Please do not type in letters. That is an\n";
			cin.clear();
			cin.ignore(1024, '\n');
			choice = 0;
		}
		choice--;
		if (choice == -1)
			return choice;
		if (Eparty[choice].StateB == N_A || Eparty[choice].StateB == DEAD || choice < 0 || choice > 4)
			cout << "INVALID TARGET, TRY AGAIN\n";
		else
			target = Eparty[choice];
	}
	return choice;
}

//Allows you to target a friendly character, assuming the attack lets you.
int PCharacter::targetSUP(PCharacter Party[], TARGET helpme)
{
	if (helpme == ALL)
		return 10;
	if (helpme == RANDOM)
		return rand() % 9;
	PCharacter target;
	int choice;
	while (target.StateB == N_A)
	{
		cout << "Who will you help? Type their number, or type 0 to go back!\n";
		cin >> choice;
		if (cin.fail())
		{
			cout << "Please do not type in letters. That is an\n";
			cin.clear();
			cin.ignore(1024, '\n');
			choice = 0;
		}
		choice--;
		if (choice == -1)
			return choice;
		if (Party[choice].StateB == N_A || choice < 0 || choice > 3)
			cout << "INVALID TARGET, TRY AGAIN\n";
		else
			target = Party[choice];
	}
	return choice;
}


/*   BATTLE EFFECTS   */


//Restores stamina :3
void PCharacter::respite()
{
	this->STAM = this->STAM + 4;
	if (this->STAM > this->totalStorage[2])
		this->STAM = this->totalStorage[2];
}

//Activates a reaction command when triggered, defending and/or attacking your chosen target.
bool PCharacter::activate(reaction ability, PCharacter *target1, ECharacter *target2, attack POW)
{
	int effect = ability.effect;
	cout << "...But " << target1->name << ability.name << "\n";
	sleep(1);
	switch (effect)
	{
	case 0: // Use Skill
	{
		attack whallop = ability.Skill;
		whallop.mult = whallop.mult * ability.mult;
		target1->strike(*target2, whallop);
		target1->prepared = false;
		if (target2->StateB == DEAD)
		{
			return false;
		}
		return true;
	}
	case 1: // Defend the target
	{
		target1->defenseValue = 3;
		target1->defend = true;
		target2->strike(*target1, POW);
		target1->defenseValue = 2;
		target1->prepared = false;
		return false;
	}
	}
	return true;
}

//Calculates the damage to apply to the enemy
void PCharacter::strike(ECharacter &enemy, attack POW)
{
	if (POW.mult == 0)
	{
		if (enemy.StateB == DEAD)
			return;
		string statName;
		switch (POW.statEffect)
		{
		case 0:
		{
			cout << "NOW ANALYZING.";
			sleep(.5);
			cout << ".";
			sleep(.5);
			cout << ".";
			sleep(.5);
			cout << "\n\n";
			enemy.display();
			cout << "Press ENTER to continue.";
			cin.get();
			cin.get();
			return;
		}
		case 1:
		{
			enemy.PATK = enemy.PATK - POW.amount;
			statName = "P. attack";
			break;
		}
		}
		cout << enemy.name << "'s " << statName << " was lowered!\n";
		sleep(1);
		return;
	}

	for (int i = 0; i < POW.amount; i++)
	{
		if (enemy.StateB == DEAD)
			return;

		int hit = rand() % 100;
		if (POW.accuracy - hit > 0)
		{//Damage calculation (DEFENSE)
			int ATKnum;
			if (POW.magic == true)
			{
				ATKnum = this->MATK;
				//cout << "Is maaaaagic!\n";
			}
			else
				ATKnum = this->PATK;

			float dmg = ATKnum;
			dmg = dmg * POW.mult;
			if (POW.rules == WEAPON_STR || POW.rules == WEAPON_USE)
			{
				dmg = dmg + this->stick.ATKpow;
			}

			float dmgRes;
			if (POW.magic == false)
				dmgRes = enemy.PDEF / 2;
			else
				dmgRes = enemy.MDEF / 2;
			dmg = dmg - dmgRes;
			atkType resistCheck = SLH;
			if (POW.type1 == WPNTYPE1 || POW.type1 == WPNTYPE2)
				resistCheck = this->stick.elem1;
			else
				resistCheck = POW.type1;
			dmg = dmg * enemy.resist[resistCheck];
			if (enemy.defend == true)
			{
				dmg = (dmg / 2); // ALTER TO INCLUDE DEFENSE VALUE ONCE ADDED TO ENEMY
			}
			int result = dmg * 1;
			//Damage calculation (VARIATION)
			int cap;
			if (POW.magic == false)
				cap = this->totalStorage[3] - this->VAR;
			else
				cap = this->totalStorage[4] - this->VAR;
			if (cap <= 0)
				cap = 1;
			result = result - rand() % cap;
			if (result <= 0)
				result = 1;
			if (critStrike(this->CRIT, enemy.MDEF) == true)
			{
				cout << "BAM! ";
				result = result * 2;
			}

			cout << enemy.name << " took " << result << " damage!\n";
			sleep(1);
			hurt(result, enemy, 0);
			this->damageDone = this->damageDone + result;
		}
		else
		{
			cout << this->name << " missed!\n";
			sleep(1);
		}
			
	}
}

//Calculates and applies a skill used on a party member
void PCharacter::help(PCharacter &buddy, attack heal)
{
	if (heal.mult == 0)
	{
		string statName;
		switch (heal.statEffect)
		{
		case 0:
		{
			cout << "ERROR: WHY ARE YOU SCANNING YOUR FRIENDS\n";
			sleep(1);
			return;
		}
		case 1:
		{
			buddy.PATK = buddy.PATK + heal.amount;
			statName = "P. attack";
			break;
		}
		}
		cout << buddy.name << "'s " << statName << " was enhanced!\n";
		sleep(1);
		return;
	}
	int ATKnum = this->MATK;
	ATKnum = ATKnum * heal.mult;
	int cap = this->MATK - this->VAR;
	if (cap <= 0)
		cap = 0;
	ATKnum = ATKnum - rand() % cap;
	if (ATKnum > 0)
		ATKnum = 0;

	cout << buddy.name << " healed " << ATKnum * -1 << " damage!\n";
	sleep(1);

	hurt(ATKnum, buddy, 0);

	if (buddy.StateB == DEAD)
	{
		if (heal.amount == 1)
		{
			buddy.StateB = FINE;
			cout << buddy.name << " got back up!\n";
			sleep(1);
		}
		else
		{
			buddy.HP = 0;
			cout << "...but " << buddy.name << " is still dead.\n";
			sleep(1);
		}
	}
}


/*   TURN FUNCTION   */

//Allows you to determine what your character does with their turn
void PCharacter::takeTurn(PCharacter Party[], ECharacter eParty[], item bag[])
{	
	if (this->StateB == TIRED)
	{
		this->StateB = FINE;
		this->PDEF = this->PDEF + (this->totalStorage[5] / 2);
		this->MDEF = this->MDEF + (this->totalStorage[6] / 2);
		this->STAM = this->totalStorage[2] / 2;
		cout << this->name << " has regained their strength!\n";
		sleep(1);
		return;
	}

	int choice;
	bool action = true;

	this->prepared = false;
	this->defend = false;

	while (action == true)
	{
		cout << "\n" << this->name << "'s turn! What will you do?\n";
		cin >> choice;
		if (cin.fail())
		{
			cout << "Please do not type in letters. That is an\n";
			cin.clear();
			cin.ignore(1024, '\n');
		}
		switch (choice) {
		case 1: //regular attack
		{
			int yourFistHere = this->targetATK(eParty, this->Basic.victim);
			if (yourFistHere == -1)
				break;
			cout << "\n" << this->name << " " << this->Basic.name << "\n";
			sleep(1);
			
			for (int i = 0; i < 5; i++)
			{
				if (eParty[i].prepared == true)
				{
					if (triggerCheck(-1, i, choice, eParty[i].activeReac, yourFistHere, false) == true)
					{
						if (eParty[i].activate(eParty[i].activeReac, this, &eParty[i], this->Basic) == false)
							return;
					}
				}
			}

			this->strike(eParty[yourFistHere], this->Basic);

			this->STAM = this->STAM - (this->Basic.STAMcost + this->stick.Weight);
			if (this->STAM < 0)
			{
				this->StateB = TIRED;
				this->PDEF = this->PDEF - (this->totalStorage[5] / 2);
				this->MDEF = this->MDEF - (this->totalStorage[6] / 2);
				cout << this->name << " is exhausted!\n";
				sleep(1);
			}
			action = false;
			break;
		}
		case 2: //use special attack
		{
			attack choice = this->displaySkill(); 
			if (choice.accuracy == -1)
				break; //Return to menu
			int yourFistHere = 0;

			if (choice.ATK == false)
				yourFistHere = this->targetSUP(Party, choice.victim);
			else
				yourFistHere = this->targetATK(eParty, choice.victim);

			if (yourFistHere == -1)
				break;

			cout << "\n" << this->name << " " << choice.name << "\n";
			sleep(1);

			for (int i = 0; i < 5; i++)
			{
				if (eParty[i].prepared == true)
				{
					if (triggerCheck(-1, i, choice, eParty[i].activeReac, yourFistHere, false) == true)
					{
						if (eParty[i].activate(eParty[i].activeReac, this, &eParty[i], choice) == false)
							return;
					}
				}
			}
			this->MP = this->MP - choice.MPcost;
			if (choice.ATK == false)
			{
				this->help(Party[yourFistHere], choice);
				action = false;
				break;
			}
			if (choice.victim == ALL)
			{
				for (int i = 0; i < 5; i++)
				{
					if (eParty[i].StateB != N_A)
					{
						this->strike(eParty[i], choice);
					}
				}
			}
			else
			{
				this->strike(eParty[yourFistHere], choice);
				if (choice.victim == ADJACENT) //Currently breaks if target is less than 0! Makes pretty ERROR graphics!
				{
					if ((yourFistHere - 1) > -1)
					{
						if (eParty[yourFistHere - 1].StateB != N_A)
							this->strike(eParty[yourFistHere - 1], choice);
					}
					if ((yourFistHere + 1) < 4)
					{
						if (eParty[yourFistHere + 1].StateB != N_A)
							this->strike(eParty[yourFistHere + 1], choice);
					}
				}
			}

			this->STAM = this->STAM - choice.STAMcost;
			if (choice.rules == (WEAPON_STR || WEAPON_USE))
				this->STAM = this->STAM - this->stick.Weight;
			if (this->STAM < 0)
			{
				this->StateB = TIRED;
				this->PDEF = this->PDEF - (this->totalStorage[5] / 2);
				this->MDEF = this->MDEF - (this->totalStorage[6] / 2);
				cout << this->name << " is exhausted!\n";
				sleep(1);
			}

			action = false;
			break;
		}
		case 3: //use reaction command
		{
			reaction Choice = this->displayReact();
			if (Choice.effect == -1)
				break;

			switch (Choice.victim)
			{
			case 0: //Targets an enemy
			{
				Choice.TarNum = this->targetATK(eParty, SINGLE) + 4;
				break;
			}
			case 1: //Targets all combatants
			{
				Choice.TarNum = 9;
				break;
			}
			case 2: //Not applicable
			{
				cout << "INVALID ABILITY\n";
				break;
			}
			case 3: //Not applicable
			{
				cout << "INVALID ABILITY\n";
				break;
			}
			case 4: //Targets self
			{
				int i = 0;
				while (Choice.TarNum < 0)
				{
					if (this->name == Party[i].name)
					{
						Choice.TarNum = i;
						break;
					}
					else
					{
						i++;
					}
				}
				break;
			}
			case 5: //Targets friend
			{
				while (Choice.TarNum == -1)
				{
					Choice.TarNum = this->targetSUP(Party, SINGLE);
					if (Choice.TarNum == -1)
						break;
					if (Party[Choice.TarNum].name == this->name)
					{
						Choice.TarNum = -1;
						cout << "You can't choose yourself!\n";
						sleep(1);
					}
				}
				break;
			}
			default:
			{
				cout << "INVALID ABILITY\n";
				break;
			}
			}

			if (Choice.TarNum == -1)
				break;
			cout << "\n" << this->name << " prepares!\n";
			sleep(1);
			this->activeReac = Choice;
			this->prepared = true;

			for (int i = 0; i < 5; i++)
			{
				if (eParty[i].prepared == true)
				{
					if (triggerCheck(-1, i, NULL, eParty[i].activeReac, -1, false) == true)
					{
						if (eParty[i].activate(eParty[i].activeReac, this, &eParty[i], -1) == false)
							return;
					}
				}
			}

			action = false;
			break;
		}
		case 4: //Use Items
		{
			item useThis = this->openBag(bag);
			int TarTar;
			if (useThis.currAmount == -1)
				break;
			if (useThis.buddy == true)
			{
				TarTar = Party[0].targetSUP(Party, SINGLE);
			}
			else
			{
				TarTar = Party[0].targetATK(eParty, SINGLE);
			}
			if (TarTar == -1)
				break;
			cout << "\n" << this->name << " uses a " << useThis.name << "!\n";
			sleep(1);

			for (int i = 0; i < 5; i++)
			{
				if (eParty[i].prepared == true)
				{
					if (triggerCheck(-1, i, NULL, eParty[i].activeReac, -1, false) == true)
					{
						if (eParty[i].activate(eParty[i].activeReac, this, &eParty[i], -1) == false)
							return;
					}
				}
			}
			this->STAM = this->STAM - useThis.UseEffort;
			itemUse(useThis, Party, eParty, false, TarTar);
			action = false;
			break;
		}
		case 5: //Special command
		{
			cout << "I'm sorry. This is not functional yet.\n";
			sleep(2);
			break;
		}
		case 6: //defend
		{
			cout << this->name << " defends!\n";
			sleep(1);
			this->defend = true;
			this->STAM = this->STAM + 10;
			if (this->STAM > this->totalStorage[2])
				this->STAM = this->totalStorage[2];

			for (int i = 0; i < 5; i++)
			{
				if (eParty[i].prepared == true)
				{
					if (triggerCheck(-1, i, NULL, eParty[i].activeReac, -1, false) == true)
					{
						if (eParty[i].activate(eParty[i].activeReac, this, &eParty[i], -1) == false)
							return;
					}
				}
			}

			action = false;
			break;
		}
		case 7: //Flee 
		{
			cout << "I'm sorry. This is not functional yet.\n";
			sleep(2);
			break;
		}
		case 8: //old debug choice
		{
			this->display();
			eParty[0].display();
			break;
		}
		default:
			cout << "INVALID COMMAND\n";
		}
	}
	//Include check for healing statuses here
}





/*    ~~~~~      ENEMY FUNCTIONS        ~~~~~     */			



	

	void ECharacter::respite()
	{
		this->STAM = this->STAM + 3;
		if (this->STAM > this->totalStorage[2])
			this->STAM = this->totalStorage[2];
	}

	//Copy of PCharacter's Reaction Activation function. May blend the two eventually
	bool ECharacter::activate(reaction ability, PCharacter *target1, ECharacter *target2, attack POW)
	{
		int effect = ability.effect;
		cout << "...But " << target2->name << ability.name << "\n";
		sleep(1);
		switch (effect)
		{
		case 0: // Use Skill
		{
			attack whallop = ability.Skill;
			whallop.mult = whallop.mult * ability.mult;
			target2->strike(*target1, whallop);
			target2->prepared = false;
			if (target1->StateB == DEAD)
			{
				return false;
			}
			return true;
		}
		case 1: // Defend the target
		{
			target2->defenseValue = 3;
			target2->defend = true;
			target1->strike(*target2, POW);
			target2->defenseValue = 2;
			target2->prepared = false;
			return false;
		}
		}
		return true;
	}

	//Copy of PCharacter's Damage calculation function. May blend the two eventually
	void ECharacter::strike(PCharacter &hero, attack POW)
	{
		if (hero.StateB == DEAD) //Adjacent or All target case
		{
			return;
		}

		if (POW.mult == 0) //Status Effecting abilities
		{
			string statName;
			switch (POW.statEffect)
			{
			default:
				cout << "AN ERROR HAS OCCURED\n";
			case 0:
			{
				cout << "The enemy has scanned you!\n";
				sleep(1);
				return;
			}
			case 1:
			{
				hero.PATK = hero.PATK - POW.amount;
				statName = "P. attack";
				break;
			}
			}
			cout << hero.name << "'s " << statName << " was lowered!\n";
			sleep(1);
			return;
		}

		for (int i = 0; i < POW.amount; i++)
		{
			if (hero.StateB == DEAD) //Adjacent or All target case
			{
				return;
			}
			int hit = clock() % 100;
			if (POW.accuracy - hit > 0)
			{ //Damage calculation (DEFENSE)
				int ATKnum;
				if (POW.magic == false)
					ATKnum = this->PATK;
				else
					ATKnum = this->MATK;
				float dmg = ATKnum;
				dmg = dmg * POW.mult;
				float dmgRes;
				if (POW.magic == false)
					dmgRes = hero.PDEF / 2;
				else
					dmgRes = hero.MDEF / 2;
				dmg = dmg - dmgRes;
				atkType resistCheck = SLH;
				if (POW.type1 == WPNTYPE1 || POW.type1 == WPNTYPE2)
					resistCheck = this->Stick.elem1;
				else
					resistCheck = POW.type1;
				dmg = dmg * hero.resist[resistCheck];
				if (hero.defend == true) //defense check
				{
					dmg = (dmg / hero.defenseValue);
				}
				int result = dmg * 1;
				//Damage calculation (VARIATION)
				int cap;
				if (POW.magic == false)
					cap = this->totalStorage[3] - this->VAR;
				else
					cap = this->totalStorage[4] - this->VAR;
				if (cap <= 0)
					cap = 0;
				result = result - rand() % cap;
				if (result <= 0)
				{
					result = 1;
				}
				if (critStrike(this->CRIT, hero.MDEF) == true)
				{
					cout << "BAM! ";
					result = result * 2;
				}

				cout << hero.name << " took " << result << " damage!\n";
				sleep(1);
				hurt(result, hero, 0);

			}
			else
			{
				cout << this->name << " missed!\n";
				sleep(1);
			}
		}
		this->STAM = this->STAM - POW.STAMcost;
		if (this->STAM < 0)
		{
			this->StateB = TIRED;
			this->PDEF = this->PDEF / 2;
			this->MDEF = this->MDEF / 2;
			cout << this->name << " is exhausted!\n";
			sleep(1);
		}
	}

	//Copy of PCharacter's Friendly attack function. May blend the two eventually
	void ECharacter::help(ECharacter &buddy, attack heal)
	{
		if (heal.mult == 0)
		{
			string statName;
			switch (heal.statEffect)
			{
			case 0:
			{
				cout << "ERROR: NOT SUPPOSED TO BE A TARGET\n";
				sleep(1);
				return;
			}
			case 1:
			{
				buddy.PATK = buddy.PATK + heal.amount;
				statName = "P. attack";
				break;
			}
			}
			cout << buddy.name << "'s " << statName << " was enhanced!\n";
			sleep(1);

			this->STAM = this->STAM - heal.STAMcost;
			if (this->STAM < 0)
			{
				this->StateB = TIRED;
				this->PDEF = this->PDEF - (this->totalStorage[5] / 2);
				this->MDEF = this->MDEF - (this->totalStorage[6] / 2);
				cout << this->name << " is exhausted!\n";
				sleep(1);
			}

			return;
		}
		int ATKnum = this->MATK;
		ATKnum = ATKnum * heal.mult;
		int cap = this->MATK - this->VAR;
		if (cap <= 0)
			cap = 0;
		ATKnum = ATKnum - rand() % cap;
		if (ATKnum > 0)
			ATKnum = 0;

		cout << buddy.name << " healed " << ATKnum * -1 << " damage!\n";
		sleep(1);

		hurt(ATKnum, buddy, 0);

		if (buddy.StateB == DEAD)
		{
			if (heal.amount == 1)
			{
				buddy.StateB = FINE;
				cout << buddy.name << " got back up!\n";
				sleep(1);
			}
			else
			{
				buddy.HP = 0;
				cout << "...but " << buddy.name << " is still dead.\n";
				sleep(1);
			}
		}

		this->STAM = this->STAM - heal.STAMcost;
		if (this->STAM < 0)
		{
			this->StateB = TIRED;
			this->PDEF = this->PDEF - (this->totalStorage[5] / 2);
			this->MDEF = this->MDEF - (this->totalStorage[6] / 2);
			cout << this->name << " is exhausted!\n";
			sleep(1);
		}
	}

	//ECharacter's AI call function
	void ECharacter::takeTurn(PCharacter party[], ECharacter eParty[])
	{
		if (this->StateB == DEAD)
			return;
		if (this->StateB == TIRED)
		{
			this->StateB = FINE;
			this->PDEF = this->PDEF + (this->totalStorage[5] / 2);
			this->MDEF = this->MDEF + (this->totalStorage[6] / 2);
			this->STAM = this->totalStorage[2] / 2;
			cout << this->name << " has regained their strength!\n";
			sleep(1);
			return;
		}
		respite();

		int FiteMe = this->target(party, eParty);
		if (FiteMe < 0)
		{
			return;
		}

		attack choice = this->moveSelect();
		/* Reaction Check */
		if (choice.amount < 0)
		{
			if (choice.ATK == false)
			{
				//DEFEND PROTOCOL
				cout << "\n" << this->name << " defends!\n";
				sleep(1);
				this->defend = true;
				this->STAM = this->STAM + 10;
				if (this->STAM > this->totalStorage[2])
					this->STAM = this->totalStorage[2];
				return;
			}
			else
			{
				//REACTION PROTOCOL
				reaction select = this->reactSelect(FiteMe);
				cout << "\n" << this->name << " prepares!\n";
				sleep(1);
				this->activeReac = select;
				this->prepared = true;
				return;
			}
		}
		else 
		{
			cout << "\n" << this->name << " " << choice.name << "\n";
			sleep(1);
		}
		
		for (int i = 0; i < 4; i++)
		{
			if (party[i].prepared == true)
			{
				bool test = triggerCheck(i, -1, choice, party[i].activeReac, FiteMe, true);
				if (test == true)
				{
					if (party[i].activate(party[i].activeReac, &party[i], this, choice) == false)
						return;
				}
			}
		}

		if (choice.ATK == false)
		{
			this->help(eParty[FiteMe], choice);
		}
		else
		{
			this->strike(party[FiteMe], choice);
		}

	}

