#pragma once

#include <windows.h>


enum colorCode {
      Black
    , Blue
    , Green
    , Cyan
    , Red
    , Purple
    , Yellow
    , Default_white
    , Grey
    , Bright_blue
    , Bright_green
    , Bright_cyan
    , Bright_red
    , pink
    , yellow
    , Bright_white
};

     
inline void highlight(colorCode color) {
    // Set console color to red
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

inline void highlightRed() {
    // Set console color to red
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_INTENSITY);
}

inline void highlightGreen() {
    // Set console color to green
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN | FOREGROUND_INTENSITY);
}

inline void highlightBlue() {
    // Set console color to blue
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_INTENSITY);
}

inline void resetHighlight() {
    // Reset console color to default
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

