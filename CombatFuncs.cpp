#include "stdafx.h"
#include "Combat.h"
#include "Structs.h"
#include <time.h>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

/* This file contains all the functions the combat engine uses to run. */
int uHitRate = 0;

void sleep(float sec)
{
	clock_t wait;
	wait = clock();
	while (clock() != wait + (sec * 1000));
}

//Damages (heals?) a player character
void hurt(int dmg, BattleEntity &victim, int stat) //Alter to allow changes in STAM and MP
{
	if (stat == 0) //Affecting HP
	{
		victim.HP = victim.HP - dmg;
		if (victim.HP > victim.totalStorage[0])
		{
			victim.HP = victim.totalStorage[0];
			cout << victim.name << " is fully healed!!!\n";
			sleep(1);
		}
		if (victim.HP <= 0)
		{
			cout << victim.name << " is down!\n";
			sleep(1);
			victim.StateB = DEAD;
			victim.HP = 0;
			victim.damageDone = 0;
		}
	}
	if (stat == 1) //Affecting MP
	{
		victim.MP = victim.MP - dmg;
		if (victim.MP > victim.totalStorage[1])
		{
			victim.MP = victim.totalStorage[1];
			cout << victim.name << " is fully powered!!!\n";
			sleep(1);
		}
		if (victim.MP <= 0)
		{
			victim.MP = 0;
		}
	}
	if (stat == 2) //Affecting STAM
	{
		victim.STAM = victim.STAM - dmg;
		if (victim.STAM > victim.totalStorage[2])
		{
			victim.STAM = victim.totalStorage[2];
			cout << victim.name << " is fully energized!!!\n";
			sleep(1);
		}
		if (victim.STAM <= 0)
		{
			victim.StateB = TIRED;
			victim.PDEF = victim.PDEF - (victim.totalStorage[5] / 2);
			victim.MDEF = victim.MDEF - (victim.totalStorage[6] / 2);
			cout << victim.name << " is exhausted!\n";
			sleep(1);
		}
	}
	if (stat == 3) //REVIVAL!
	{
		dmg = dmg * -1;
		if (victim.StateB == DEAD)
		{
			victim.StateB = FINE;
			int revAmount = (victim.totalStorage[0] / (100 / dmg));
			victim.HP = revAmount;
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

			switch (eParty[target].resist[resistCheck])
			{
			default:
				break;
			case WEAK:
			{
				dmg = dmg * 1.5;
				cout << eParty[target].name << " winced in pain!\n";
				sleep(1);
				//Other effects, raise your morale, lower theirs, reduce their speed
				break;
			}
			case NORM:
				break;
			case RESISTANT:
			{
				dmg = dmg * 0.25;
				cout << eParty[target].name << " was unfazed!\n";
				sleep(1);
				//Any other effects to add? Morale effects?
				break;
			}
			case IMMUNE:
			{
				dmg = dmg * 0;
				cout << eParty[target].name << " was unaffected!\n";
				sleep(1);
				//Any other effects to add? Morale effects?
				break;
			}
			case REFLECT:
			{
				cout << "...But the attack bounced back!\n";
				sleep(1);
				//hurt(dmg, this, 0); Whatever. I'll fix it later.
				break;
			}
			case ABSORB:
			{
				dmg = dmg * -1;
				cout << eParty[target].name << " absorbed the attack!\n";
				sleep(1);
				//Any other effects to add? Morale effects?
				break;
			}
			}

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
//All Battle Effects are shared between player and enemy

//Restores stamina :3
void BattleEntity::respite()
{
	this->STAM = this->STAM + 5;
	if (this->STAM > this->totalStorage[2])
		this->STAM = this->totalStorage[2];
}

//Activates a reaction command when triggered, defending and/or attacking your chosen target.
bool BattleEntity::activate(reaction ability, BattleEntity *target1, BattleEntity *target2, attack POW)
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
		target1->strike(*target2, whallop, false);
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
		target2->strike(*target1, POW, false);
		target1->defenseValue = 2;
		target1->prepared = false;
		return false;
	}
	}
	return true;
}

