#include "stdafx.h"
#include "Structs.h"
#include <string>
#include <iostream>

using namespace std;
//Includes Skills and Reactions

/*  This is the Attack section of this file. Should it get too big or unweildy, it will be transferred to its own file.  */
attack::attack()
{
	TAG = "ERROR";
	mult = 1;
	amount = 0;
	MPcost = 0;
	STAMcost = 0;
	victim = SINGLE;
	magic = false;
	ATK = true;
	accuracy = -1;
	type1 = SLH;
	type2 = SLH;
	delivery = MELEE;
	name = "commits Seppuku!";
	DESC = "means that this is not a real ability.";
}

attack::attack(int atkNum)
{
	switch (atkNum)
	{
	default:
		break;
	case(0):
	{
		TAG = "Basic attack";
		mult = 1;
		amount = 1;
		MPcost = 0;
		STAMcost = 8;
		victim = SINGLE;
		magic = false;
		ATK = true;
		support = true;
		accuracy = 94;
		type1 = WPNTYPE1;
		type2 = WPNTYPE2;
		delivery = WEAPON;
		rules = WEAPON_STR;
		name = "attacks!";
		DESC = "strikes the enemy with your weapon.";
		break;
	}
	case(1):
	{
		TAG = "Triple Slash";
		mult = 1;
		amount = 3;
		MPcost = 0;
		STAMcost = 30;
		victim = SINGLE;
		magic = false;
		ATK = true;
		support = false;
		accuracy = 84;
		type1 = SLH;
		type2 = SLH;
		delivery = MELEE;
		rules = WEAPON_STR;
		name = "strikes multiple times!";
		DESC = "attacks the enemy three times with a sharp weapon.";
		break;
	}
	case(2):
	{
		TAG = "Combo Strike";
		mult = 1;
		amount = 3;
		MPcost = 0;
		STAMcost = 30;
		victim = SINGLE;
		magic = false;
		ATK = true;
		support = false;
		accuracy = 84;
		type1 = FRC;
		type2 = FRC;
		delivery = MELEE;
		rules = WEAPON_STR;
		name = "strikes multiple times!";
		DESC = "attacks the enemy three times with a blunt weapon.";
		break;
	}
	case(3):
	{
		TAG = "Lume ";
		mult = 1.5;
		amount = 1;
		MPcost = 5;
		STAMcost = 5;
		victim = SINGLE;
		magic = true;
		ATK = true;
		support = false;
		accuracy = 99;
		type1 = FIR;
		type2 = FIR;
		delivery = ENERGY;
		rules = SPELL;
		name = "uses Lume!";
		DESC = "summons a ring of fire to burn an enemy.";
		break;
	}
	case(4):
	{
		TAG = "Xeo  ";
		mult = 1.5;
		amount = 1;
		MPcost = 5;
		STAMcost = 5;
		victim = SINGLE;
		magic = true;
		ATK = true;
		support = false;
		accuracy = 99;
		type1 = ICE;
		type2 = ICE;
		delivery = ENERGY;
		rules = SPELL;
		name = "uses Xeo!";
		DESC = "summons icicles to attack the enemy";
		break;
	}
	case(5):
	{
		TAG = "Raio ";
		mult = 1.5;
		amount = 1;
		MPcost = 5;
		STAMcost = 5;
		victim = SINGLE;
		magic = true;
		ATK = true;
		support = false;
		accuracy = 99;
		type1 = ELC;
		type2 = ELC;
		delivery = ENERGY;
		rules = SPELL;
		name = "uses Raio!";
		DESC = "summons a burst of electricity to attack an enemy.";
		break;
	}
	case(6):
	{
		TAG = "Vento";
		mult = 1.5;
		amount = 1;
		MPcost = 5;
		STAMcost = 5;
		victim = SINGLE;
		magic = true;
		ATK = true;
		support = false;
		accuracy = 99;
		type1 = WND;
		type2 = FRC;
		delivery = ENERGY;
		rules = SPELL;
		name = "uses Vento!";
		DESC = "summons a gale to throw the enemy.";
		break;
	}
	case(7):
	{
		TAG = "Haya ";
		mult = -2;
		amount = 0;
		MPcost = 5;
		STAMcost = 5;
		victim = SINGLE;
		magic = true;
		ATK = false;
		support = false;
		accuracy = 200;
		type1 = LIF;
		type2 = LIF;
		delivery = ENERGY;
		rules = SPELL;
		name = "uses Haya!";
		DESC = "soothes a friend with healing energy.";
		break;
	}
	case(8):
	{
		TAG = "Plaga";
		mult = 1.5;
		amount = 1;
		MPcost = 5;
		STAMcost = 5;
		victim = SINGLE;
		magic = true;
		ATK = true;
		support = false;
		accuracy = 99;
		type1 = NEC;
		type2 = NEC;
		delivery = ENERGY;
		rules = SPELL;
		name = "uses Plaga!";
		DESC = "grips an enemy with the chill of death.";
		break;
	}
	case(9):
	{
		TAG = "Sonic Blade";
		mult = 1.5;
		amount = 1;
		MPcost = 8;
		STAMcost = 10;
		victim = ADJACENT;
		magic = false;
		ATK = true;
		support = false;
		accuracy = 89;
		type1 = SON;
		type2 = SLH;
		delivery = PROJECTILE;
		rules = WEAPON_USE;
		name = "creates a blade of sound!";
		DESC = "slashes several enemies from a distance with sound.";
		break;
	}
	case(10):
	{
		TAG = "Sonic Shout";
		mult = 1;
		amount = 1;
		MPcost = 8;
		STAMcost = 13;
		victim = ALL;
		magic = true;
		ATK = true;
		support = false;
		accuracy = 89;
		type1 = SON;
		type2 = SLH;
		delivery = ENERGY;
		rules = SPELL;
		name = "screams with incredible force!";
		DESC = "damages all enemies with a sonic wave.";
		break;
	}
	case(11):
	{
		TAG = "Scan";
		mult = 0;
		amount = 1;
		MPcost = 2;
		STAMcost = 5;
		victim = SINGLE;
		magic = true;
		ATK = true;
		support = false;
		accuracy = 200;
		type1 = ELD;
		type2 = ELD;
		delivery = ENERGY;
		rules = SPELL;
		name = "scrutinizes the enemy!";
		DESC = "reveals an opponent's weaknesses.";
		break;
	}
	case(12):
	{
		TAG = "Exofri";
		mult = 0;
		amount = 7;
		MPcost = 10;
		STAMcost = 0;
		victim = SINGLE;
		magic = true;
		ATK = false;
		support = false;
		accuracy = 200;
		type1 = FIR;
		type2 = FIR;
		delivery = ENERGY;
		rules = SPELL;
		statEffect = 1;
		name = "uses Exofri!";
		DESC = "raises a single ally's physical attack.";
		break;
	}
	//case(13):   DEFENSE UP
	//case(14):   M. ATTACK UP
	//case(15):   M. DEFENSE UP
	case(16):
	{
		TAG = "Heavy Slam";
		mult = 1;
		amount = 3;
		MPcost = 0;
		STAMcost = 25;
		victim = SINGLE;
		magic = false;
		ATK = true;
		support = false;
		accuracy = 70;
		type1 = FRC;
		type2 = FRC;
		delivery = MELEE;
		rules = WEAPON_USE;
		name = " charged into the target!";
		DESC = "deals a lot of force damage to one target, if it hits.";
		break;
	}
	//DEFENSE-UP, SPEED-UP, and all the "DOWN" spells should be here, for categorizing.
	//Stat-healing spells are here. Most include a STAM recovery along with them.
	//Revival spell

	//-US level spells here, followed by ALL target spells, first level

	//-OTH level spells here, followed by ALL target spells, second level
	//...
	case (998):
	{
		TAG = "EnemDefend";
		mult = 1;
		amount = -1;
		MPcost = 0;
		STAMcost = 0;
		victim = SINGLE;
		magic = false;
		ATK = false;
		support = false;
		accuracy = -1;
		type1 = SLH;
		type2 = SLH;
		delivery = MELEE;
		name = "defends!";
		DESC = "means that this is for enemies to defend.";
		break;
	}

	case(999):
	{
		TAG = "EnemReact";
		mult = 1;
		amount = -1;
		MPcost = 0;
		STAMcost = 0;
		victim = SINGLE;
		magic = false;
		ATK = true;
		support = false;
		accuracy = -1;
		type1 = SLH;
		type2 = SLH;
		delivery = MELEE;
		name = "vomits on the floor!";
		DESC = "means that this is for enemies to use reactions.";
		break;
	}
	}
	//Every attack will have a case here until I think up a more elegant solution
}

