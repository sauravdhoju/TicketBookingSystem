#ifndef Title_H
#define Title_H

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>


// Forward declaration
COORD getConsoleWindowSize();

inline void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Title(const std::string& text, int paddingY);

void setConsoleSizeAndCenter();
#endif // Title_H