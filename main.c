#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#define COLS 24
#define ROWS 24


//ogni cella ha un nuovo e un vecchio stato
//uso il vecchio stato per calcolarmi il nuovo stato di ogni cella
//dopo ogni ciclo di vita del programma
//e poi me li copio sul vecchio stato alla fine
//true (1) vuol dire che la cella è viva, false (0) se è morta

typedef struct
{
	bool oS;
	bool nS;
	
} cell;

//stampa il piano 
void printPlane(cell plane[ROWS][COLS])
{
	system("clear");
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

//conta il numero di celle adiacenti ad una cella [x][y]
int countNeighbours(cell plane[ROWS][COLS], int x, int y)
{
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
	//per valutare per ogni cella, se sarà viva o morta alla prossima
	//iterazione
	for (int x = 0; x < COLS; x++)
	{
		for (int y = 0; y < ROWS; y++)
		{
			int adjCnt = countNeighbours(plane, x, y);
			//printf("neighbours: %d\n", countNeighbours(x,y));
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
	//e poi aggiorno il vecchio stato col nuovo
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
	//mappa del piano delle cellule
	cell cellmap[ROWS][COLS];
	//mappa del file di input
	//questo file è una griglia di 1 e 0 
	//a cui ad ogni 1 associo una cella con valore iniziale true 
	//e ad ogni 0 una con valore iniziale false
	char charmap[ROWS][COLS];

	//azzero charmap
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
	
	while(true) //ciclo principale del programma
	{
		printPlane(cellmap);
		evalCells(cellmap);
		usleep(1000000);
	}
}