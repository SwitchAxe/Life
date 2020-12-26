#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define COLS 24
#define ROWS 24


//every cell has a new and old state.
//i use the old state to determine the new state of each cell
//after each life cycle of the program and then i copy
//the new state of every cell to the old one, i print the
//map  and start again.
//the true (1) state means that the cell is alive, false (0) means it's dead.

typedef struct
{
	bool oS;
	bool nS;
	
} cell;

//i print the plane
void printPlane(cell plane[ROWS][COLS])
{
	printf("\033[0;0H\033[0;0f");
	for (int i = 0; i < ROWS; i++)
	{	
		for (int e = 0; e < COLS+1; e++)
		{
			printf("%s", (plane[i][e].oS == true) ? "x" : " ");
		}
		printf("\n");
	}
}

//counts the number of living neighbours adjacent to a generic
//cell [x][y]
int countNeighbours(cell plane[ROWS][COLS], int x, int y)
{
	//variable to keep track of the neighbours
	int adjCnt = 0;
	if (plane[x-1][y].oS && ((x-1) >= 0)) adjCnt++;
	if (plane[x][y-1].oS && ((y-1) >= 0)) adjCnt++;
	if (plane[x-1][y-1].oS && ((y-1) >= 0) && ((x-1) >= 0)) adjCnt++;
	if (plane[x+1][y].oS && ((x+1) < COLS)) adjCnt++;
	if (plane[x][y+1].oS && ((y+1)) < ROWS) adjCnt++; 
	if (plane[x+1][y+1].oS && ((x+1) < COLS) && ((y+1) < ROWS)) adjCnt++;
	if (plane[x-1][y+1].oS && ((x-1) >= 0) && ((y+1) < ROWS)) adjCnt++;
	if (plane[x+1][y-1].oS && ((y-1) >= 0) && ((x+1) < ROWS)) adjCnt++;
	return adjCnt;
}


void evalCells(cell plane[ROWS][COLS])
{
	//this is to evaluate which cells will live 
	//and which will die in the nxt iteration
	for (int x = 0; x < COLS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			int adjCnt = countNeighbours(plane, x, y);
			if (plane[x][y].oS) 
			{
				if ( adjCnt == 2 || adjCnt == 3) 
					plane[x][y].nS = true;
				else plane[x][y].nS = false;
			}
			else
			{
				if (adjCnt == 3) plane[x][y].nS = true;
				else plane[x][y].nS = false;
			}			
		}
	}
	//and after i calculated each new state, 
	//i can upload it to the old one and start up again.
	for (int x = 0; x < COLS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			plane[x][y].oS = plane[x][y].nS;
		}
	}
}



int main()
{
	//cell map
	cell cellmap[ROWS][COLS];
	//file input map.
	//this is a grid of 1s and 0s in which at every 1 i associate 
	//a live cell (starting value of "true") and to each 0 a dead cell.
	char charmap[ROWS][COLS];

	//this is to put charmap to 0. i'm pretty sure it's pointless.
	for (int i = 0; i < ROWS; i++)
		for (int e = 0; e < COLS; e++)
			charmap[i][e] = 0;

	FILE* file = fopen("input", "r");

	for (int i = 0; i < ROWS; i++)
		fscanf(file, "%s", charmap[i]);

	for (int i = 0; i < ROWS; i++)
	{
		for (int e = 0; e < COLS; e++)
		{
			cellmap[i][e].oS = (charmap[i][e] == '1') ? true : false;	
		}
	}
	
	while(true) //main program cycle
	{
		printPlane(cellmap);
		evalCells(cellmap);
		usleep(1000000); //this is to better enjoy the 
		//transition between different states of the whole plane.
	}
}
