#include "Obstacle.h"

Obstacle::Obstacle(std::mt19937& rng, const Board& brd, const Snake& snake, const Target& trgt)
{
//	Spawn(rng, brd, snake,trgt);
}

void Obstacle::Spawn(std::mt19937& rng, const Board& brd, const Snake& snake,const Target& trgt)
{
	std::uniform_int_distribution<int> xDist(0, brd.getWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.getHeight() - 1);
	//std::uniform_int_distribution<int> xDist(1, brd.getWidth() - 2);
	//std::uniform_int_distribution<int> yDist(1, brd.getHeight() - 2);

	Location newLoc;

	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);

	} while (snake.IsInTile(newLoc) || trgt.GetLocation() == newLoc || IsInTile(newLoc));

	
	if (currLoc < maxObs) {
		oLocs[currLoc].setLocation(newLoc);
		currLoc++;
	}
}

bool Obstacle::IsInTile(const Location& target) const
{
	for (int i = 0; i < currLoc; i++)
	{
		if (oLocs[i].getLocation() == target)
		{
			return true;
		}
	}
	return false;
}


void Obstacle::DrawObstacle(Board& board) const
{
	for (int i = 0; i < currLoc; i++)
	{
		board.DrawCell(oLocs[i].getLocation(), c);
	}
	
}

Location Obstacle::ObsLocs::getLocation() const
{
	return obsLocs;
}

void Obstacle::ObsLocs::setLocation(const Location& loc)
{
	obsLocs = loc;
}
