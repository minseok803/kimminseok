#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
#include<Windows.h>
#define SPACE 32
#define ENTER 13
#define FLAG -1
#define TRUE 1
#define FALSE 0
#define MINE 10
//10  50  100
//

typedef struct point
{
	int x;
	int y;
}Point;

typedef struct block
{
	Point p;
	int mine;
	int check;
}Block;

void gotoxy(int x, int y)
{
	COORD Pos = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}
int menu();
void SelectLevel(int* width, int* height, int* mine);
void BoxDraw(int width, int height);
void TextDraw(int x, int y, char str[]);
void BlockDraw(Block map);
void play(int width, int height, int mine);
void init(Block* map, int width, int height);
char input();
void minning(Block* map, int width, int height, int mine);
void PlusAround(int width, int height, Block* map);
void move(Point* cusor, int width, int height, char ch);
void Flag(Block* block);
int Check(Block block);
void ReDraw(Block* map, int width, int height);
void MineDraw(Block* map, int max, int mine);
int Victory(Block* map, int max, int mine);

void main()
{
	int width, height, mine;
	srand((unsigned)time(NULL));
	while (1)
	{
		switch (menu())
		{
		case 1:
			SelectLevel(&width, &height, &mine);
			play(width, height, mine);
			break;
		case 2:
			return;
		default:
			break;
		}
	}
}

void SelectLevel(int* width, int* height, int* mine)
{
	int select;
	while (1) {
		system("cls");
		printf("LEVEL\n\t1.EASY (MINE : 10)\n\t2.NORMAL (MINE : 50)\n\t3.HARD (MINE : 100)\nSELECT : ");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			(*width) = 10;
			(*height) = 10;
			(*mine) = 10;
			return;
		case 2:
			(*width) = 20;
			(*height) = 20;
			(*mine) = 50;
			return;
		case 3:
			(*width) = 30;
			(*height) = 30;
			(*mine) = 100;
			return;
		default:
			printf("잘못된 선택입니다.\n");
			system("pause");
			break;
		}
	}
}

int menu() 
{
	int select;
	system("cls");
	printf("MINE GAME\n\t1.GAME START\n\t2.EXIT\nSELECT : ");
	scanf("%d", &select);
	return select;
}

void BoxDraw(int width, int height) 
{
	for (int y = 0; y <= height + 1; y++)
	{
		for (int x = 0; x <= width + 1 ; x++)
		{
			if (y==0)
			{
				if (x == 0)
					printf("┌");
				else if (x == width + 1)
					printf("┐");
				else
					printf("─");
			}
			else if (y == height + 1)
			{
				if (x == 0)
					printf("└");
				else if (x == width + 1)
					printf("┘");
				else
					printf("─");
			}
			else
			{
				if (x == 0 || x == width + 1)
					printf("│");
				else
					printf("■");
			}
		}
		printf("\n");
	}
}

void TextDraw(int x, int y, char str[])
{
	gotoxy(x * 2, y);
	printf("%s", str);
}

void IntDraw(int x, int y, int num)
{
	gotoxy(x * 2, y);
	printf("%d", num);
}

void BlockDraw(Block map)
{
	if (map.check == FLAG)
		TextDraw(map.p.x, map.p.y, "V");
	else if (map.check == FALSE)
		TextDraw(map.p.x, map.p.y, "■");
	else
	{
		if (map.mine == 0)
			TextDraw(map.p.x, map.p.y, "□");
		else
			IntDraw(map.p.x, map.p.y, map.mine);
	}
}

char input()
{
	char ch;
	ch = _getch();
	switch (ch)
	{
	case 'A':
		ch = 'a';
	case 'a':
		break;
	case 'S':
		ch = 's';
	case 's':
		break;
	case 'D':
		ch = 'd';
	case 'd':
		break;
	case 'W':
		ch = 'w';
	case 'w':
		break;
	case ENTER:
	case SPACE:
		break;
	default:
		break;
	}
	return ch;
}

void move(Point* cusor, int width, int height,char ch)
{
	switch (ch)
	{
	case 'a':
		if (cusor->x >1)
			cusor->x--;
		break;
	case 'd':
		if (cusor->x < width)
			cusor->x++;
		break;
	case 's':
		if (cusor->y <height)
			cusor->y++;
		break;
	case 'w':
		if (cusor->y > 1)
			cusor->y--;
		break;
	}
	TextDraw(cusor->x, cusor->y, "⊙");
}

