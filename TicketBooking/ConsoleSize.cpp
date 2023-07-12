#include "ConsoleSize.h"
#include "Title.h"

int centerX=0;
int centerY=0;

void setConsoleSizeAndCenter() {

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //stores the console's current dimensions
	MoveWindow(console, r.left, r.top, 900, 200, TRUE); // 800 width, 100 height

    COORD consoleSize = getConsoleWindowSize();
    int consoleWidth = consoleSize.X;
    int consoleHeight = consoleSize.Y;

    centerX = consoleWidth / 2;
    centerY = consoleHeight / 2;
}

