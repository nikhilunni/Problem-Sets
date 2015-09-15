#include "maze.h"
#include "png.h"
#include <stdlib.h>
#include <vector>
#include <utility>
#include <iostream>

using namespace std;

SquareMaze::SquareMaze()
{
	//????
}

SquareMaze::~SquareMaze()
{
	for(int i = 0; i < w; i++)
		delete[] maze[i];
	delete[] maze;
}
void SquareMaze::makeMaze(int width, int height)
{
	srand(time(NULL));
	maze = new pair<bool,bool> * [width];
	for(int i = 0; i < width; i++)
	{
		maze[i] = new pair<bool,bool> [height];
		for(int j = 0; j < height; j++)
			maze[i][j] = make_pair(true,true);
	}
	w = width, h = height;
	int numTiles = w*h;
	walls.addelements(numTiles);
	while(walls.size(0) < numTiles) //Keep going until all tiles are part of the same set/tree. Also, size() runs find(), so tree is organized all the while.
	{
		//I considered iterating through width x height and removng right/bottom randomly, but this seems less structured and I think will lead to more interesting mazes.
		//Although longer convergence time....
		int randX = rand() % w, randY = rand() % h;
		int side = rand() % 2;
		if(side == 0) //Right wall
		{
			int current = w*randY + randX;
			int next = current+1;
			if(randX < w-1 && walls.find(current) != walls.find(next))
			{
				maze[randX][randY].first = false;
				walls.setunion(current,next);
			}
		}
		else //Bottom wall
		{
			int current = w*randY + randX;
			int next = current + w;
			if(randY < h-1 && walls.find(current) != walls.find(next))
			{
				maze[randX][randY].second = false;
				walls.setunion(current,next);
			}
		}
		//If picked a bad tile, don't pick other wall type by default -- move on
	}
}

bool SquareMaze::canTravel(int x, int y, int dir) const
{
	switch(dir) 
	{
		case 0:
			return (x+1 < w ? !maze[x][y].first : false);
		case 1:
			return (y+1 < h ? !maze[x][y].second : false);
		case 2:
			return (x-1 >= 0 ? !maze[x-1][y].first : false);
		case 3:
			return (y-1 >= 0 ? !maze[x][y-1].second : false);
	}
	return false; //Bad dir
}

void SquareMaze::setWall(int x, int y, int dir, bool exists)
{
	if(dir == 0)
		maze[x][y].first = exists;
	if(dir == 1)
		maze[x][y].second = exists;
}

vector<int> SquareMaze::solveMaze()
{
	//A property of the DisjointSets is that it is possible to get from one tile to every other tile
	vector< vector<int> > solutions;
	vector<int> pathSoFar;
	pathSoFar.push_back(1);
	
	solveMaze_helper(0,0,pathSoFar,solutions);
	
	int largestSize = solutions[0].size();
	for(int i = 0; i < solutions.size(); i++)
	{
		if(solutions[i].size() > largestSize)
			largestSize = solutions[i].size();
	}

	vector<int> winners;
	for(int i = 0; i < solutions.size(); i++) // In case of multiple largest sizes, we must pick the lowest x value
	{
		if(solutions[i].size() == largestSize)
			winners.push_back(i);
	}
	int lowestX = 0;
	for(int i = 0; i < winners.size(); i++)
	{
		pair<int,int> loc = finalLocation(0,0,solutions[winners[i]]);
		if(loc.first < finalLocation(0,0,solutions[winners[lowestX]]).first)
			lowestX = i;
	}

	vector<int> out = solutions[winners[lowestX]];
	out.erase(out.begin());	
	return out;
}

