#include "Golem.h"
#include "Grid.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

#define REWARD_NULL 0
#define GOLEM_REWARD 1
#define SPECTRE_REWARD 2
#define FAUCHEUR_REWARD 3

Golem::Golem(int hp, int atk, int line, int column, int chance) : Character(hp, atk, line, column)
{
	mChanceToBlock = chance;
	mReward = GOLEM_REWARD;
}

bool Golem::IsDeadAndResetCase(Grid* pGrid)
{
	if (mHP <= 0)
	{
		cout << "GOLEM vaincu ! Entrer pour continuer." << endl;
		char tmp = _getch();
		mAlive = false;
		pGrid->ResetGridPos(mLine, mColumn);
		return true;
	}
	else
		return false;
}

bool Golem::IsDead()
{
	if (mHP <= 0)
		return true;
	else
		return false;
}

void Golem::TakeDamage(int atk)
{
	int rdm = rand()%mChanceToBlock + 1 ;
	if (rdm == mChanceToBlock)
	{
		cout << "GOLEM : Bloquage !"<<endl;
		return;
	}
	mHP = mHP - atk;
	cout << "GOLEM : -" << atk <<" HP" << endl;
}

void Golem::ShowStats()
{
	cout << "#---------GOLEM---------#" << endl;
	cout << "|* " << mHP << "/" << mMaxHP << " HP *|" << endl;
	cout << "|* " << mATK << " ATK | BLK : 1/"<< mChanceToBlock<< " *|" << endl;
	cout << "#-----------------------#" << endl;
}

void Golem::SetCharacterPos(Grid* pGrid)
{
	pGrid->SetGridPos(mLine, mColumn, 1);
}