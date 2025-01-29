#include "Spectre.h"
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

Spectre::Spectre(int hp, int atk, int x, int y) : Character(hp, atk / 2, x, y)
{
	mReward = SPECTRE_REWARD;
}

bool Spectre::IsDeadAndResetCase(Grid* pGrid)
{
	if (mHP <= 0)
	{
		cout << "SPECTRE vaincu ! Entrer pour continuer." << endl;
		char tmp = _getch();
		mAlive = false;
		pGrid->ResetGridPos(mLine, mColumn);
		
		return true;
	}
	else
		return false;
}

bool Spectre::IsDead()
{
	if (mHP <= 0)
		return true;
	else
		return false;
}

void Spectre::TakeDamage(int atk)
{
	mHP = mHP - atk;
	cout << "SPECTRE : -" << atk << " HP" << endl;
}

void Spectre::ShowStats()
{
	cout << "#--------SPECTRE--------#" << endl;
	cout << "|* " << mHP << "/" << mMaxHP << " HP *|" << endl;
	cout << "|* " << mATK << " ATK *|" << endl;
	cout << "#-----------------------#" << endl;
}

void Spectre::SetCharacterPos(Grid* pGrid)
{
	pGrid->SetGridPos(mLine, mColumn, 2);
}

bool Spectre::GoAway(Grid* pGrid, Character* player)
{
	int nLine = mLine + pGrid->ReturnGoAwayLine(mLine, mColumn, player->ReturnCharacterLine());
	int nColumn = mColumn + pGrid->ReturnGoAwayColumn(nLine, mColumn, player->ReturnCharacterColumn());
	if (nLine == mLine && nColumn == mColumn)
		return false;
	pGrid->SetGridPos(nLine, nColumn, 2);
	pGrid->ResetGridPos(mLine, mColumn);
	mLine = nLine;
	mColumn = nColumn;
	return true;
}