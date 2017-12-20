#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "solver.h"
#include "mazehelper.h"
#include "path.h"
#include "list.h"

PathLL * solveMaze(Maze * m) {
	
	PathLL * successPaths = buildPaths();
	char * retval = malloc(((m->height * m->width) + 1) * sizeof(char));

	MazePos mp = {.xpos = m->start.xpos, .ypos = m->start.ypos};
	depthFirstSolve(m, mp, retval, 0, successPaths);
	
	free(retval);
	
	return successPaths;
}

void depthFirstSolve(Maze * m, MazePos curpos, char * path, int step, PathLL * successPaths) {
	
	if(atEnd(curpos, m)){
	path[step] = '\0';
	addNode(successPaths, path);
	return;
	}
	if(!squareOK(curpos, m)){
	return;
	}

	m -> maze[curpos.ypos][curpos.xpos].visited = true;
	char dir[4] = {NORTH, SOUTH, EAST, WEST};
	MazePos steps[4] = {
	{.xpos = curpos.xpos, .ypos = curpos.ypos - 1},
	{.xpos = curpos.xpos, .ypos = curpos.ypos + 1},
	{.xpos = curpos.xpos + 1, .ypos = curpos.ypos},
	{.xpos = curpos.xpos - 1, .ypos = curpos.ypos}
	};
	int i;
	for(i = 0; i < 4; i++)
	{
	path[step] = dir[i];
	depthFirstSolve(m, steps[i], path, step + 1, successPaths);
	}
	m -> maze[curpos.ypos][curpos.xpos].visited = false;
	return;
}

