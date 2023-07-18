#include "ConsoleSize.h"
#include "Title.h"

int centerX=0;
int centerY=0;

void setConsoleSizeAndCenter() {

	HWND console = GetConsoleWindow();
	RECT r;

    COORD consoleSize = getConsoleWindowSize();
    int consoleWidth = consoleSize.X;
    int consoleHeight = consoleSize.Y;

    centerX = consoleWidth / 2;
    centerY = consoleHeight / 2;
}

