#pragma once

#include "Character.h"

class Golem : public Character
{
protected :

	int mChanceToBlock;

public :

	Golem(int hp, int atk, int line, int column, int chance);

	bool IsDeadAndResetCase(Grid* pGrid) override;
	bool IsDead() override;

	void TakeDamage(int atk) override;

	void ShowStats() override;

	void SetCharacterPos(Grid* pGrid) override;
};

