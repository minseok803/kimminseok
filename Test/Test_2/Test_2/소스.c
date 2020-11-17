#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

void Quiz1();
void Quiz2();
void Quiz3();
void Quiz4();
void Quiz5();
int menu();
void Play(int max, int chance);
void SetMax(int *max, int *chance);

void main()
{
	Quiz1();
	printf("\n\n");
	Quiz2();
	printf("\n\n");
	Quiz3();
	printf("\n\n");
	Quiz4();
	printf("\n\n");
	Quiz5();
}

void Quiz1()
{
	printf("1번 문제\n\n");
	int num1, num2, big;
	printf("두 정수를 입력하시오:");
	scanf("%d%d", &num1, &num2);
	if (num1 > num2)
		big = num1;
	else
		big = num2;
	if ((big % 2) == 0)
		printf("두 정수 중 큰수는 %d이고 짝수입니다.\n", big);
	else
		printf("두 정수 중 큰수는 %d이고 홀수입니다.\n", big);
}

void Quiz2()
{
	printf("2번 문제\n\n");
	int kor, eng, math, sum;
	double aver;
	printf("국어 점수를 입력하시오:");
	scanf("%d", &kor);
	printf("영어 점수를 입력하시오:");
	scanf("%d", &eng);
	printf("수학 점수를 입력하시오:");
	scanf("%d", &math);
	sum = kor + eng + math;
	aver = (double)sum / 3.0f;
	printf("국어 점수 : %d\n영어 점수 : %d\n수학 점수 : %d\n합계: %d\n평균 : %.2lf\n", kor, eng, math, sum, aver);
	printf("등급 : ");
	if (aver >= 90)
		printf("A");
	else if (aver >= 80)
		printf("B");
	else if (aver >= 70)
		printf("C");
	else if (aver >= 60)
		printf("D");
	else
		printf("F");
}

void Quiz3()
{
	printf("3번 문제\n\n");
	int sum = 0;
	for (int i = 1; i <= 1000; i++)
	{
		if (i % 5 == 0);
		else if (i % 3 == 0)
			continue;
		sum += i;
	}
	printf("합계 : %d\n", sum);
}

void Quiz4()
{
	printf("4번 문제\n\n");
	int input;
	int sum = 0;
	printf("합계를 구할 정수들을 입력하시오(0입력시 종료)\n");
	while (1)
	{
		scanf("%d", &input);
		sum += input;
		if (input == 0)
			break;
	}
	printf("해당 숫자들의 합은 총 %d입니다.\n", sum);
}

void Quiz5()//updown
{
	printf("5번문제\n");
	system("pause");
	srand((unsigned int)time(NULL));
	int max, chance;
	max = 30;
	chance = 10;
	while (1)
	{
		switch (menu())
		{
		case 1:
			Play(max, chance);
			break;
		case 2:
			SetMax(&max, &chance);
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}

int menu()
{
	system("cls");
	int select;
	printf("UpDown Game\n");
	printf("1. Start\n2. setting\n3. Exit\nSelect: ");
	scanf("%d", &select);
	return select;
}

void Play(int max, int chance)
{
	system("cls");
	printf("1~%d까지 중 랜덤한 수를 마추시오\n", max);
	int turn = 1;
	int input, randnum;
	randnum = rand() % max + 1;
	while (1)
	{
		printf("Turn %d : ", turn);
		scanf("%d", &input);
		if (input > randnum)
		{
			printf("UP\n");
		}
		else if (input < randnum)
		{
			printf("DOWN\n");
		}
		else
		{
			printf("YOU WIN\n");
			printf("정답까지 걸린 턴수 : %d\n", turn);
			break;
		}
		turn++;
		if (turn > chance)
		{
			printf("횟수 제한 초과 \nYOU LOSE\n");
			printf("정답 : %d\n", randnum);
			break;
		}
	}
	system("pause");
}
void SetMax(int* max, int* chance)
{
	int select;
	int input;
	while (1)
	{
		system("cls");
		printf("Setting\n");
		printf("1. RandMax\n2. TurnMax\n3. Exit\nSelect: ");
		scanf("%d", &select);
		switch (select)
		{
		case 1:
			system("cls");
			printf("현재 최대수 : %d\n", (*max));
			printf("변경할 최대수를 입력 : ");
			scanf("%d",&input);
			if (input < 1)
			{
				printf("1이하의 숫자로는 변경할수 없습니다.\n");
				system("pause");
			}
			else
			{
				(*max) = input;
			}
			break;
		case 2:
			system("cls");
			printf("현재 최대턴 : %d\n", (*chance));
			printf("변경할 최대턴을 입력 : ");
			scanf("%d", &input);
			if (input < 1)
			{
				printf("1이하의 숫자로는 변경할수 없습니다.\n");
				system("pause");
			}
			else
			{
				(*chance) = input;
			}
			break;
		case 3:
			return;
		default:
			break;
		}
	}
}
