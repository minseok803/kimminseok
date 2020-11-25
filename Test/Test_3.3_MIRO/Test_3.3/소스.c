#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#define WALL 10
#define EXIT 20
#define START 30
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define TRUE 1
#define FALSE 0
#define NULL 0

typedef struct position
{
	int x;
	int y;
}Position;

typedef struct player
{
	Position p;
	int count;
	int direc;
}Player;

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
void RightWallFallow(int* map, Player* player, int width);
int Move(int* map, Player* player, int width);
void TextDraw(int x, int y, char str[]);
void PlayerDraw(Player player);
void BoxDraw(int* map, int width, int height);
void MapLoad(int** map, int* width, int *height);
void init(int* map, Player* player, int width, int height);

void main() 
{
	printf("MIRO simulation\nKey Press to Start\n");
	system("pause");
	system("cls");
	int endflag = FALSE;
	int* map = NULL;
	int width, height;
	Player player1;
	MapLoad(&map, &width, &height);
	BoxDraw(map, width, height);
	init(map, &player1, width, height);
	while (!endflag)
	{
		PlayerDraw(player1);
		RightWallFallow(map, &player1, width);
		endflag = Move(map, &player1, width);
	}
	free(map);
	gotoxy(0,height);
	printf("Move: %d\n", player1.count);
	system("pause");
}

void RightWallFallow(int* map, Player* player, int width) 
{
	int index = player->p.x + (player->p.y * width);
	
	switch (player->direc)
	{
	case UP:
		index++;
		break;
	case DOWN:
		index--;
		break;
	case RIGHT:
		index += width;
		break;
	case LEFT:
		index -= width;
		break;
	}
	if (map[index] == NULL || map[index] == EXIT)
	{
		switch (player->direc)
		{
		case UP:
			player->direc = RIGHT;
			break;
		case DOWN:
			player->direc = LEFT;
			break;
		case RIGHT:
			player->direc = DOWN;
			break;
		case LEFT:
			player->direc = UP;
			break;
		}
		Sleep(200);
		PlayerDraw(*player);
	}
}
int Move(int* map, Player* player, int width)
{
	int index = player->p.x + (player->p.y * width);
	player->count++;
	while (1)
	{
		Sleep(200);
		TextDraw(player->p.x, player->p.y, "  ");
		switch (player->direc)
		{
		case UP:
			if (map[index - width] == NULL)
			{
				player->p.y--;
				return FALSE;
			}
			else if (map[index - width] == EXIT)
			{
				player->p.y--;
				return TRUE;
			}
			else
				player->direc = LEFT;
			break;
		case DOWN:
			if (map[index + width] == NULL)
			{
				player->p.y++;
				return FALSE;
			}
			else if (map[index + width] == EXIT)
			{
				player->p.y++;
				return TRUE;
			}
			else
				player->direc = RIGHT;
			break;
		case RIGHT:
			if (map[index + 1] == NULL)
			{
				player->p.x++;
				return FALSE;
			}
			else if (map[index + 1] == EXIT)
			{
				player->p.x++;
				return TRUE;
			}
			else
				player->direc = UP;
			break;
		case LEFT:
			if (map[index - 1] == NULL)
			{
				player->p.x--;
				return FALSE;
			}
			else if (map[index - 1] == EXIT)
			{
				player->p.x--;
				return TRUE;
			}
			else
				player->direc = DOWN;
			break;
		}
		PlayerDraw(*player);
	}
}

void PlayerDraw(Player player) 
{
	switch (player.direc)
	{
	case UP:
		TextDraw(player.p.x, player.p.y, "¡ã");
		break;
	case DOWN:
		TextDraw(player.p.x, player.p.y, "¡å");
		break;
	case RIGHT:
		TextDraw(player.p.x, player.p.y, "¢º");
		break;
	case LEFT:
		TextDraw(player.p.x, player.p.y, "¢¸");
		break;
	}
}


void TextDraw(int x, int y, char str[])
{
	gotoxy(x * 2, y);
	printf("%s", str);
}

void BoxDraw(int* map, int width, int height) 
{
	int index = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			switch (map[index])
			{
			case WALL:
				printf("¡á");
				break;
			case START:
			case NULL:
				printf("  ");
				break;
			case EXIT:
				printf("¡Ú");
				break;
			}
			index++;
		}
		printf("\n");
	}
}

void MapLoad(int** map, int* width, int* height) 
{
	FILE* f;
	f = fopen("map1.txt", "r");
	fscanf(f, "%d", width);
	fscanf(f, "%d", height);
	int max = (*width) * (*height);
	(*map) = (int*)malloc(sizeof(int) * max);
	for (int i = 0; i < max; i++)
	{
		fscanf(f, "%d", &(*map)[i]);
	}
	fclose(f);
}

void init(int* map, Player* player, int width, int height) 
{
	int max = width * height;
	for (int i = 0; i < max; i++)
	{
		if (map[i] == START)
		{
			player->p.x = i % width;
			player->p.y = i / width;
			break;
		}
	}
	player->count = 0;
	player->direc = RIGHT;
}
