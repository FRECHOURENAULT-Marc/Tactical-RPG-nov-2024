#pragma once

#include "Character.h"

class Faucheur : public Character
{
protected :

	int mChanceToRegen;

public:

	Faucheur(int hp, int atk, int x, int y, int chance);

	bool IsDeadAndResetCase(Grid* pGrid) override;
	bool IsDead() override;

	void TakeDamage(int atk) override;

	void ShowStats() override;

	void SetCharacterPos(Grid* pGrid) override;
	void GoToYou(Grid* pGrid, Character* player) override;
};

