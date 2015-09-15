#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "png.h"
#include <utility>
#include "dsets.h"

using namespace std;

class SquareMaze
{
	public:
		SquareMaze();
		~SquareMaze();
		void makeMaze(int width, int height);
		bool canTravel(int x, int y, int dir) const;
		void setWall(int x, int y, int dir, bool exists);
		vector<int> solveMaze();
		PNG* drawMaze() const;
		PNG* drawMazeWithSolution();

	private:
		pair<int,int> finalLocation(int x, int y, vector<int> path); 
		int solveMaze_helper(int x, int y, vector<int> pathSoFar, vector< vector<int> > & solutions);
		pair<bool,bool> ** maze;
		int w, h;
		DisjointSets walls;

};
#endif
