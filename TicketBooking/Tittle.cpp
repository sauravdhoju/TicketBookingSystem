#include "Title.h"
#include "ConsoleSize.h"

COORD getConsoleWindowSize() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;
    GetConsoleScreenBufferInfo(consoleHandle, &screenInfo);

    COORD windowSize;
    windowSize.X = screenInfo.srWindow.Right - screenInfo.srWindow.Left + 1;
    windowSize.Y = screenInfo.srWindow.Bottom - screenInfo.srWindow.Top + 1;

    return windowSize;
}

void Title(const std::string& text, int paddingY) {
    COORD consoleSize = getConsoleWindowSize();
    int consoleWidth = consoleSize.X;
    int consoleHeight = consoleSize.Y;

    int textWidth = text.length();
    int paddingX = (consoleWidth - textWidth) / 2;

    gotoxy(paddingX, paddingY);
    std::cout << text << std::endl;
}