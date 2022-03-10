#pragma once
#include "Board.h"
#include "Snake.h"
#include <random>
#include "Target.h"

class Obstacle
{
private:
	class ObsLocs
	{
	private:
		Location obsLocs;
	public:
		Location getLocation() const;
		void setLocation(const Location& loc);
	};
	//Location loc;
	static constexpr Color c = Colors::Gray;

	static constexpr int maxObs = 100;
	ObsLocs oLocs[maxObs];
	int currLoc = 0;

public:
	Obstacle(std::mt19937& rng, const Board& brd, const Snake& snake, const Target& trgt);
	bool IsInTile(const Location& target) const;
	void Spawn(std::mt19937& rng, const Board& brd, const Snake& snake,const Target& trgt);
	void DrawObstacle(Board& board) const;
	
	const Location& GetLocation() const;
};

