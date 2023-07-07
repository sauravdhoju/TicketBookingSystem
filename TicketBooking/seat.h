#pragma once

#ifndef SEAT_H
#define SEAT_H


#include<windows.h>
#include"Title.h"
#include"ConsoleColor.h"
#include<conio.h>
#include"ConsoleSize.h"

//int debug;
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
#endif

#pragma once

#ifndef SEAT_H
#define SEAT_H

#include <windows.h>
#include "Title.h"
#include "ConsoleColor.h"
#include <conio.h>
#include "ConsoleSize.h"

// Structures and function declarations

#endif

void initiateHall(hall& h);
void drawSeat(int x, int y, colorCode c);
void drawHall(hall& h, int current);
void controlHallSeat(hall& h);

