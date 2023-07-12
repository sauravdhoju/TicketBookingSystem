#ifndef Title_H
#define Title_H

#include <iostream>
#include <iomanip>
#include <string>
#include <Windows.h>
#include <string.h>

// Forward declaration
COORD getConsoleWindowSize();

inline int length(std::string s){
    return s.length();
}
inline void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Title(const std::string& text, int paddingY);

void setConsoleSizeAndCenter();
#endif // Title_H
