/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"
#include <chrono>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	brd(gfx),
	rng(std::random_device()()),
    snake({ 2,2}),
	target(rng, brd, snake),
	obstacle(rng,brd,snake,target)
	
{
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
	//is this message here?
}

void Game::UpdateModel()
{
	HandleMovement();
}

void Game::standardKeyIn()
{
	if (delta_loc.y != 1) {
		if (wnd.kbd.KeyIsPressed(VK_UP) && keyBeingPressed == false) {
			keyBeingPressed = true;
		//	if (keyBeingPressed == true) {
				delta_loc = { 0,-1 };
		//	}
		}
	//	keyBeingPressed = false;
	}
	if (delta_loc.y != -1) {
		if (wnd.kbd.KeyIsPressed(VK_DOWN) && keyBeingPressed == false) {
			keyBeingPressed = true;
			delta_loc = { 0,1 };
		}
	//	keyBeingPressed = false;
	}
	//const bool UpOrDown = wnd.kbd.KeyIsPressed(VK_UP) && wnd.kbd.KeyIsPressed(VK_DOWN);

	if (delta_loc.x != 1) {
		if (wnd.kbd.KeyIsPressed(VK_LEFT) && keyBeingPressed == false) {
			keyBeingPressed = true;
			delta_loc = { -1,0 };
		}
	//	keyBeingPressed = false;
	}
	if (delta_loc.x != -1) {
		if (wnd.kbd.KeyIsPressed(VK_RIGHT) && keyBeingPressed == false) {
			keyBeingPressed = true;
		//	if (keyBeingPressed == true) {
				delta_loc = { 1,0 };
		//	}
		}
	//	keyBeingPressed = false;
	}
}

bool Game::multipleKeyIn()
{

	const bool leftAnd = wnd.kbd.KeyIsPressed(VK_LEFT) && (wnd.kbd.KeyIsPressed(VK_UP) || wnd.kbd.KeyIsPressed(VK_DOWN));
	const bool rightAnd = wnd.kbd.KeyIsPressed(VK_RIGHT) && (wnd.kbd.KeyIsPressed(VK_UP) || wnd.kbd.KeyIsPressed(VK_DOWN));
	const bool lAndr = wnd.kbd.KeyIsPressed(VK_LEFT) && wnd.kbd.KeyIsPressed(VK_RIGHT);
	const bool UandD = wnd.kbd.KeyIsPressed(VK_UP) && wnd.kbd.KeyIsPressed(VK_DOWN);
	
	/*if (delta_loc.x == 1) {
		if (wnd.kbd.KeyIsPressed(VK_UP))
		{
			auto start = std::chrono::high_resolution_clock::now();
			if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
				auto end = std::chrono::high_resolution_clock::now();
				std::chrono::duration<float> duration = end - start;
				if (duration.count() < 0.0008) {
					return true;
				}
			}
		}
	}*/

	return leftAnd || rightAnd || lAndr || UandD;
}



void Game::HandleMovement()
{
	//keyBeingPressed = false;
	if (!gameOver) {
		//const bool notLeftOrRight = !wnd.kbd.KeyIsPressed(VK_LEFT) && !wnd.kbd.KeyIsPressed(VK_RIGHT);
		if (!multipleKeyIn()) {
				standardKeyIn();
				
				
			
		}

		++obsSpwnCntr;

		if (obsSpwnCntr >= obstacleSpawnPeriod) {
			obsSpwnCntr = 0;
			obstacle.Spawn(rng, brd, snake, target);
		}


		++snakeMvCntr; 

		if (snakeMvCntr >= snakeMovePeriod-cntrIncr) {
			snakeMvCntr = 0;
			const Location nxt = snake.GetNextHeadLocation(delta_loc);
			keyBeingPressed = false;
			if (snake.IsInTileExceptEnd(nxt) == true || brd.IsInBoard(nxt) == false || obstacle.IsInTile(nxt)==true) {
				gameOver = true;
			}
			else {
				const bool eaten = nxt == target.GetLocation();
				if (eaten) {
					snake.Grow(rng);
					cntrIncr += 0.25;
				}
				snake.moveBy(delta_loc);
				if (eaten)
				{
					target.Respawn(rng,brd,snake,obstacle.IsInTile(target.PotenGetLocation()));
				}
				if (!eaten && obstacle.IsInTile(target.PotenGetLocation())) {
					target.Respawn(rng, brd, snake, obstacle.IsInTile(target.PotenGetLocation()));
				}
			}
		}
	}
}

void Game::ComposeFrame()
{
	//std::uniform_int_distribution<int> clrDist(0, 255);
	for (int i = 0; i < brd.getWidth(); i++) {
		for (int j = 0; j < brd.getHeight(); j++) {
			Location loc = { i,j };
			Color c(0, 0, 0);//Color c(1, 0, 54);//(clrDist(rng), clrDist(rng), clrDist(rng));
			brd.DrawCell(loc, c);
		}
	}
	const int tempW = brd.getWidth();
	const int tempH = brd.getHeight();
	
	for (int i = 0; i <= tempW ; i++) {
		for (int j = 0; j < tempH ; j++) {
			Location loc = { i,j };
			Color c(77, 87, 101);//(clrDist(rng), clrDist(rng), clrDist(rng));
			if (loc.y == 0) {
				Location tempLoc = loc;
				tempLoc.Add({ 0,-1 });
				brd.drawBorder(tempLoc, c, -0.5,0.54,1,0.5);
			}
			if (loc.x == 0)
			{
				Location tempLoc = loc;
				tempLoc.Add({ -1,0 });
				brd.drawBorder(tempLoc, c, 0.5, 0, 0.5, 1);
			}
			 if (loc.x == tempW-1)
			{
				 
				 Location tempLoc = loc;
				 tempLoc.Add({ 1,0 });
				brd.drawBorder(tempLoc, c, 0, 0, 0.5, 1);
			}
			if (loc.y == tempH-1)
			{
				Location tempLoc2 = loc;
				tempLoc2.Add({ 0,1 });
				brd.drawBorder(tempLoc2, c, -0.5, 0, 1, 0.5);
			}
		}
	}
	snake.DrawSnake(brd);
	target.DrawTarget(brd);
	obstacle.DrawObstacle(brd);
	if (gameOver)
	{
		SpriteCodex::DrawGameOver(350, 250, gfx);
	}
}
