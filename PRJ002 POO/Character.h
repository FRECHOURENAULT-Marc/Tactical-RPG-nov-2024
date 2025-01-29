#pragma once

class Grid;

class Character
{
protected :
	int mMaxHP;
	int mHP;
	int mATK;
	int mReward;
	int mLine;
	int mColumn;
	bool mAlive;
public :

	Character(int hp, int atk, int line, int column);

	virtual void TakeDamage(int atk);

	int ReturnCharacterLine();
	int ReturnCharacterColumn();
	int ReturnHP();
	int ReturnATK();

	virtual void ShowStats();
	
	virtual bool IsDeadAndResetCase(Grid* pGrid);
	virtual bool IsDead();

	virtual void SetCharacterPos(Grid* pGrid);
	void SetPathPos(Grid* pGrid, int line, int column);

	void Movement(Grid* pGrid);

	void KillReward(Grid* pGrid, int type);

	virtual bool GoAway(Grid* pGrid, Character* player);
	virtual void GoToYou(Grid* pGrid, Character* player);
};

