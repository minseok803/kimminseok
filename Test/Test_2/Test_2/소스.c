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
	printf("1�� ����\n\n");
	int num1, num2, big;
	printf("�� ������ �Է��Ͻÿ�:");
	scanf("%d%d", &num1, &num2);
	if (num1 > num2)
		big = num1;
	else
		big = num2;
	if ((big % 2) == 0)
		printf("�� ���� �� ū���� %d�̰� ¦���Դϴ�.\n", big);
	else
		printf("�� ���� �� ū���� %d�̰� Ȧ���Դϴ�.\n", big);
}

void Quiz2()
{
	printf("2�� ����\n\n");
	int kor, eng, math, sum;
	double aver;
	printf("���� ������ �Է��Ͻÿ�:");
	scanf("%d", &kor);
	printf("���� ������ �Է��Ͻÿ�:");
	scanf("%d", &eng);
	printf("���� ������ �Է��Ͻÿ�:");
	scanf("%d", &math);
	sum = kor + eng + math;
	aver = (double)sum / 3.0f;
	printf("���� ���� : %d\n���� ���� : %d\n���� ���� : %d\n�հ�: %d\n��� : %.2lf\n", kor, eng, math, sum, aver);
	printf("��� : ");
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
	printf("3�� ����\n\n");
	int sum = 0;
	for (int i = 1; i <= 1000; i++)
	{
		if (i % 5 == 0);
		else if (i % 3 == 0)
			continue;
		sum += i;
	}
	printf("�հ� : %d\n", sum);
}

void Quiz4()
{
	printf("4�� ����\n\n");
	int input;
	int sum = 0;
	printf("�հ踦 ���� �������� �Է��Ͻÿ�(0�Է½� ����)\n");
	while (1)
	{
		scanf("%d", &input);
		sum += input;
		if (input == 0)
			break;
	}
	printf("�ش� ���ڵ��� ���� �� %d�Դϴ�.\n", sum);
}

void Quiz5()//updown
{
	printf("5������\n");
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
	printf("1~%d���� �� ������ ���� ���߽ÿ�\n", max);
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
			printf("������� �ɸ� �ϼ� : %d\n", turn);
			break;
		}
		turn++;
		if (turn > chance)
		{
			printf("Ƚ�� ���� �ʰ� \nYOU LOSE\n");
			printf("���� : %d\n", randnum);
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
			printf("���� �ִ�� : %d\n", (*max));
			printf("������ �ִ���� �Է� : ");
			scanf("%d",&input);
			if (input < 1)
			{
				printf("1������ ���ڷδ� �����Ҽ� �����ϴ�.\n");
				system("pause");
			}
			else
			{
				(*max) = input;
			}
			break;
		case 2:
			system("cls");
			printf("���� �ִ��� : %d\n", (*chance));
			printf("������ �ִ����� �Է� : ");
			scanf("%d", &input);
			if (input < 1)
			{
				printf("1������ ���ڷδ� �����Ҽ� �����ϴ�.\n");
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
