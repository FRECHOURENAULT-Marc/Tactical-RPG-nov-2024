#include "Character.h"
#include "Spectre.h"
#include "Golem.h"
#include "Faucheur.h"
#include "Grid.h"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <conio.h>
#include <Windows.h>

using namespace std;

#define SIZE_OF_AREA 11
#define REWARD_NULL 0
#define PATH -2
#define PLAYER -1
#define MONSTER_GOLEM 1
#define MONSTER_SPECTRE 2
#define MONSTER_FAUCHEUR 3

Character::Character(int hp, int atk, int line, int column)
{
	mMaxHP = hp;
	mHP = mMaxHP;
	mATK = atk;
	mLine = line;
	mColumn = column;
	mAlive = true;
	mReward = REWARD_NULL;
}

void Character::TakeDamage(int atk)	//Inflige dégâts
{
	mHP = mHP - atk;
	cout << "PLAYER : -" << atk << " HP" << endl;
}

int Character::ReturnCharacterLine()
{
	return mLine;
}

int Character::ReturnCharacterColumn()
{
	return mColumn;
}

int Character::ReturnATK()
{
	return mATK;
}

int Character::ReturnHP()
{
	return mHP;
}

void Character::ShowStats()
{
	cout << "#---------PLAYER---------#" << endl;
	cout << "|* " << mHP << "/" << mMaxHP << " HP *|" << endl;
	cout << "|* " << mATK << " ATK *|" << endl;
	cout << "#------------------------#" << endl;
}

bool Character::IsDeadAndResetCase(Grid* pGrid)	//Vérif si mort met le membre en false (et reset la case pour monstre)
{
	if (mHP <= 0)
	{
		cout << "PLAYER vaincu !" << "Entrer pour continuer." << endl;
		char tmp = _getch();
		mAlive = false;
		return true;
	}
	else
		return false;
}

bool Character::IsDead()	//Vérif si vie<0
{
	if (mHP <= 0)
	{
		cout << "PERDU !" << endl;
		cout << "Relancement d'une partie...";
		Sleep(3000);
		system("cls");
		return true;
	}
	else
		return false;
}

void Character::SetCharacterPos(Grid* pGrid)
{
	pGrid->SetGridPos(mLine,mColumn,-1);
}

void Character::SetPathPos(Grid* pGrid, int line, int column)
{
	pGrid->SetGridPos(line, column, -2);
}

void Character::Movement(Grid* pGrid)
{
	int range[24][2]
	{
		{1,0},
		{2,0},
		{3,0},
		{-1,0},
		{-2,0},
		{-3,0},
		{0,1},
		{0,2},
		{0,3},
		{0,-1},
		{0,-2},	//index 10
		{0,-3},
		{1,1},
		{2,1},
		{1,2},
		{-1,-1},
		{-2,-1},
		{-1,-2},
		{-1,1},
		{-2,1},
		{-1,2},	//index 20
		{1,-1},
		{2,-1},
		{1,-2},	//index 23
	};

	for (int i = 0; i < 24; i++)
	{
		if (pGrid->InGrid(mLine + range[i][0], mColumn + range[i][1]) == true && pGrid->GetType(mLine + range[i][0], mColumn + range[i][1]) == 0)		//Vérif cases existent
			pGrid->SetGridPos(mLine + range[i][0], mColumn + range[i][1], -2);
	}

	while (true)
	{
		cout << "Appuyer sur Z Q S D pour vous deplacer." << endl;
		cout << "A pour valider le deplacement.";
		char key;
		key = _getch();
		if (key == 's')
		{
			if (pGrid->InGrid(mLine + 1, mColumn) == true && pGrid->GetType(mLine + 1, mColumn) == -2)
			{
				pGrid->SetGridPos(mLine, mColumn, -2);
				mLine++;
				SetCharacterPos(pGrid);
			}
		}
		if (key == 'z')
		{
			if (pGrid->InGrid(mLine - 1, mColumn) == true && pGrid->GetType(mLine - 1, mColumn) == -2)
			{
				pGrid->SetGridPos(mLine, mColumn, -2);
				mLine--;
				SetCharacterPos(pGrid);
			}

		}
		if (key == 'd')
		{
			if (pGrid->InGrid(mLine, mColumn + 1) == true && pGrid->GetType(mLine, mColumn + 1) == -2)
			{
				pGrid->SetGridPos(mLine, mColumn, -2);
				mColumn++;
				SetCharacterPos(pGrid);
			}

		}
		if (key == 'q')
		{
			if (pGrid->InGrid(mLine, mColumn - 1) == true && pGrid->GetType(mLine, mColumn - 1) == -2)
			{
				pGrid->SetGridPos(mLine, mColumn, -2);
				mColumn--;
				SetCharacterPos(pGrid);
			}
		}
		if (key == 'a')
		{
			break;
		}
		
		pGrid->ShowGrid();
	}

	pGrid->ResetPath();

}

void Character::KillReward(Grid* pGrid, int type)	//Attribut les récompenses lors des kills
{
	if (type == 1)
		mATK = mATK + 1;
	if (type == 2)
	{
		mMaxHP++;
		mHP = mMaxHP;
	}
}

bool Character::GoAway(Grid* pGrid, Character* player)	//Fait fuire les spectre (spectre.cpp)
{
	return false;
}
void Character::GoToYou(Grid* pGrid, Character* player)	//Fait venir les faucheurs (faucheur.cpp)
{
	return;
}