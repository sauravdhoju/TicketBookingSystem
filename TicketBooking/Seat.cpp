﻿#include "seat.h"
#include "Title.h"
#include "MenuAndTime.h"
#include "ConsoleColor.h"
#include "ConsoleSize.h"

void initiateHall(run& h) {
	for (int i = (row - premiumRowSeats) * column; i < totalSeat; i++) {
		h.s[i].qlt = PREMIUM;
	}
}
void drawSeat(int x, int y, colorCode c) {
	int Block = 219;
	gotoxy(x, y);
	highlight(c);
	std::cout << char(Block) << char(Block) << " ";//size 1
	resetHighlight();
}

void drawHall(run& h, int current) {
	colorCode c = Default_white;
	int premiumSelected = 0;
	int nonPremiumSelected = 0;
	int totalSelected = 0;

	int startX = centerX - hallLength / 2;
	int x = startX, y = centerY - hallBreadth / 2;
	int sx = (centerX * 2 + (x + hallLength)) / 2 - 9;


	for (int i = 0; i < totalSeat; i++) {
		if (h.s[i].selected == true) {
			if (h.s[i].qlt == PREMIUM) premiumSelected++;
			if (h.s[i].qlt == NON_PREMIUM) nonPremiumSelected++;
			gotoxy(sx, y + totalSelected + 2);
			totalSelected++;
			if (h.s[i].qlt == PREMIUM) highlight(yellow);
			std::cout << "Seat   Number:     ";
			if (i < 10) std::cout << '0';
			std::cout << i;
			resetHighlight();
		}
	}

	int sy = y + 15;
	if (totalSelected == 0) {
		gotoxy(sx, y);
		std::cout << "                              \n";
		for (int i = 0; i < 8; i++) {
			gotoxy(sx, y + i + 2);
			std::cout << "                               ";

		}
		for (int i = 0; i < 3; i++) {
			gotoxy(sx, sy + i);
			std::cout << "                                                      ";
		}
	}
	else {
		gotoxy(sx, y);
		std::cout << "Selected Seat List\n";
		gotoxy(sx, sy);
		std::cout << "Normal  Seats:     " << nonPremiumSelected << " * Rs " << nonPremiumRate << " = Rs " << nonPremiumSelected * nonPremiumRate;
		gotoxy(sx, sy + 1);
		std::cout << "Premium Seats:     " << premiumSelected << " * Rs " << premiumRate << " = Rs " << premiumSelected * premiumRate;
		gotoxy(sx, sy + 2);
		std::cout << "Total        :     " << totalSelected << "          = Rs " << nonPremiumSelected * nonPremiumRate + premiumSelected * premiumRate;
	}
	int Block = 219;
	int ssy = y;
	gotoxy(0, ssy);
	std::cout << "Normal    Seat      \n\n"
		<< "Premium   Seat      \n\n"
		<< "Booked    Seat      \n\n"
		<< "Selected  Seat      \n\n\n\n\n"
		<< "Cancel Selection :   ESC\n"
		<< "Payment :            SPACE\n";
	drawSeat(19, ssy, Default_white);
	drawSeat(19, ssy + 2, yellow);
	drawSeat(19, ssy + 4, Red);
	drawSeat(19, ssy + 6, Green);

	/*
	gotoxy(0, 0);
	std::cout << char(24) << char(27) << char(25) << char(26);

	std::cout << " W " << char(24);gotoxy(0, y + 11);
	std::cout << " A " << char(27);gotoxy(0, y + 12);
	std::cout << " S " << char(25);gotoxy(0, y + 13);
	std::cout << " D " << char(26);
	*/

	for (int i = 0; i < totalSeat; i++) {
		if (i == current) c = Bright_blue;
		else if (h.s[i].selected == true) c = Green;
		else if (h.s[i].available == false) c = Red;
		else {
			if (h.s[i].qlt == NON_PREMIUM) c = Default_white;
			else if (h.s[i].qlt == PREMIUM) c = yellow;
		}
		drawSeat(x, y, c);
		//columnPartition=column/column division 12/4 = 3
		if ((i % columnPartition) == columnPartition - 1) x += corridorGap;
		if (i % column == column - 1) {
			if (i == ((row - premiumRowSeats) * column) - 1) y += 3;
			y += 2;
			x = startX;
		}
		else x += 3;
	}
}
void confirmPayment(run& h) {
	system("cls");
	Title("Are You sure You want to Pay?", centerY);
	int choice = menuInput({ "Yes","No" }, centerX, centerY + 2);
	if (choice == 1) {//yes
		//payemetn fucntion
	}
	else {//No
		system("cls");
		controlHallSeat(h);
	}
}
void controlHallSeat(run& h) {
	char keyPressed;
	int index = totalSeat / 2;
	int totalSelected = 0;
	drawHall(h, totalSeat / 2);
	while (true) {
		do {
			keyPressed = _getch();
			if (keyPressed == -32) {
				keyPressed = _getch();
				switch (keyPressed) {
				case 72: // Up arrow
					if (index > column - 1) {
						index -= column;
					}
					break;
				case 80: // Down arrow
					if (index < ((row - 1) * column)) {
						index += column;
					}
					break;
				case 77: // Right arrow
					if (index % column < column - 1) {
						index += 1;
					}
					break;
				case 75: // Left arrow
					if (index % column > 0) {
						index -= 1;
					}
					break;
				}
			}
			else if (keyPressed == '\r' && h.s[index].selected == false && h.s[index].available == true && totalSelected < 8) {
				h.s[index].selected = true;
				totalSelected++;
			}
			else if (keyPressed == char(27)) {//esc button
				for (int i = 0; i < totalSeat; i++) {
					if (h.s[i].selected) {
						h.s[i].selected = false;
					}
				}
			}
			else if (keyPressed == char(32)) {//space button
				confirmPayment(h);
			}
		} while (
			keyPressed != char(72) && keyPressed != char(80) && keyPressed != char(75) && keyPressed != char(77) &&
			keyPressed != '\r' && keyPressed != char(27) && keyPressed != char(32));
		//      enter                          escape                    space   
		gotoxy(centerX - 11, centerY + hallBreadth / 2 + 5);
		std::cout << "Currently on Seat No:  ";
		if (index < 10)std::cout << '0';
		std::cout << index;
		drawHall(h, index);
	}
}



