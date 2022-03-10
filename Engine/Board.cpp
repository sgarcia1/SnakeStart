#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx)
{
}

Board::~Board(){}


void Board::drawCenter(int x, int y)
{
	// so the max width and height in pixels is the screen width and height divided by the dimension of cells
	//so the middle base on inputed pixels, is inpusted /2 but keep in mind as a result of the width and height of board so  
	// something like (here) x/dim -  (dim/width) **check this****

	WOffset = x - GridWCntr;
	HOffset = y - GridHCntr;

}

void Board::drawBorder(const Location& loc, Color c, float xaddOffset, float yaddOffset, float wdimCut, float hdimCut)
{
	//for (int i = 0; i < width+2; i++) {
	//	for (int j = 0; j < height+2; j++) {
	//		//Location loc = { i,j };
	//		//Color c(1, 0, 54);//(clrDist(rng), clrDist(rng), clrDist(rng));
	//		//brd.DrawCell(loc, c);
	xaddOffset = dim * xaddOffset;
	yaddOffset = dim * yaddOffset;

	///i want to add additional offest and change the dim based on input
			gfx.DrawRectDim((loc.x * dim) + WOffset + xaddOffset, (loc.y * dim) + HOffset + yaddOffset, dim*wdimCut, dim*hdimCut, c);
	//	}
	//}
}

void Board::DrawCell(const Location& loc, Color c){
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	//here for padding
	drawCenter(400, 300);
	gfx.DrawRectDim((loc.x * dim)+WOffset, (loc.y * dim)+HOffset, dim-padding, dim-padding, c);
}

bool Board::IsInBoard(const Location& loc) const
{
	return loc.x >= 0 && loc.x < width && loc.y < height && loc.y >= 0;
}

int Board::getWidth() const
{
	return width;
}

int Board::getHeight() const
{
	return height;
}


