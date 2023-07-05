#pragma once
#ifndef MenuAndArrow_H
#define MenuAndArrow_H
#include <iostream>
#include <conio.h>

/*
void arrow(void (*Eptr)(),void (*uptr)(), void (*dptr)(), void (*lptr)() = NULL, void (*rptr)() = NULL) {
    char keyPressed;
    do {
        keyPressed = _getch(); // Read a single character without echoing it
        if (keyPressed == -32) { // Check if the character is the escape character
            // Check if the next character is the opening square bracket
            keyPressed = _getch(); // Read the arrow key character
            switch (keyPressed) {
            case 72: // Up arrow
                uptr();
                break;
            case 80: // Down arrow
                dptr();
                break;
            case 77: // Right arrow
                if (lptr != NULL)lptr();
                break;
            case 75: // Left arrow
                if (rptr != NULL)rptr();
                break;
            }
        }
        else if ( keyPressed == '\r' ) {
            Eptr();
            return;
        }
    } while (true);
}

*/
int menuInput(int beginningY,int cursorX,int noOfChoices, char cursor = '>') {
    char keyPressed;
    int choice;
    int pointerCursorY = beginningY;
    highlightGreen();
    gotoxy(cursorX, pointerCursorY);
    std::cout << cursor;
    do {
        keyPressed = _getch(); // Read a single character without echoing it
        if (keyPressed == -32) { // Check if the character is the escape character
            keyPressed = _getch(); // Read the arrow key character
            switch (keyPressed) {
            case 72: // Up arrow
                if (pointerCursorY > beginningY) {
                    gotoxy(cursorX, pointerCursorY);
                    std::cout << ' ';
                    pointerCursorY -= 1;
                    gotoxy(cursorX, pointerCursorY);
                    std::cout << cursor;
                }
                gotoxy(0, 0);
                std::cout << pointerCursorY - 1;
                break;
            case 80: // Down arrow
                if (pointerCursorY < beginningY + noOfChoices - 1) {
                    gotoxy(cursorX, pointerCursorY);
                    std::cout << ' ';
                    pointerCursorY += 1;
                    gotoxy(cursorX, pointerCursorY);
                    std::cout << cursor;
                }
                gotoxy(0, 0);
                std::cout<< pointerCursorY;
                break;
            }
        }
        else if (keyPressed == '\r') {
            for (int i = 0; i < 3; i++) {
                if (pointerCursorY == beginningY + i) {
                    choice = i + 1;
                }
            }
            resetHighlight();
            return choice;
        }
    } while (true);
    resetHighlight();
}

#endif