void play(int width, int height, int mine)
{
	char ch;
	int index, endflag = FALSE;
	Block* map = NULL;
	map = (Block*)malloc(sizeof(Block) * width * height);
	Point cusor;
	cusor.x = width / 2;
	cusor.y = height / 2;
	system("cls");
	init(map, width, height);
	minning(map ,width, height, mine);
	BoxDraw(width, height);
	while (!endflag)
	{
		ch = input();
		index = (cusor.x - 1) + ((cusor.y - 1) * width);
		switch (ch)
		{
		case 'a':
		case 'd':
		case 's':
		case 'w':
			BlockDraw(map[index]);
			move(&cusor, width, height, ch);
			break;
		case SPACE:
			switch (Check(map[index]))
			{
			case FALSE:
				ReDraw(&map[index], width, height);
				if (Victory(map, width * height, mine))
				{
					endflag = TRUE;
					TextDraw(1, height + 2, "YOU  WIN   ");
				}
				break;
			case MINE:
				MineDraw(map, width * height, mine);
				endflag = TRUE;
				TextDraw(1, height + 2, "YOU LOSE   ");
				break;
			default:
				break;
			}
			break;
		case ENTER:
			Flag(&map[index]);
			break;
		default:
			break;
		}
	}
	free(map);
	map = NULL;
	system("pause");
}

void init(Block* map, int width, int height) 
{
	int index = 0;
	for (int y = 1; y <= height; y++)
	{
		for (int x = 1; x <= width; x++)
		{
			map[index].p.x = x;
			map[index].p.y = y;
			map[index].check = 0;
			map[index].mine = 0;
			index++;
		}
	}
}

void minning(Block* map, int width, int height, int mine) 
{
	int x, y, index;
	for (int i = 0; i < mine; i++)
	{
		while (1)
		{
			x = rand() % width;
			y = rand() % height;
			index = x + (y * width);
			if (map[index].mine >= MINE)
				continue;
			else
			{
				map[index].mine = MINE;
				PlusAround(width, height, &map[index]);
				break;
			}
		}
	}
}

void PlusAround(int width, int height, Block* map)
{
	if (map->p.x != 1)
	{
		(map - 1)->mine++;				//9시
		if (map->p.y != 1)
			(map - width - 1)->mine++;	//11시
		if (map->p.y != height)
			(map + width - 1)->mine++;	//7시
	}
	if (map->p.x != width)
	{
		(map + 1)->mine++;				//3시
		if (map->p.y != 1)
			(map - width + 1)->mine++;	//1시
		if (map->p.y != height)
			(map + width + 1)->mine++;	//5시
	}
	if (map->p.y != 1)
		(map - width)->mine++;			//12시
	if (map->p.y != height)
		(map + width)->mine++;			//6시
}

void Flag(Block* block)
{
	if (block->check == TRUE)
		return;
	if (block->check == FLAG)
	{
		block->check = FALSE;
		TextDraw(block->p.x, block->p.y, "■");
	}
	else
	{
		block->check = FLAG;
		TextDraw(block->p.x, block->p.y, "V");
	}
}

int Check(Block block)
{
	if (block.check == TRUE)
		return TRUE;
	else if (block.mine >= MINE)
		return MINE;
	else
		return FALSE;
}

void ReDraw(Block* map, int width, int height)
{
	if (map->check == TRUE)
		return;
	else
		map->check = TRUE;
	if (map->mine != 0)
	{
		IntDraw(map->p.x,map->p.y,map->mine);
		return;
	}
	else
	{
		TextDraw(map->p.x, map->p.y, "□");
	}

	if (map->p.x != 1)
	{
		ReDraw(map - 1, width, height);
		if (map->p.y != 1)
			ReDraw(map - width - 1, width, height);
		if (map->p.y != height)
			ReDraw(map + width - 1, width, height);
	}
	if (map->p.x != width)
	{
		ReDraw(map + 1, width, height);
		if (map->p.y != 1)
			ReDraw(map - width + 1, width, height);
		if (map->p.y != height)
			ReDraw(map + width + 1, width, height);
	}
	if (map->p.y != 1)
		ReDraw(map- width, width, height);
	if (map->p.y != height)
		ReDraw(map + width, width, height);
}

void MineDraw(Block* map, int max, int mine) 
{
	int count = 0;
	for (int i = 0; i < max; i++)
	{
		if (map[i].mine >= MINE)
		{
			TextDraw(map[i].p.x, map[i].p.y, "☆");
			count++;
		}
		if (count >= mine)
			break;
	}
}

int Victory(Block* map, int max, int mine)
{
	int count = 0;
	for (int i = 0; i < max; i++)
	{
		if (map[i].check != TRUE)
			count++;
		if (count > mine)
			return FALSE;
	}
	if (count == mine)
		return TRUE;
}