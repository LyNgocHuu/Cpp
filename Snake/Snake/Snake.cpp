#include <stdio.h>
#include <conio.h>
#include "console.h"
#include <Windows.h>

#define ConsoleWidth 25
#define ConsoleHeight 25

enum Status { up, down, left, right };
struct Diem
{
	int x, y;
};
struct Snake
{
	Diem Dot[30];
	int n;
	Status tt;
};
struct Fruit
{
	Diem fr;
};

void Create(Snake &ran, Fruit &qua)
{	
	ran.n = 1;
	ran.Dot[0].x = 0;
	ran.Dot[0].y = 0;
	ran.tt = down;

	qua.fr.x = rand() % (ConsoleWidth - 1);
	qua.fr.y = rand() % (ConsoleHeight - 1);
}
void Display(Snake ran, Fruit qua, int diem, int time)
{
	clrscr();

	for (int i = 0; i < ConsoleHeight; i++)
	{
		gotoXY(ConsoleWidth, i);
		TextColor(12);
		putchar('|');
	}

	TextColor(14);
	gotoXY(ConsoleWidth + 1, 1);
	printf(" **     ** **     ** **     **");
	gotoXY(ConsoleWidth + 1, 2);
	printf(" **     ** **     ** **     **");
	gotoXY(ConsoleWidth + 1, 3);
	printf(" ********* **     ** **     **");
	gotoXY(ConsoleWidth + 1, 4);
	printf(" **     ** **     ** **     **");
	gotoXY(ConsoleWidth + 1, 5);
	printf(" **     ** ********* *********");

	TextColor(12);
	gotoXY(ConsoleWidth + 1, 10);
	printf("score: %d", diem);
	gotoXY(ConsoleWidth + 1, 11);
	printf("time sleep: %d", time);
			
	gotoXY(qua.fr.x, qua.fr.y);
	TextColor(9);
	putchar('$');

	TextColor(13);
	gotoXY(ran.Dot[0].x, ran.Dot[0].y);
	putchar('O');
	for (int i = 1; i < ran.n; i++)
	{
		gotoXY(ran.Dot[i].x, ran.Dot[i].y);		
		putchar('*');
	}
}
void Opera(Snake &ran)
{
	for (int i = ran.n - 1; i > 0; i--)
		ran.Dot[i] = ran.Dot[i - 1];
		
	if (_kbhit())
	{
		char key = _getch();
		if (key == 'A' || key == 'a')
			ran.tt = left;
		if (key == 'D' || key == 'd')
			ran.tt = right;
		if (key == 'W' || key == 'w')
			ran.tt = up;
		if (key == 'S' || key == 's')
			ran.tt = down;
	}

	if (ran.tt == up)
		ran.Dot[0].y--;
	else if (ran.tt == down)
		ran.Dot[0].y++;
	else if (ran.tt == left)
		ran.Dot[0].x--;
	else if (ran.tt == right)
		ran.Dot[0].x++;
}
int Handle(Snake &ran, Fruit &qua,int &time,int &diem)
{
	if (ran.Dot[0].x == qua.fr.x&&ran.Dot[0].y == qua.fr.y)
	{
		for (int i = ran.n - 1; i > 0; i--)
			ran.Dot[i] = ran.Dot[i - 1];

		ran.n++;	

		if (ran.tt == up)
			ran.Dot[0].y--;
		else if (ran.tt == down)
			ran.Dot[0].y++;
		else if (ran.tt == left)
			ran.Dot[0].x--;
		else if (ran.tt == right)
			ran.Dot[0].x++;

		qua.fr.x = rand() % (ConsoleWidth - 1);
		qua.fr.y = rand() % (ConsoleHeight - 1);

		time -= 10;
		diem += 10;
	}

	if (ran.Dot[0].x < 0 || ran.Dot[0].x >= ConsoleWidth
		|| ran.Dot[0].y < 0 || ran.Dot[0].y >= ConsoleHeight)
		return -1;
	for (int i = 1; i < ran.n; i++)
		if (ran.Dot[0].x == ran.Dot[i].x&&ran.Dot[0].y == ran.Dot[i].y)
			return -1;
	if (diem == 200 && time == 0)
		return 0;
}

void Nocursortype()
{
	CONSOLE_CURSOR_INFO Info;
	Info.bVisible = FALSE;
	Info.dwSize = 20;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &Info);
}

int main()	
{
	Snake snake;
	Fruit fruit;
	Create(snake, fruit);

	int TimeSleep = 200;
	int Score = 0;

	Nocursortype();
	
	while (1)
	{
		Display(snake, fruit, Score, TimeSleep);
		Opera(snake);
		int kq = Handle(snake, fruit, TimeSleep, Score);
		TextColor(11);
		if (kq == -1)
		{
			gotoXY(ConsoleWidth + 1, ConsoleHeight / 2);
			printf("LOSEEEEEEEEEEEEE");
			while (_getch() != 13);
			break;
		}
		else if (kq == 0)
		{
			gotoXY(ConsoleWidth + 1, ConsoleHeight / 2);
			printf("WWINNER CHICCKKENN DINNER");
			while (_getch() != 13);
			break;
		}
		Sleep(TimeSleep);
	}
}
