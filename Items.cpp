#include "stdafx.h"
#include "Structs.h"
#include <iostream>

using namespace std;
//Includes weapons and items

weapon::weapon()
{
	ATKpow = 0;
	Weight = 0;
	name = "ERROR";
	elem1 = ELD;
	USER = -1;
}

weapon::weapon(int select)
{
	switch (select)
	{
	default:
		break;
	case(0):
	{
		name = "Pointy Stick";
		ATKpow = 5;
		Weight = 3;
		elem1 = SLH;
		elem2 = SLH;
		strike = MELEE;
		USER = 0;
		break;
	}
	case(1):
	{
		name = "Beaten-up Bear";
		ATKpow = 3;
		Weight = 0;
		elem1 = FRC;
		elem2 = FRC;
		strike = PROJECTILE;
		USER = 1;
		break;
	}
	case(2):
	{
		name = "Enemy Slash";
		ATKpow = 0;
		Weight = 3;
		elem1 = SLH;
		elem2 = SLH;
		strike = MELEE;
		USER = 6;
		break;
	}
	case(3):
	{
		name = "Enemy Bash";
		ATKpow = 0;
		Weight = 3;
		elem1 = FRC;
		elem2 = FRC;
		strike = MELEE;
		USER = 6;
		break;
	}
	}
}

item::item()
{
	name = "ERROR";
	maxAmount = 0;
	currAmount = -1;
	effect = -1;
}

item::item(int select)
{
	switch (select)
	{
	default:
		break;
	case(0):
	{
		name = "Band-aid"; //Reclassify later to cure BLEED
		ID = 0;
		maxAmount = 10;
		UseEffort = 10;
		effect = 0;
		potency = 20;
		buddy = true;
		elem = LIF;
		usage = MELEE;
		DESC = "cover wounds, restoring 20 points of HP to one person.";
		break;
	}
	case(1):
	{
		name = "Scented candle";
		ID = 1;
		maxAmount = 10;
		UseEffort = 10;
		effect = 1;
		potency = 10;
		buddy = true;
		elem = WND;
		usage = ENERGY;
		DESC = "relax the body, restoring 10 points of MP to one person.";
		break;
	}
	case(2):
	{
		name = "Energy drink";
		ID = 2;
		maxAmount = 10;
		UseEffort = 10;
		effect = 2;
		potency = 30;
		buddy = true;
		elem = FIR;
		usage = MELEE;
		DESC = "give you more energy, restoring 30 points of STAM to one person.";
		break;
	}
	case(3):
	{
		name = "Cherry Bomb";
		ID = 3;
		maxAmount = 10;
		UseEffort = 5;
		effect = 0;
		potency = 20;
		buddy = false;
		elem = FIR;
		usage = PROJECTILE;
		DESC = "explode on impact, dealing low fire damage to a single enemy.";
		break;
	}
	case(4):
	{
		name = "Smelling Salts";
		ID = 4;
		maxAmount = 5;
		UseEffort = 10;
		effect = 3;
		potency = 34;
		buddy = true;
		elem = WND;
		usage = MELEE;
		DESC = "wake up a sleeping friend, reviving them from being KOed.";
		break;
	}
	case(5):
	{/*
		name = ???;
		ID = 5;
		maxAmount = ???;
		UseEffort = ???;
		effect = ?;  HP, MP, STAM, Revive?
		potency = ???;
		buddy = true? Enemy or friend?;
		elem = something;
		usage = Whatever makes sense;
		DESC = "does whatever I want it to.";*/
		break;
	}
	}
}

void item::describe()
{
	cout << this->name << "s " << this->DESC << "\n\n";
}


void cleanup()
{
	system("CLS");
}