void attack::describe()
{
	cout << this->TAG << " " << this->DESC << "\n\n";
}

void attack::printOut()
{
	string ELEM; string TARGET; string METHOD;
	switch (this->type1) //Icons for element
	{
	default:
		ELEM = "---";
		break;
	case 0:
		ELEM = "]=>";
		break;
	case 1:
		ELEM = "=O3";
		break;
	case 2:
		ELEM = "\\^/";
		break;
	case 3:
		ELEM = "[']";
		break;
	case 4:
		ELEM = "}#{";
		break;
	case 5:
		ELEM = "~&~";
		break;
	case 6:
		ELEM = "cC(";
		break;
	case 7:
		ELEM = "-<3";
		break;
	case 8:
		ELEM = "X_X";
		break;
	case 9:
		ELEM = "(@)";
		break;
	}
	switch (this->victim) //Icons for Target
	{
	default:
		TARGET = " 0 ";
		break;
	case 0:
		TARGET = " 0 ";
		break;
	case 1:
		TARGET = "<0>";
		break;
	case 2:
		TARGET = "*0*";
		break;
	case 3:
		TARGET = "*?*";
		break;
	case 4:
		TARGET = ">O<";
		break;
	case 5:
		TARGET = " O ";
		break;
	}
	switch (this->delivery)
	{
	default:
		METHOD = "O> 0";
		break;
	case 0:
		METHOD = "O> 0";
		break;
	case 1:
		METHOD = "=o 0";
		break;
	case 2:
		METHOD = "~$ 0";
		break;
	case 3:
		METHOD = "-> 0";
		break;
	}
	cout << this->TAG << "   " << this->MPcost << "   " << ELEM << "   " << TARGET << "   " << METHOD << "\n";
}


