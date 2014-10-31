#define _CRT_SECURE_NO_WARNINGS 1
#define SIZE 10
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

//char[SIZE][SIZE] is the grid. int[] is the car

//displays the grid and the cars coords
void display(char grid[SIZE][SIZE], int car[]);

//fills the grid with '-'
void makeGrid(char grid[SIZE][SIZE]);

//limits the car's coords to to (0,SIZE-1)
//blocks the car if there is a wall
//the car explodes if there is a bomb
int update(char grid[SIZE][SIZE], int car[], char direct);

//if car hits the bomb (B0 then it returns 1, if not then it returns 0
int updateBomb(char grid[SIZE][SIZE], int car[]);

//if car is beyond boundary then place car back into grid
void updateBoundary(int car[]);

//if car hits walls then place car back to original position
void updateWall(char grid[SIZE][SIZE], int car[], char direct);

//removes car from grid and changes coords based from keyboard
void move(char grid[SIZE][SIZE], int car[], char direct);

//displays directions for the car
void displayDirections();

//changes the value on the grid to any char.
void makeValue(char grid[SIZE][SIZE], int x, int y, int lenX, int lenY, char value);

int main()
{
	srand((unsigned int)time(NULL)); //sets the seed of random to the current time

	char grid[SIZE][SIZE];
	int car[2] = { 0, 0 };
	char direct;

	makeGrid(grid);
	grid[0][0] = 'C';
	makeValue(grid, 2, 2, 6, 1, 'W');
	makeValue(grid, 2, 2, 1, 6, 'W');
	makeValue(grid, 2, 4, 1, 1, '-');
	makeValue(grid, 4, 2, 1, 1, '-');
	makeValue(grid, 0, SIZE - 1, 1, 1, 'B');

	displayDirections();
	do
	{
		display(grid, car);
		scanf(" %c", &direct);
		direct = tolower(direct);
		move(grid, car, direct);
	} while (update(grid, car, direct));
}

//displays the grid and the cars coords
void display(char grid[SIZE][SIZE], int car[])
{
	int col, row;
	for (col = 0; col < SIZE; col++)
	{
		for (row = 0; row < SIZE; row++)
		{
			printf("%c", grid[row][col]);
		}
		printf("\n");
	}

	printf("[%d,%d]\n", car[0], car[1]);
}

//fills the grid with '-'
void makeGrid(char grid[SIZE][SIZE])
{
	int col, row;
	for (col = 0; col < SIZE; col++)
	{
		for (row = 0; row < SIZE; row++)
		{
			grid[row][col] = '-';
		}
		printf("\n");
	}
}

//limits the car's coords to to (0,SIZE-1)
//blocks the car if there is a wall
//the car explodes if there is a bomb
int update(char grid[SIZE][SIZE], int car[], char direct)
{
	updateBoundary(car);
	updateWall(grid, car, direct);

	if (direct == 'x' || updateBomb(grid, car))
	{
		return 0;
	}
	grid[car[0]][car[1]] = 'C';
	return 1;
}

//if car hits the bomb (B0 then it returns 1, if not then it returns 0
int updateBomb(char grid[SIZE][SIZE], int car[])
{
	int i;
	if (grid[car[0]][car[1]] == 'B')
	{
		printf("You exploded!\n");
		for (i = 0; i < 15; i++)
		{
			grid[rand() % SIZE][rand() % SIZE] = (char)(rand() % 94) + 33;
		}
		display(grid, car);
		return 1;
	}
	return 0;

}

//if car is beyond boundary then place car back into grid
void updateBoundary(int car[])
{
	if (car[1] > SIZE - 1)
		car[1] = SIZE - 1;
	if (car[1] < 0)
		car[1] = 0;

	if (car[0] > SIZE - 1)
		car[0] = SIZE - 1;
	if (car[0] < 0)
		car[0] = 0;
}

//if car hits walls then place car back to original position
void updateWall(char grid[SIZE][SIZE], int car[], char direct)
{
	if (grid[car[0]][car[1]] == 'W')
	{
		switch (direct)
		{
		case 's':
			car[1]--;
			break;
		case 'w':
			car[1]++;
			break;
		case 'a':
			car[0]++;
			break;
		case 'd':
			car[0]--;
		}
	}
}

//removes car from grid and changes coords based from keyboard
void move(char grid[SIZE][SIZE], int car[], char direct)
{
	grid[car[0]][car[1]] = '-';

	switch (direct)
	{
	case 's':
		car[1]++;
		break;
	case 'w':
		car[1]--;
		break;
	case 'd':
		car[0]++;
		break;
	case 'a':
		car[0]--;
		break;
	}
}

//displays directions for the car
void displayDirections()
{
	printf("Move around with wasd. \n");
	printf("Exit the program with x. \n");
	printf("The car is C. Walls are W. Bombs are B. \n\n");
}

//changes the value on the grid to any char.
void makeValue(char grid[SIZE][SIZE], int x, int y, int lenX, int lenY, char value)
{
	int yCount, xCount;
	for (yCount = 0; yCount < lenY; yCount++)
	{
		for (xCount = 0; xCount < lenX; xCount++)
		{
			grid[x + xCount][y + yCount] = value;
		}
	}
}