//Calculates the damage to apply to the enemy
void BattleEntity::strike(BattleEntity &enemy, attack POW, bool reflected) 
{
	if (POW.mult == 0)
	{
		if (enemy.StateB == DEAD)
			return;
		string statName;
		switch (POW.statEffect) // 0 - SCAN  1 - PATK, 2 - MATK, 3 - PDEF, 4 - MDEF, 5 - SPD
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
			if (enemy.good == false)
			{
				//badChild(enemy);
			}
			else
			{
				cout << "The enemy has scanned you!\n";
			}
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
		case 2:
		{
			enemy.MATK = enemy.MATK - POW.amount;
			statName = "M. attack";
			break;
		}
		case 3:
		{
			enemy.PDEF = enemy.PDEF - POW.amount;
			statName = "P. defence";
			break;
		}
		case 4:
		{
			enemy.MDEF = enemy.MDEF - POW.amount;
			statName = "M. defence";
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

		int hit = (rand() % 100) + uHitRate;
		if (POW.accuracy - hit > 0)
		{//Damage calculation (DEFENSE)
			uHitRate++;
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

			switch (enemy.resist[resistCheck])
			{
			default:
				break;
			case WEAK:
			{
				dmg = dmg * 1.5;
				cout << enemy.name << " winced in pain!\n";
				sleep(1);
				//Other effects, raise your morale, lower theirs, reduce their speed
				break;
			}
			case NORM:
				break;
			case RESISTANT:
			{
				dmg = dmg * 0.25;
				cout << enemy.name << " was unfazed!\n";
				sleep(1);
				//Any other effects to add? Morale effects?
				break;
			}
			case IMMUNE:
			{
				dmg = dmg * 0;
				cout << enemy.name << " was unaffected!\n";
				sleep(1);
				//Any other effects to add? Morale effects?
				break;
			}
			case REFLECT:
			{
				if (reflected == true)
					break;
				cout << "...But the attack bounced back!\n";
				sleep(1);
				//hurt(dmg, this, 0); Whatever. I'll fix it later.
				break;
			}
			case ABSORB:
			{
				dmg = dmg * -1;
				cout << enemy.name << " absorbed the attack!\n";
				sleep(1);
				//Any other effects to add? Morale effects?
				break;
			}
			}
			if (enemy.defend == true)
			{
				dmg = (dmg / enemy.defenseValue); // ALTER TO INCLUDE DEFENSE VALUE ONCE ADDED TO ENEMY
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
			uHitRate = -5;
		}
			
	}
}

//Calculates and applies a skill used on a party member
void BattleEntity::help(BattleEntity &buddy, attack heal)
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
bool PCharacter::takeTurn(PCharacter Party[], ECharacter eParty[], item bag[])
{	
	if (this->StateB == TIRED)
	{
		this->StateB = FINE;
		this->PDEF = this->PDEF + (this->totalStorage[5] / 2);
		this->MDEF = this->MDEF + (this->totalStorage[6] / 2);
		this->STAM = this->totalStorage[2] / 2;
		cout << this->name << " has regained their strength!\n";
		sleep(1);
		return true;
	}

	int choice;

	this->prepared = false;
	this->defend = false;

	
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
			return false;
		cout << "\n" << this->name << " " << this->Basic.name << "\n";
		sleep(1);

		for (int i = 0; i < 5; i++)
		{
			if (eParty[i].prepared == true)
			{
				if (triggerCheck(-1, i, choice, eParty[i].activeReac, yourFistHere, false) == true)
				{
					if (eParty[i].activate(eParty[i].activeReac, this, &eParty[i], this->Basic) == false)
						return true;
				}
			}
		}
		this->strike(eParty[yourFistHere], this->Basic, false);
		this->STAM = this->STAM - (this->Basic.STAMcost + this->stick.Weight);
		if (this->STAM < 0)
		{
			this->StateB = TIRED;
			this->PDEF = this->PDEF - (this->totalStorage[5] / 2);
			this->MDEF = this->MDEF - (this->totalStorage[6] / 2);
			cout << this->name << " is exhausted!\n";
			sleep(1);
		}
		break;
	}
	case 2: //use special attack
	{
		attack choice = this->displaySkill(); 
		if (choice.accuracy == -1)
			return false; //Return to menu
		int yourFistHere = 0;

		if (choice.ATK == false)
			yourFistHere = this->targetSUP(Party, choice.victim);
		else
			yourFistHere = this->targetATK(eParty, choice.victim);

		if (yourFistHere == -1)
			return false;

		cout << "\n" << this->name << " " << choice.name << "\n";
		sleep(1);

		for (int i = 0; i < 5; i++)
		{
			if (eParty[i].prepared == true)
			{
				if (triggerCheck(-1, i, choice, eParty[i].activeReac, yourFistHere, false) == true)
				{
					if (eParty[i].activate(eParty[i].activeReac, this, &eParty[i], choice) == false)
						return true;
				}
			}
		}
		this->MP = this->MP - choice.MPcost;
		if (choice.ATK == false)
		{
			this->help(Party[yourFistHere], choice);
			break;
		}
		if (choice.victim == ALL)
		{
			for (int i = 0; i < 5; i++)
			{
				if (eParty[i].StateB != N_A)
				{
					this->strike(eParty[i], choice, false);
				}
			}
		}
		else
		{
			this->strike(eParty[yourFistHere], choice, false);
			if (choice.victim == ADJACENT) //Currently breaks if target is less than 0! Makes pretty ERROR graphics!
			{
				if ((yourFistHere - 1) > -1)
				{
					if (eParty[yourFistHere - 1].StateB != N_A)
						this->strike(eParty[yourFistHere - 1], choice, false);
				}
				if ((yourFistHere + 1) < 4)
				{
					if (eParty[yourFistHere + 1].StateB != N_A)
						this->strike(eParty[yourFistHere + 1], choice, false);
				}
			}
		}

		this->STAM = this->STAM - choice.STAMcost;
		if (choice.rules == WEAPON_STR || choice.rules == WEAPON_USE)
			this->STAM = this->STAM - this->stick.Weight;
		if (this->STAM < 0)
		{
			this->StateB = TIRED;
			this->PDEF = this->PDEF - (this->totalStorage[5] / 2);
			this->MDEF = this->MDEF - (this->totalStorage[6] / 2);
			cout << this->name << " is exhausted!\n";
			sleep(1);
		}

		break;
	}
	case 3: //use reaction command
	{
		reaction Choice = this->displayReact();
		if (Choice.effect == -1)
			return false;

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
			return false;
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
						return true;
				}
			}
		}

		break;
	}
	case 4: //Use Items
	{
		item useThis = this->openBag(bag);
		int TarTar;
		if (useThis.currAmount == -1)
			return false;
		if (useThis.buddy == true)
		{
			TarTar = Party[0].targetSUP(Party, SINGLE);
		}
		else
		{
			TarTar = Party[0].targetATK(eParty, SINGLE);
		}
		if (TarTar == -1)
			return false;
		cout << "\n" << this->name << " uses a " << useThis.name << "!\n";
		sleep(1);

		for (int i = 0; i < 5; i++)
		{
			if (eParty[i].prepared == true)
			{
				if (triggerCheck(-1, i, NULL, eParty[i].activeReac, -1, false) == true)
				{
					if (eParty[i].activate(eParty[i].activeReac, this, &eParty[i], -1) == false)
						return true;
				}
			}
		}
		this->STAM = this->STAM - useThis.UseEffort;
		itemUse(useThis, Party, eParty, false, TarTar);
		break;
	}
	case 5: //Special command
	{
		cout << "I'm sorry. This is not functional yet.\n";
		sleep(2);
		return false;
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
						return true;
				}
			}
		}

		break;
	}
	case 7: //Flee 
	{
		cout << "I'm sorry. This is not functional yet.\n";
		sleep(2);
		return false;
	}
	case 8: //old debug choice
	{
		this->display();
		eParty[0].display();
		return false;
	}
	default:
		cout << "INVALID COMMAND\n";
		return false;
	}
	
	//Include check for healing statuses here
	return true;
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
			this->strike(party[FiteMe], choice, false);
		}

	}

