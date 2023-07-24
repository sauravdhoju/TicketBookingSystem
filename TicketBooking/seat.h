#pragma once

#ifndef SEAT_H
#define SEAT_H


#include<windows.h>
#include"Title.h"
#include"ConsoleColor.h"
#include<conio.h>
#include"ConsoleSize.h"
#include"MenuAndTime.h"

//int debug;
#define row 8// last ko 2 row premium
#define column 12// 4 division
#define totalSeat row*column
#define hallLength 2*column+(column-1)//gap ko value 1
#define hallBreadth row+(row-1)
#define corridorGap 3
#define columnDivision 4
#define premiumRowSeats 2

#define nonPremiumRate 220
#define premiumRate 410
#define seatLimit 4

const int columnPartition = column / columnDivision;

enum qualityOfSeat { NON_PREMIUM, PREMIUM };

struct seat {
	bool available=true;
    bool selected = false;
	qualityOfSeat qlt= NON_PREMIUM;
};

struct run {//run a;
	seat s[totalSeat];
	DateAndTime startTime = {0,0, 0, 0, 0, 0 };
};

void initiateHall(run& h);
void drawSeat(int x, int y, colorCode c);
 void drawHall(run& h, int current);
 void controlHallSeat(run& h);
 void payment(run& a, std::string name, std::string MovieName); // Declare the payment function

#endif