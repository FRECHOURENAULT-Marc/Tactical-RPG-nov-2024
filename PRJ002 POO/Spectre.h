#pragma once

#include "Character.h"

class Spectre : public Character
{

public:
	Spectre(int hp, int atk, int x, int y);

	bool IsDeadAndResetCase(Grid* pGrid) override;
	bool IsDead() override;

	void TakeDamage(int atk) override;

	void ShowStats() override;

	void SetCharacterPos(Grid* pGrid) override;

	bool GoAway(Grid* pGrid, Character* player) override;
};

