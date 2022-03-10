#pragma once

#include "Board.h"
#include "Snake.h"
#include <random>
//#include "Obstacle.h"


class Target
{
private:
	Location loc;
	static constexpr Color c = Colors::Red;
	Location potLocation;
	

public:
	Target(std::mt19937& rng, const Board& brd, const Snake& snake);
	void Respawn(std::mt19937& rng, const Board& brd, const Snake& snake, bool inobst);
	void DrawTarget(Board& board) const;
	const Location& GetLocation() const;
	const Location& PotenGetLocation() const;

};

