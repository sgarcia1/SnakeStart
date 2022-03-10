#include "Target.h"

Target::Target(std::mt19937& rng, const Board& brd, const Snake& snake)
{
	
	Respawn(rng, brd, snake, false);
}

void Target::Respawn(std::mt19937& rng, const Board& brd, const Snake& snake, bool inobst)
{
	std::uniform_int_distribution<int> xDist(0, brd.getWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.getHeight()-1);
	//std::uniform_int_distribution<int> xDist(1, brd.getWidth() - 2);
	//std::uniform_int_distribution<int> yDist(1, brd.getHeight() - 2);

	Location newLoc;

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
		potLocation = newLoc;

	} while (snake.IsInTile(newLoc) || inobst );

	loc = newLoc;
}


void Target::DrawTarget(Board& board) const
{
	board.DrawCell(loc, c);
}

const Location& Target::GetLocation() const
{
	return loc;
}

const Location& Target::PotenGetLocation() const
{
	return potLocation;
}
