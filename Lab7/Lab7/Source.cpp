#include <bits/stdc++.h>
#include <windows.h>
#include <conio.h>
using namespace std;
int score = 0;
char cursor(int x, int y) {
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    char buf[2]; COORD c = { x,y }; DWORD num_read;
    if (
        !ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))

        return '\0';
    else
        return buf[0];

}
void setcolor(int fg, int bg)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}
void draw_ship(int x, int y)
{
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(2, 0);
    printf("<-0->");
}
void draw_star(int x, int y)
{
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(7, 0);
    printf("*");
}
void draw_score()
{
    COORD c = { 100,1 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(7, 0);
    printf("score : %d", score);
}
void draw_bullet(int x, int y)
{
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(4, 0);
    printf("^");
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
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(0, 0);
    printf(" ");
}
void erase_star(int x, int y)
{
    COORD c = { x,y };
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

    srand(time(NULL));
    for (int i = 0; i < 20; i++)
    {
        int randx = abs((rand() % 61) + 10), randy = abs((rand() % 4) + 2);
        while (cursor(randx, randy) == '*')
        {
            randx = abs((rand() % 61) + 10), randy = abs((rand() % 4) + 2);
        }
        draw_star(randx, randy);
    }
    draw_score();
    char ch = ' ';
    int x = 38, y = 20, move = 0;
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
                Bullet.push_back(make_pair(x + 2, y));
            }
            fflush(stdin);
        }
        for (int i = 0; i < Bullet.size(); i++)
        {

            if (Bullet[i].second != 0)
            {
                if (cursor(Bullet[i].first, Bullet[i].second - 1) == '*')
                {
                    score++;
                    draw_score();
                    Beep(700, 100);
                    int randx = abs((rand() % 61) + 10), randy = abs((rand() % 4) + 2);
                    while (cursor(randx, randy) == '*')
                    {
                        randx = abs((rand() % 61) + 10), randy = abs((rand() % 4) + 2);
                    }
                    draw_star(randx, randy);
                    erase_bullet(Bullet[i].first, Bullet[i].second);
                    erase_star(Bullet[i].first, Bullet[i].second - 1);
                    Bullet.erase(Bullet.begin() + i);
                    i--;

                }
                else
                {
                    erase_bullet(Bullet[i].first, Bullet[i].second);
                    draw_bullet(Bullet[i].first, --Bullet[i].second);
                }

            }
            else
            {
                erase_bullet(Bullet[i].first, Bullet[i].second);
                Bullet.erase(Bullet.begin() + i);
                i--;
            }


        }
        erase_ship(x, y);
        if ((x > 0 && move == -1) || (x <= 70 && move == 1) || move == 0)
            draw_ship(x += move, y);
        else
        {
            move = 0;
            draw_ship(x += move, y);
        }
        Sleep(100);
    } while (ch != 'x');


    return 0;
}