#include "Faucheur.h"
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

Faucheur::Faucheur(int hp, int atk, int x, int y, int chance) : Character(hp, atk*2, x, y)
{
	mChanceToRegen = chance;
	mReward = FAUCHEUR_REWARD;
}

bool Faucheur::IsDeadAndResetCase(Grid* pGrid)
{
	if (mHP <= 0)
	{
		cout << "FAUCHEUR vaincu ! Entrer pour continuer." << endl;
		char tmp = _getch();
		mAlive = false;
		pGrid->ResetGridPos(mLine, mColumn);
		return true;
	}
	else
		return false;
}

bool Faucheur::IsDead()
{
	if (mHP <= 0)
		return true;
	else
		return false;
}

void Faucheur::TakeDamage(int atk)
{
	mHP = mHP - atk;
	cout << "FAUCHEUR : -" << atk << " HP" << endl;
	int rdm = rand() % mChanceToRegen + 1;
	if (rdm == mChanceToRegen)
	{
		mHP = mMaxHP;
		cout << "FAUCHEUR : Regeneration !" << endl;
	}
}

void Faucheur::ShowStats()
{
	cout << "#--------FAUCHEUR--------#" << endl;
	cout << "|* " << mHP << "/" << mMaxHP << " HP *|" << endl;
	cout << "|* " << mATK << " ATK | HL CHS 1/" << mChanceToRegen<< " *|" << endl;
	cout << "#------------------------#" << endl;
}

void Faucheur::SetCharacterPos(Grid* pGrid)
{
	pGrid->SetGridPos(mLine, mColumn, 3);
}

void Faucheur::GoToYou(Grid* pGrid, Character* player)
{
	int nLine = mLine + pGrid->ReturnGoToYouLine(mLine, mColumn, player->ReturnCharacterLine());
	int nColumn = mColumn + pGrid->ReturnGoToYouColumn(nLine, mColumn, player->ReturnCharacterColumn());
	if (nLine == mLine && nColumn == mColumn)
		return;
	pGrid->SetGridPos(nLine, nColumn, 3);
	pGrid->ResetGridPos(mLine, mColumn);
	mLine = nLine;
	mColumn = nColumn;
}
