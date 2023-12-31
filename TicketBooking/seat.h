#pragma once

#include<windows.h>
#include"Title.h"
#include"ConsoleColor.h"
#include<conio.h>
#include"ConsoleSize.h"
#include"MenuAndTime.h"
#include "payment.h"

//int debug;
#define row 8// last ko 2 row premium//8,12
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
	char id[10]="";//ends with 2 digit seat number
	bool available=true;
    bool selected = false;
	qualityOfSeat qlt= NON_PREMIUM;
};

struct run {//run a;
	seat s[totalSeat];
	DateAndTime startTime = {0,0, 0, 0, 0, 0 };
	run() {
		for (int i = (row - premiumRowSeats) * column; i < totalSeat; i++) {
			s[i].qlt = PREMIUM;
		}
	}
};

void initiateHall(run& h);
void drawSeat(int x, int y, colorCode c);
 void drawHall(run& h, int current);
 bool controlHallSeat(run& h, std::string, int);
 void payment(run& a, std::string name, std::string MovieName); // Declare the payment function
