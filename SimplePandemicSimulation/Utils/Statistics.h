#pragma once

struct Statistics
{
	void Infect() { Healthy--; Infected++; }
	void Heal() { Infected--; Cured++; }
	void Immunize() { Healthy--; Immune++; }

	int Healthy = 0;
	int Infected = 0;
	int Cured = 0;
	int Immune = 0;

	int Humans = 0;
};