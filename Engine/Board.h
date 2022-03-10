#pragma once

#include "Graphics.h"
#include "Location.h"


class Board
{
private:
	static constexpr int width = 48;
	static constexpr int height = 36;
	static constexpr int dim = 15;

	Graphics& gfx;

	float GridWCntr = width * (float(dim) / 2);
	float WOffset = 0;
	float GridHCntr = height * (float(dim) / 2);
	float HOffset = 0;
	float padding = 2;

public:
	Board(Graphics& gfx);
	~Board();

	void DrawCell(const Location& loc, Color c);

	bool IsInBoard(const Location& loc) const;

	int getWidth() const;
	int getHeight() const;

	void drawCenter(int x, int y);
	void drawBorder(const Location& loc, Color c, float xaddOffset, float yaddOffset, float wdimCut, float hdimCut);


};

