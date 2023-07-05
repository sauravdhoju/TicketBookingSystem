#pragma once

#ifndef SEAT_H
#define SEAT_H


#include<windows.h>
#include"Title.h"
#include"ConsoleColor.h"
#include<conio.h>
#include"ConsoleSize.h"


#define row 8 // last ko 2 row premium
#define column 12// 4 division
#define totalSeat row*column
#define hallLength 2*column+(column-1)//gap ko value 1
#define hallBreadth row+(row-1)
#define corridorGap 3
#define columnDivision 4
#define premiumRowSeats 2

const int columnPartition = column / columnDivision;
enum qualityOfSeat { NON_PREMIUM, PREMIUM };
struct seat {
	bool available=true;
    bool selected = false;
	qualityOfSeat qlt= NON_PREMIUM;
};
struct hall {
	seat s[totalSeat];
};

void initiateHall(hall &h) {
    for (int i = (row - premiumRowSeats) * column; i < totalSeat; i++) {
        h.s[i].qlt = PREMIUM;
    }
}
void drawSeat(int x, int y , colorCode c) {
    int Block = 219;
    gotoxy(x,y);
    highlight(c);
    std::cout << char(Block) << char(Block);//size 1
    resetHighlight();
}

void drawHall(hall &h, int current) {
    int startX = centerX-hallLength/2;
    int x = startX, y = centerY-hallBreadth/2;
    colorCode c= Default_white;
    for (int i = 0; i < totalSeat; i++) {
        if (i == current) c = Bright_blue;
        else if (h.s[i].selected == true) c = Green;
        else if (h.s[i].available == false) c = Red;
        else {
            if (h.s[i].qlt == NON_PREMIUM) c = Default_white;
            else if (h.s[i].qlt == PREMIUM) c = yellow;
        }
        drawSeat(x, y, c);
        if (debug) {
            gotoxy(getConsoleWindowSize().X - 10, y);
            std::cout << i;
        }
        //columnPartition=column/column division 12/4 = 3
        if ((i % columnPartition) == columnPartition - 1) x += corridorGap;
        if (i % column == column - 1) {
            if (i == ((row - premiumRowSeats) * column)-1) y+=3;
            y += 2;
            x = startX;
        }
        else x+=3;
    }
}

/*void controlHallSeat(hall& h) {
    char keyPressed;
    int index=0;
    seat *selected[20];
    int totalSelected=0;
    std::string s = char(37) + char(38) + char(39) + char(40);
    while (true) {
        do {
            keyPressed = _getch();
        } while (
            keyPressed != '"w' = "wasd"
            keyPressed != '\r' && keyPressed != char(27) && keyPressed != char(32));    
                    //      enter                   escape                    space         
        if ((keyPressed == char(38)) && index > column - 1) {
            index -= column;
        }
        if ((keyPressed == char(40)) && index < ((row - 1) * column) - 1) {
            index += column;
        }
        if ((keyPressed == char(37)) && index % row > 0) {
            index -= 1;
        }
        if ((keyPressed == char(39)) && index % row < column - 1) {
            index += 1;
        }
        if (keyPressed == '\r' && h.s[index].selected==false && h.s[index].available == true) {
            h.s[index].selected = true;
            selected[totalSelected] = &h.s[index];
            totalSelected++;
        }
        if (keyPressed == char(27)) {//esc button
            std::cout << "esc";
            //resets array of seats
            for (int i = totalSelected - 1; i >= 0; i++) {
                selected[i]->selected=false;
                selected[i]=NULL;
            }
        }

        drawHall(h, index);
    }
}
*/
#endif