int SquareMaze::solveMaze_helper(int x, int y, vector<int> pathSoFar, vector< vector<int> > & solutions)
{
	if(y == h-1)
	{
		solutions.push_back(pathSoFar);
	}
	if(solutions.size() < w) //If we haven't hit all of the bottom row yet
	{
		int variousPaths[4];
		if(canTravel(x,y,0) && pathSoFar.back() != 2) //If we can move right and we didn't just go left
		{
			vector<int> updatedPath = pathSoFar;
			updatedPath.push_back(0);
			variousPaths[0] = solveMaze_helper(x+1,y,updatedPath,solutions);
		}
		if(canTravel(x,y,1) && pathSoFar.back() != 3) 
		{
			vector<int> updatedPath = pathSoFar;
			updatedPath.push_back(1);
			variousPaths[1] = solveMaze_helper(x,y+1,updatedPath,solutions);
		}
		if(canTravel(x,y,2) && pathSoFar.back() != 0)
		{
			vector<int> updatedPath = pathSoFar;
			updatedPath.push_back(2);
			variousPaths[2] = solveMaze_helper(x-1,y,updatedPath,solutions);
		}
		if(canTravel(x,y,3) && pathSoFar.back() != 1)
		{
			vector<int> updatedPath = pathSoFar;
			updatedPath.push_back(3);
			variousPaths[3] = solveMaze_helper(x,y-1,updatedPath,solutions);
		}
		for(int i = 0; i <= 3; i++)
		{
			if(variousPaths[i] > 0);
				return variousPaths[i];
		}
		return -1; //Failure!
	}
	else //Success! 
	{
		return 0;	
	}
}

pair<int,int> SquareMaze::finalLocation(int x, int y, vector<int> path)
{
	int finalX = x;
	int finalY = y;
	for(int i = 0; i < path.size(); i++)
	{
		switch(path[i]) 
		{
			case 0:
				finalX++; break;
			case 1:
				finalY++; break;
			case 2:
				finalX--; break;
			case 3:
				finalY--; break;
		}
	}
	pair<int,int> out = make_pair(finalX,finalY);
	return out;
}

PNG* SquareMaze::drawMaze() const
{
	PNG * out = new PNG(w*10+1,h*10+1);
	RGBAPixel BLACK(0,0,0);
	int i = 0, j = 0, k = 0;
	for(i = 10; i <= w*10; i++)
		*(*out)(i,0) = BLACK;
	for(j = 0; j <= h*10; j++)
		*(*out)(0,j) = BLACK;

	for(i = 0; i < w; i++)
	{
		for(j = 0; j < h; j++)
		{
			if(maze[i][j].first) //If right wall
			{
				for(k = 0; k <= 10; k++)
					*(*out)( (i+1)*10 , j*10+k ) = BLACK;
			}
			if(maze[i][j].second) //If bottom wall
			{
				for(k = 0; k <= 10; k++)
					*(*out)( i*10+k , (j+1)*10 ) = BLACK;
			}
		}
	}
	return out;
}

PNG* SquareMaze::drawMazeWithSolution()
{
	PNG * out = drawMaze();
	vector<int> path = solveMaze();
	RGBAPixel RED(255,0,0);
	RGBAPixel WHITE(255,255,255);
	int x = 5, y = 5;
	int i = 0;
	for(int j = 0; j < path.size(); j++)
	{
		switch(path[j])
		{
			case 0:
				for(i = 0; i <= 10; i++)
					*(*out)(x+i,y) = RED;
				x += 10;
				break;
			case 1:
				for(i = 0; i <= 10; i++)
					*(*out)(x,y+i) = RED;
				y += 10;
				break;
			case 2:
				for(i = 0; i <= 10; i++)
					*(*out)(x-i,y) = RED;
				x -= 10;
				break;
			case 3:
				for(i = 0; i <= 10; i++)
					*(*out)(x,y-i) = RED;
				y -= 10;
				break;
		}
	}
	pair<int,int> finalLoc = finalLocation(0,0,path); 
	for(int k = 1; k <= 9; k++)
		*(*out)(finalLoc.first*10 + k, (finalLoc.second+1)*10) = WHITE;
	
	return out;
}

