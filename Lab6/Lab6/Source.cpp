#define _CRT_SECURE_NO_WARNING 1
#include<stdio.h>
#include<windows.h>
#include<conio.h>

void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void gotoxy(int x, int y)
{
    COORD c = { x, y };
    SetConsoleCursorPosition(
        GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void draw_ship(int x, int y)
{
    gotoxy(x, y);
    setcolor(2, 4);
    printf(" <-0-> ");
}

void erase_ship(int x, int y)
{
    gotoxy(x, y);
    setcolor(0, 0);
    printf("       ");
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
    int move = 0;
    char ch = ' ';
    int x = 38, y = 20;
    draw_ship(x, y);
    do {
        if (_kbhit())
        {
            ch = _getch();
            if (ch == 'a' && x >= 1)
            {
                move = -1;
            }
            if (ch == 'd' && x <= 72)
            {
                move = 1;
            }
            if (ch == 's' && y < 20)
            {
                move = 0;
            }
            if (ch == ' ')
            {

            }
            fflush(stdin);
        }
        if (move = -1)
        {
            erase_ship(x, y);
            draw_ship(--x, y);
        }
        if (move = 1)
        {
            erase_ship(x, y);
            draw_ship(++x, y);
        }
        Sleep(50);
    } while (ch != 'x');
    return 0;
}