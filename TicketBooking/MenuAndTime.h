#pragma once
#ifndef MenuAndTime_H
#define MenuAndTime_H

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <thread>
#include <conio.h>
#include "Global.h"
#include "ConsoleColor.h"
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
inline int menuInput(int beginningY,int cursorX,int noOfChoices, char cursor = '>') {
    char keyPressed;
    int choice = 1;
    int pointerCursorY = beginningY;
    
    highlightGreen();
    gotoxy(cursorX, pointerCursorY);
    std::cout << cursor;
    resetHighlight();
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
                    choice--;
                    highlightGreen();
                    gotoxy(cursorX, pointerCursorY);
                    std::cout << cursor;
                    resetHighlight();
                }
                gotoxy(0, 0);
                std::cout << pointerCursorY - 1;
                break;
            case 80: // Down arrow
                if (pointerCursorY < beginningY + noOfChoices - 1) {
                    gotoxy(cursorX, pointerCursorY);
                    std::cout << ' ';
                    pointerCursorY += 1;
                    choice++;
                    highlightGreen();
                    gotoxy(cursorX, pointerCursorY);
                    std::cout << cursor;
                    resetHighlight();
                }
                break;
            }
        }
        else if (keyPressed == '\r') {

            return choice;
        }
        gotoxy(0, 0);
        std::cout << pointerCursorY << "," << choice;
    } while (true);

}

inline int get_month_index(std::string name)
{
    std::string month[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
    for(int i = 0; i < 12; i++) {
        if (month[i] == name) return i+1;
    }
    return 0;
}

inline int get_weekday_index(std::string name)
{
    std::string weekday[7] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    for (int i = 0; i < 7; i++) {
        if (weekday[i] == name) return i + 1;
    }
    return 0;
}

inline std::string presentTime() {
        time_t result = time(NULL);
        char str[26];
        ctime_s(str, sizeof str, &result);
        std::string date = str;
        gotoxy(2*centerX-24, 0);
        std::cout << date;
        return date;
}

/*
DateAndTime NowTime(DateAndTime dat) {
    std::string now = presentTime();
    std::istringstream str(now);
    std::string weekday, month, day, hour, minute, second,year;
    std::getline(str, weekday, ' ');
    std::getline(str, month, ' ');
    std::getline(str, day, ' ');// lol there are 2 spaces: Jul  2
    std::getline(str, day, ' ');
    std::getline(str, hour, ':');
    std::getline(str, minute, ':');
    std::getline(str, second, ' ');
    std::getline(str, year, ' ');
    dat.weekday = get_weekday_index(weekday);
    dat.month = get_month_index(month);
    dat.day = std::stoi(day);
    dat.hour = std::stoi(hour);
    dat.minute = std::stoi(minute);
    dat.second = std::stoi(second);
    dat.year = std::stoi(year);
    return dat;
    //std::cout << dat.weekday << " " << dat.month << " " << dat.day << " " << dat.hour << " " << dat.minute << " " << dat.second << " " << dat.year;
}
*/


inline void updatePresentTime() {
    
    while (!terminateProgram) {
        HANDLE                      m_hConsole;
        WORD                        m_currentConsoleAttr;
        CONSOLE_SCREEN_BUFFER_INFO   csbi;

        //retrieve and save the current attributes
        m_hConsole=GetStdHandle(STD_OUTPUT_HANDLE);
        if(GetConsoleScreenBufferInfo(m_hConsole, &csbi))
        m_currentConsoleAttr = csbi.wAttributes;

        // Store the current cursor position
        GetConsoleScreenBufferInfo(m_hConsole, &csbi);
        COORD originalPos = csbi.dwCursorPosition;

        resetHighlight();
        presentTime();

        // Restore the cursor position
        SetConsoleCursorPosition(m_hConsole, originalPos);
        
        //set the ttribute to the original one
        SetConsoleTextAttribute (m_hConsole,m_currentConsoleAttr);
        

        // Sleep for one second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    } 
}

#endif