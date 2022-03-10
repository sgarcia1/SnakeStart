#pragma once

#include "Board.h"
#include <random>

class Snake {
private:
	class Segment
	{
	private:
		Location segLoc;
		Color segC;
		Color bodyColor = Color(0, 80, 0);
		int counter = 0;
		
	public:
		void DrawSeg(Board& brd) const;
		void Follow(const Segment& next);
		void MoveBy(const Location& delta_loc);
		void InitHead(const Location loc);
		void InitBody(std::mt19937& rng, int numsegs, int clr);
		Location GetLocation() const;
		//int getXinit();
		
	};
	static constexpr Color headColor = Color(192, 180, 0);
//	static constexpr Color bodyColor = Colors::Green;
	


	static constexpr int maxSegs = 100;
	Segment segments[maxSegs];
	int nsegs = 1;
	bool increasing = true;
	int colorCntr = 30;
	
	//int counter;
public:
	Snake(const Location& loc);
	void moveBy(const Location& delta_loc);
	Location GetNextHeadLocation(const Location& delta_loc) const;
	void Grow(std::mt19937& rng);
	void DrawSnake(Board& brd) const;
	bool IsInTileExceptEnd(const Location& target) const;
	bool IsInTile(const Location& target) const;
	int getNsegs() const;

};