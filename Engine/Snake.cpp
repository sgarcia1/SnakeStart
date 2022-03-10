#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location& loc){
	segments[0].InitHead(loc);
}

void Snake::moveBy(const Location& delta_loc)
{
	for (int i = nsegs - 1; i > 0; i--) {
		segments[i].Follow(segments[i - 1]);
	}
	segments[0].MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l (segments[0].GetLocation());
	l.Add(delta_loc);
	return l; 
}

void Snake::Grow(std::mt19937& rng)
{
	if (nsegs < maxSegs) {
		if (increasing) {
			colorCntr += 50;
		}
		else {
			colorCntr -= 50;
		}

		if (colorCntr >= 180) {
			increasing = false;
		}
		if (colorCntr <= 80) {
			increasing = true;
		}
		segments[nsegs].InitBody(rng, nsegs,colorCntr);
		nsegs++;
	}
}

void Snake::DrawSnake(Board& brd) const
{
	for (int i = 0; i < nsegs; i++) {
		segments[i].DrawSeg(brd);
	}
}

bool Snake::IsInTileExceptEnd(const Location& target) const
{
	for (int i = 0; i < nsegs-1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTile(const Location& target) const
{
	for (int i = 0; i < nsegs; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

int Snake::getNsegs() const
{
	return nsegs;
}


void Snake::Segment::DrawSeg(Board& brd) const
{
	brd.DrawCell(segLoc, segC);
}

void Snake::Segment::Follow(const Segment& next)
{
	segLoc = next.segLoc;
}

void Snake::Segment::MoveBy(const Location& delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	segLoc.Add(delta_loc);
}

void Snake::Segment::InitHead(const Location loc)
{
	segLoc = loc;
	segC = Snake::headColor;
}

void Snake::Segment::InitBody(std::mt19937& rng, int numsegs, int clr)
{
	//std::uniform_int_distribution<int> rDist(0,255);
	//std::uniform_int_distribution<int> gDist(0, 255);
	//std::uniform_int_distribution<int> bDist(0, 255);
	//Color c(rDist(rng), gDist(rng), bDist(rng));
	Color c(0,clr,0);
	//segLoc = { 2,3};
	//if (numsegs == 1) {
	//	segC = bodyColor;
	//
	//}
	//else {
		
		segC = c;
	//}
	/*
	bool increasing  = true;

	colorCntr = 80;

	if(increaseing){
	   colorcntr += 50;
	}
	else{
		colorCntr -= 50;
	}

	if(colorCntr >= 180){
		increasing = false;
	}
	if(colorCntr <= 80){
		increasing = true;
	}
	*/
}

Location Snake::Segment::GetLocation() const
{
	return segLoc;
}

//int Snake::Segment::getXinit()
//{
//	return segLoc.x;
//}
