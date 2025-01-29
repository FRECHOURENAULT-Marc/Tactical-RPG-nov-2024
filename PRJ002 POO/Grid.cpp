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

Grid::Grid()
{
	ppGrid = (Case**) malloc(sizeof(Case*) * SIZE_OF_AREA);
	for (int line = 0; line < SIZE_OF_AREA; line++)
	{	
		
		ppGrid[line] = (Case*) malloc(sizeof(Case) * SIZE_OF_AREA);
		for (int column = 0; column < SIZE_OF_AREA; column++)
		{
			ppGrid[line][column].mLine = line;
			ppGrid[line][column].mColumn = column;
			ppGrid[line][column].mState = 0;
		}
	}
}

void Grid::ShowGrid()
{
	system("cls");
	cout << "+ - + - + - + - + - + - + - + - + - + - + - +" << endl;
	for (int line = 0; line < SIZE_OF_AREA; line++)
	{
		for (int column = 0; column < SIZE_OF_AREA; column++)
		{
			cout << "|";
			if (ppGrid[line][column].mState == -2)
				cout << " * ";
			if (ppGrid[line][column].mState == -1)
				cout << " @ ";
			if (ppGrid[line][column].mState == 0)
				cout << "   ";
			if (ppGrid[line][column].mState == 1)
				cout << " G ";
			if (ppGrid[line][column].mState == 2)
				cout << " S ";
			if (ppGrid[line][column].mState == 3)
				cout << " F ";
		}
		cout << "|" << endl;
		cout << "+ - + - + - + - + - + - + - + - + - + - + - +" << endl;
	}
}

bool Grid::InGrid(int line, int column)
{
	if (line < 0 || line > SIZE_OF_AREA - 1 || column < 0 || column > SIZE_OF_AREA - 1)
	{
		return false;
	}
	else
		return true;
}

void Grid::SetGridPos(int line, int column, int type)
{
	ppGrid[line][column].mState = type;
}

void Grid::ResetGridPos(int line, int column)
{
	ppGrid[line][column].mState = 0;
}

void Grid::ResetPath()
{
	for (int line = 0; line < SIZE_OF_AREA; line++)
	{
		for (int column = 0; column < SIZE_OF_AREA; column++)
		{
			if (ppGrid[line][column].mState == -2)
			{
				ppGrid[line][column].mState = 0;
			}
		}
	}
}

int Grid::IsMonsterAround(int line, int column)	//Retourn le type du premier monstre détécté autour
{
	int direction[4][2]
	{
		{0,1},
		{-1,0},
		{1,0},
		{0,-1},
	};

	for (int i = 0; i < 4; i++)
	{
		int nLine = line + direction[i][0];
		int nColumn = column + direction[i][1];
		if (InGrid(nLine, nColumn) == true && ppGrid[nLine][nColumn].mState != 0)
		{
			return ppGrid[nLine][nColumn].mState;
		}
	}
	return 0;
}

int Grid::GetType(int line, int column)
{
	return ppGrid[line][column].mState;
}

int Grid::IsPlayerAround(int line, int column)	//Vérif si joueur est autour et retourne le type joueur (-1)
{
	int direction[4][2]
	{
		{0,1},
		{-1,0},
		{1,0},
		{0,-1},
	};

	for (int i = 0; i < 4; i++)
	{
		int nLine = line + direction[i][0];
		int nColumn = column + direction[i][1];
		if (InGrid(nLine, nColumn) == true && ppGrid[nLine][nColumn].mState == -1)
		{
			return ppGrid[nLine][nColumn].mState;
		}
	}
	return false;
}

bool Grid::IsVictory()	//Vérif si victoire (plus d'ennemis) affiche message et retourne bool
{
	int caseCount = 0;
	for (int line = 0; line < SIZE_OF_AREA; line++)
	{
		for (int column = 0; column < SIZE_OF_AREA; column++)
		{
			if (ppGrid[line][column].mState == 3)
				caseCount++;
		}
	}
	if (caseCount == 0)
	{
		cout << "VICTOIRE !";
		Sleep(3000);
		return true;
	}
	return false;
}

int Grid::ReturnGoAwayLine(int spectreLine, int spectreColumn, int playerLine)
{
	if (spectreLine < SIZE_OF_AREA - 1 && spectreLine > playerLine && ppGrid[spectreLine + 1][spectreColumn].mState == 0)
		return 1;
	if (spectreLine > 0 && spectreLine < playerLine && ppGrid[spectreLine - 1][spectreColumn].mState == 0)
		return -1;
	else
		return 0;
}
int Grid::ReturnGoAwayColumn(int spectreLine, int spectreColumn, int playerColumn)
{
	if (spectreColumn < SIZE_OF_AREA - 1 && spectreColumn > playerColumn && ppGrid[spectreLine][spectreColumn + 1].mState == 0)
		return 1;
	if (spectreColumn > 0 && spectreColumn < playerColumn && ppGrid[spectreLine][spectreColumn - 1].mState == 0)
		return -1;
	else
		return 0;
}

int Grid::ReturnGoToYouLine(int faucheurLine, int faucheurColumn, int playerLine)
{
	if (faucheurLine > 0 && faucheurLine > playerLine && ppGrid[faucheurLine - 1][faucheurColumn].mState == 0)
		return -1;
	if (faucheurLine < SIZE_OF_AREA - 1 && faucheurLine < playerLine && ppGrid[faucheurLine + 1][faucheurColumn].mState == 0)
		return 1;
	else
		return 0;
}
int Grid::ReturnGoToYouColumn(int faucheurLine, int faucheurColumn, int playerColumn)
{
	if (faucheurColumn > 0 && faucheurColumn > playerColumn && ppGrid[faucheurLine][faucheurColumn - 1].mState == 0)
		return - 1;
	if (faucheurColumn < SIZE_OF_AREA - 1 && faucheurColumn < playerColumn && ppGrid[faucheurLine][faucheurColumn + 1].mState == 0)
		return 1;
	else
		return 0;
}