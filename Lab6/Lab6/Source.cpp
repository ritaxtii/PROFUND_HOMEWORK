#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	setcolor(2, 4);
	printf("<-0->");
}
void draw_bullet(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	setcolor(4, 0);
	printf("  o  ");
}
void erase_ship(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	setcolor(0, 0);
	printf("     ");
}
void erase_bullet(int x, int y)
{
	COORD c = { x+2,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	setcolor(0, 0);
	printf(" ");
}

void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}
int main()
{
	setcursor(0);
	vector<pair<int, int>> Bullet;
	char ch = ' ';
	int x = 38, y = 20,move=0;
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a')
			{
				move = -1;
			}
			if (ch == 's')
			{
				move = 0;
			}
			if (ch == 'd')
			{
				move = 1;
			}
			if (ch == ' ')
			{
				if (Bullet.size() < 5)
				Bullet.push_back(make_pair(x, y));
			}
			fflush(stdin);
		}
		erase_ship(x, y);
		for (int i = 0; i < Bullet.size(); i++)
		{
			if (Bullet[i].second != 0)
			{
			erase_bullet(Bullet[i].first, Bullet[i].second);
			draw_bullet(Bullet[i].first, --Bullet[i].second);
			}
			else
			{
				erase_bullet(Bullet[i].first, Bullet[i].second);
				Bullet.erase(Bullet.begin());
				i--;
			}
			
		}
		if ((x > 0 && move == -1) || (x < 115 && move == 1) || move == 0)
			draw_ship(x+=move, y);
		else
		{
			move = 0;
			draw_ship(x += move, y);
		}
		Sleep(100);
	} while (ch != 'x');


	return 0;
}