/*  This is the Reaction section of this file. Should it get too big or unweildy, it will be transferred to its own file.  */
reaction::reaction()
{
	TAG = "ERROR";
	TarNum = -1;
	victim = SINGLE;
	effect = -1;
	activate = CLOSE;
	name = " dances around like a pudding!";
}


reaction::reaction(int reacNum)
{
	switch (reacNum)
	{
	default:
		break;
	case(0):
	{
		TAG = "Bodyguard";
		victim = FRIEND;
		activate = SIN_ATTACK;
		effect = 1;
		mult = 3;
		name = " jumps in the way!";
		DESC = " defends one ally against an attack.";
		break;
	}
	case(1):
	{
		TAG = "Counter";
		victim = SELF;
		activate = CLOSE;
		effect = 0;
		mult = 3;
		Skill = attack(0);
		name = " struck first!";
		DESC = " allows you to strike back against a close opponent.";
		break;
	}
	case(2):
	{
		TAG = "Delay";
		victim = SINGLE;
		activate = TURNUP;
		effect = 0;
		mult = 1;
		Skill = attack(0);
		name = " struck first!";
		DESC = " allows you to attack during an opponent's turn, interrupting attacks.";
		break;
	}
	//SUPPORT: If friend uses a support move, triggers a special move!
	//Quick Item: Uses an item on a preselected target when the target is attacked.
	//INTERCEPT: Shoves a foe to a different target, provided they're only attacking one person
	//REFLECT: Like defend, but with different properties. Injures opponent slightly in melee,
	//         reflects a projectile attack, and both you and protectee get hurt with energy. [ANDREW SKILL]
	//BULLET COUNTER: Shoots down enemies, interrupting attacks or cancelling projectiles. [JASPER SKILL]
	//ABSORB: Negates energy attacks and restores the caster's health. Costs MP. [CHLOE SKILL]
	}
}

void reaction::describe()
{
	cout << this->TAG << this->DESC << "\n\n";
}

//Loads a preset moveset from the list of attacks for a battle entity's creation
void SetMove(int NUM, attack loadMe[10], reaction loadMeToo[8])
{
	switch (NUM)
	{
	default:
		break;
	case 0: //Eric\a beta
	{
		loadMe[0] = attack(11); //Scan
		loadMe[1] = attack(1); //Triple Slash
		loadMe[2] = attack(9); //Sonic Blade
		loadMe[3] = attack(10); //Sonic Shout

		loadMeToo[0] = reaction(0); //Bodyguard
		loadMeToo[1] = reaction(1); //Counter 
		loadMeToo[2] = reaction(2); //Delay strike
		break;
	}
	case 1: //Chloe beta 
	{
		loadMe[0] = attack(3); //Lume
		loadMe[1] = attack(4); //Xeo
		loadMe[2] = attack(7); //Haya
		loadMe[3] = attack(12); //Exofri

		loadMeToo[0] = reaction(0); //Bodyguard
		loadMeToo[1] = reaction(1); //Counter (may change to interrupt)
		break;
	}
	case 2: //Squirrel beta
	{
		loadMe[0] = attack(1); //Triple Slash
		break;
	}
	case 3: //Songbird beta
	{
		loadMe[0] = attack(6); //Vento
		loadMe[1] = attack(12); //Exofri
		loadMe[2] = attack(7); //Haya
		break;
	}
	case 4: //Rabbit beta
	{
		loadMe[0] = attack(999); //Use Reaction
		loadMe[2] = attack(998); //Use Defend
		loadMe[4] = attack(9);   //Plaga
		loadMe[7] = attack(12);  //Heavy Slam

		loadMeToo[0] = reaction(0); //Bodyguard
		break;
	}
	}
}

