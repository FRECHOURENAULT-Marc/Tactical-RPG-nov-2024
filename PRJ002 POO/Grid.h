#pragma once

#include "Character.h"

struct Case
{
	int mLine;
	int mColumn;
	int mState;
};

class Grid : public Case
{
protected:
	Case** ppGrid;

public:
	Grid();
	void ShowGrid();
	bool InGrid(int line, int column);
	void SetGridPos(int x, int column, int type);
	void ResetGridPos(int x, int column);
	void ResetPath();
	int IsMonsterAround(int line, int column);
	int GetType(int line, int column);
	int IsPlayerAround(int line, int column);
	bool IsVictory();
	int ReturnGoAwayLine(int spectreLine, int spectreCloumn, int playerLine);
	int ReturnGoAwayColumn(int spectreLine, int spectreCloumn, int playerCloumn);
	int ReturnGoToYouLine(int spectreLine, int spectreColumn, int playerLine);
	int ReturnGoToYouColumn(int spectreLine, int spectreColumn, int playerColumn);
};


