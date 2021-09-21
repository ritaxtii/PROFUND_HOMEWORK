#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <bits/stdc++.h>
#include <conio.h>
#define screen_x 80
#define screen_y 25
#define px first
#define py second

using namespace std;
HANDLE rHnd;
HANDLE wHnd;
DWORD fdwMode;
COORD bufferSize = { screen_x,screen_y };
SMALL_RECT windowSize = { 0,0,screen_x - 1,screen_y - 1 };
CHAR_INFO consoleBuffer[screen_x * screen_y];
COORD characterPos = { 0,0 };
int last_posx = -1, last_posy = -1;
int color_fg, color_bg;
int sum_Boom = 0;
vector<pair<int, int>> star;
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
void draw_star(int x, int y)
{
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(7, 0);
    printf("*");
}
void draw_ship(int x, int y)
{
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(color_fg, color_bg);
    printf("<-0->");
}
void erase_star(int x, int y)
{
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(0, 0);
    printf(" ");
}
void erase_ship(int x, int y)
{
    COORD c = { x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
    setcolor(0, 0);
    printf("     ");
}

int setConsole(int x, int y)
{
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
    SetConsoleScreenBufferSize(wHnd, bufferSize);
    return 0;
}
int setMode()
{
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT |
        ENABLE_MOUSE_INPUT;
    SetConsoleMode(rHnd, fdwMode);
    return 0;
}
void setcursor(bool visible)
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(console, &lpCursor);
}
void rand_star(bool y)
{
    int randx = abs(rand() % 80), randy = abs(rand() % 25);
    if (!y)  randy = 0;
    while (cursor(randx, randy) == '*')
    {
        randx = abs(rand() % 80), randy = abs(rand() % 25);
        if (!y)  randy = 0;
    }
    draw_star(randx, randy);
    star.push_back(make_pair(randx, randy));
}
void rand_color()
{
    color_fg = rand() % 16;
    color_bg = rand() % 16;
    while (color_bg == color_fg)
    {
        color_bg = rand() % 16;
    }
}
void check_star(int x, int y)
{
    /*
     *****
    <-0->
     *****
    */
    bool Sound = false;
    for (int i = 0; i < star.size(); i++)
    {
        if (star[i].px - x >= 0 && star[i].px - x < 5)
        {
            if (star[i].py + 1 == y || star[i].py - 1 == y)
            {
                erase_ship(star[i].px, star[i].py);
                star.erase(star.begin() + i);
                i--;
                rand_star(0);
                Sound = true;

            }
        }
        else if (star[i].py == y)
        {
            if (star[i].px == x - 1 && star[i].px == x + 5)
            {
                erase_ship(star[i].px, star[i].py);
                erase_ship(last_posx, last_posy);
                star.erase(star.begin() + i);
                i--;
                rand_star(0);
                Sound = true;
            }
        }
    }
    if (Sound)
    {
        Beep(700, 100);
        sum_Boom++;
    }
}
int main()
{
    bool play = true;
    DWORD numEvents = 0;
    DWORD numEventsRead = 0;
    setConsole(screen_x, screen_y);
    setMode();
    setcursor(0);
    srand(time(NULL));
    color_fg = rand() % 16;
    color_bg = rand() % 16;
    for (int i = 0; i < 80; i++)
    {
        rand_star(1);
    }
    while (play)
    {
        check_star(last_posx, last_posy);
        if (sum_Boom >= 10)
            break;
        for (int i = 0; i < star.size(); i++)
        {
            if (star[i].py < screen_y - 1)
            {
                draw_star(star[i].px, ++star[i].py);
                erase_star(star[i].px, star[i].py - 1);
            }
            else
            {
                erase_star(star[i].px, star[i].py);
                star.erase(star.begin() + i);
                i--;
                rand_star(0);
            }
        }
        GetNumberOfConsoleInputEvents(rHnd, &numEvents);
        if (numEvents != 0) {
            INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
            ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
            for (DWORD i = 0; i < numEventsRead; ++i) {
                if (eventBuffer[i].EventType == KEY_EVENT && eventBuffer[i].Event.KeyEvent.bKeyDown == true) {
                    if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                        play = false;
                    }
                    else if (eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'c' || eventBuffer[i].Event.KeyEvent.uChar.AsciiChar == 'C')
                        rand_color();
                }
                else if (eventBuffer[i].EventType == MOUSE_EVENT) {
                    int posx = eventBuffer[i].Event.MouseEvent.dwMousePosition.X;
                    int posy = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
                    if (eventBuffer[i].Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
                        rand_color();
                    else if (eventBuffer[i].Event.MouseEvent.dwEventFlags & MOUSE_MOVED) {
                        if (posx < screen_x - 2 && posy < screen_y && posx>1 && posy>0)
                        {
                            erase_ship(last_posx, last_posy);
                            draw_ship(posx - 2, posy);
                            last_posx = posx - 2, last_posy = posy;
                        }
                    }
                }
            }
            delete[] eventBuffer;
        }
        Sleep(100);
    }
    return 0;
}