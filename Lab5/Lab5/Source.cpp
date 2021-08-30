#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;

void draw_ship(int x,int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("<-0->");
}
void erase_ship(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	printf("     ");
}

void gotoxy(int x, int y)
{
	COORD c = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main()
{
	char ch = ' ';
	int x=38, y=20;
	draw_ship(x, y);
	do {
		if (_kbhit()) {
			ch = _getch();
			if (ch == 'a' && x > 0)
			{
				erase_ship(x, y);
				draw_ship(--x, y);
			}
			if (ch == 'd' && x < 80)
			{
				erase_ship(x, y);
				draw_ship(++x, y);
			}
			if (ch == 'w' && y > 0)
			{
				erase_ship(x, y);
				draw_ship(x, --y);
			}
			if (ch == 's' && y < 23)
			{
				erase_ship(x, y);
				draw_ship(x, ++y);
			}
			fflush(stdin);
		}
		Sleep(100);
	} while (ch != 'x');
	/*for (int i = 0; i < 80; i++)
	{
		draw_ship(i,20);
		Sleep(500);
	}*/
	
	return 0;
}