#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include <thread>
#include <conio.h>
#include <vector>
#include "Global.h"
#include "ConsoleColor.h"
#include "ConsoleSize.h"

inline std::string presentTime() {
    time_t result = time(NULL);
    char str[26];
    ctime_s(str, sizeof str, &result);
    std::string date = str;
    gotoxy(2 * centerX - 24, 0);
    std::cout << date;
    return date;
}

struct DateAndTime {
    int year=0, month=0, day=0, hour=0, minute=0, second=0;
    std::string dateString() {
        return std::to_string(year)+ '/' + std::to_string(month)+ '/' + std::to_string(day)
                + "  " + std::to_string(hour)+':' + std::to_string(minute)+':'+std::to_string(second);
    }
    void display(){
        if (year > 0)std::cout << "" <<std::setw(-4)<< year << " years " << std::setw(-2) << month << " months " << std::setw(-2) << day << " Days ";
        else if (month > 0)std::cout << std::setw(-2) << month << " months " << std::setw(-2) << day << " Days ";
        else std::cout << std::setw(-2) << day << " Days ";
        std::cout << std::setw(-2) << hour << " hours " << std::setw(-2) << minute << " minutes " << std::setw(-2) << second << " seconds " << std::endl;
    }
    void diffTime(){
        time_t now = time(0);
        tm* gmtm = gmtime(&now);//if this is causing error then:
                                //Configuration Properties>>C/C++>>Preporocessor>>Preprocessor Definitions>> _CRT_SECURE_NO_WARNINGS
        DateAndTime diff;
        diff.year   = year - (1900 + gmtm->tm_year);
        diff.month    = month - (1 + gmtm->tm_mon);
        diff.day    = day - (gmtm->tm_mday);
        diff.hour     = hour - (5 + gmtm->tm_hour);
        diff.minute = minute - (45 + gmtm->tm_min);
        diff.second    = second - (gmtm->tm_sec);
        while (diff.second < 0 || diff.minute < 0 || diff.hour < 0 || diff.day < 0 || diff.month < 0) {
            if (diff.second < 0) {
                diff.minute--;
                diff.second += 60;
            }
            if (diff.minute < 0) {
                diff.hour--;
                diff.minute += 60;
            }
            if (diff.hour < 0) {
                diff.day--;
                diff.hour += 24;
            }
            if (diff.day < 0) {
                diff.month--;
                diff.day += 30;
            }
            if (diff.month < 0) {
                diff.year--;
                diff.month += 12;
            }
        }
        if (diff.year < 0) std::cout << "The Movie has premired already";
        else diff.display();
    }
    void modifyTime() {
        int vx = 15;
        int vy = 2;
      
        do{
            gotoxy(vx, vy); system("cls");  presentTime();

            Title("Movie-Ticket Booking System", centerY - 12);
            gotoxy(centerX -40, centerY - 12 - 12);//not working gotoxy function in this section
            std::cout << "Movie Released Year: ";
            std::cin >> year;
            if (year < 2023 || year >2030) {
                std::cout << "\tYear cant be less than 2023 and greater than 2030"; _getch();
            }
        } while (year < 2023 || year >2030);

      
        do{
            gotoxy(vx, vy); system("cls");  presentTime();
            Title("Movie-Ticket Booking System", centerY - 12);
            gotoxy(centerX - 40, centerY - 12 - 12);//not working gotoxy function in this section
            std::cout << "Movie Release Month: ";
            std::cin >> month;
            if (month < 1 || month>12) {
                std::cout << "\tMonth cant be less than 1 and greater than 12"; _getch();
            }
        }while (month<1||month>12);

      
        do{
            gotoxy(vx, vy); system("cls");  presentTime();
            Title("Movie-Ticket Booking System", centerY - 12);
            std::cout << "Movie Release Day: ";
            std::cin >> day;
            if (day < 1 || day>31) {
                std::cout << "\tDay cant be less than 1 and greater than 31"; _getch();
            }
        } while (day<1||day>31);

      
        do{
            gotoxy(vx, vy); system("cls");  presentTime();
            Title("Movie-Ticket Booking System", centerY - 12);
            std::cout << "Movie Release Hour: ";
            std::cin >> hour;
            if (hour < 0 || hour>23) {
                std::cout << "\tHour cant be less than 0 and greater than 23"; _getch();
            }
        } while (hour<0||hour>23);

      
        do{
             gotoxy(vx, vy);system("cls");  presentTime();
             Title("Movie-Ticket Booking System", centerY - 12);
             std::cout << "Movie Release Minute: ";
            std::cin >> minute;
            if (minute < 0 || minute>59) {
                std::cout << "\tMinute cant be less than 0 and greater than 59"; _getch();
            }
        } while (minute < 0 || minute>59);

      
        do{
             gotoxy(vx, vy);system("cls");  presentTime();
             Title("Movie-Ticket Booking System", centerY - 12);
             std::cout << "Movie Release Second: ";
            std::cin >> second;
            if (second < 0 || second>59) {
                std::cout << "\tSecond cant be less than 0 and greater than 59"; _getch();
            }
        } while (second<0||second>59);
        gotoxy(vx, vy); system("cls");  presentTime();
    }
};

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
inline int menuInput(std::vector<std::string> options, int startX, int startY, char cursor = '>') {
    char keyPressed;
    int choice = 1;
    do {
        for (int i = 0; i < options.size(); i++) {
            gotoxy(startX - 1, startY + i);
            if (i == choice - 1) {
                highlightGreen();
                std::cout << cursor;
            }
            else std::cout << " ";
            std::cout << i + 1 << ". " << options.at(i);
            resetHighlight();
        }
        keyPressed = _getch(); // Read a single character without echoing it
        if (keyPressed == -32) { // Check if the character is the escape character
            keyPressed = _getch(); // Read the arrow key character
            switch (keyPressed) {
            case 72: // Up arrow
                if (choice > 1) {
                    choice--;
                }
                break;
            case 80: // Down arrow
                if (choice < options.size()) {
                    choice++;
                }
                break;
            }
        }
        else if (keyPressed == '\r') {
            return choice;
        }
        else if (keyPressed == char(27)) {//esc to exit lol
            return options.size();
        }
    } while (true);
}


inline void updatePresentTime() {
    while (true) {
        HANDLE m_hConsole;
        WORD m_currentConsoleAttr;
        CONSOLE_SCREEN_BUFFER_INFO csbi;

        // Retrieve and save the current attributes
        m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        if (GetConsoleScreenBufferInfo(m_hConsole, &csbi))
            m_currentConsoleAttr = csbi.wAttributes;

        // Store the current cursor position
        GetConsoleScreenBufferInfo(m_hConsole, &csbi);
        COORD originalPos = csbi.dwCursorPosition;

        resetHighlight();
        presentTime();
        // Restore the cursor position
        SetConsoleCursorPosition(m_hConsole, originalPos);

        // Set the attribute to the original one
        SetConsoleTextAttribute(m_hConsole, m_currentConsoleAttr);

        // Sleep for one second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}