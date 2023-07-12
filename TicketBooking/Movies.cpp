#include "Movies.h"
#include "Title.h"
#include "ConsoleSize.h"
#include "MenuAndTime.h"
#include "ConsoleColor.h"
#include "seat.h"
#include <fstream>

void Movie::showMovies() {
	int choice;
	


	system("cls"); presentTime();
	/*//Title("Movie-Ticket Booking System", centerY - 12);
	gotoxy(centerX-8, centerY - 12);
	std::cout << ("Movie-Ticket Booking System\n");
	gotoxy(centerX-2, centerY - 8);
	std::cout << "Premiere Movies\n";

	gotoxy(centerX - 30, centerY - 4);
	std::cout << "1. Spiderman Home Coming\n";
	gotoxy(centerX - 30, centerY - 3);
	std::cout << "2. Spiderman Away From Home\n";
	gotoxy(centerX - 30, centerY - 2);
	std::cout << "3. The Amazing Spiderman\n";
	gotoxy(centerX - 30, centerY - 1);
	std::cout << "4. Main Menu\n";
	
	choice = menuInput(centerY - 4, centerX - 31, 4);
	do {
		std::string line;
		std::ifstream Movie1;
		switch (choice) {
		case 1:	
			system("cls"); presentTime();
			
			Movie1.open(MOVIES_DETAIL1, std::ios::out);

			if (Movie1.is_open()) {
				gotoxy(centerX - 13, centerY - 12);
				std::cout << ("Movie-Ticket Booking System");
				gotoxy(centerX - 10, centerY - 11);
				std::cout << "Spiderman Home Coming";
				
				gotoxy(1, centerY - 9);
				std::cout << "1. Synopsis";
				gotoxy(1, centerY - 8);
				std::cout << "2. Book Ticket";
				gotoxy(1, centerY - 7);
				std::cout << "3. Menu\n\n";
				int ch;
				ch = menuInput(centerY - 9, 0, 3);

				switch (ch) {
				case 1:
					while (std::getline(Movie1, line)) {
						std::cout << line << "\n";
					}
					_getch();
					Movie1.close();
					break;
				case 2:
					system("cls"); presentTime();
					gotoxy(centerX - 13, centerY - 12);
					std::cout << ("Movie-Ticket Booking System");
					gotoxy(centerX - 10, centerY - 11);
					std::cout << "Spiderman Home Coming";
					BookTicket();
					break;
				case 3:
					break;
				}
			}
			else std::cout << "Cannot open file\n";
			

			
			break;
		case 2:
			system("cls"); presentTime();
			break;
		case 3:
			system("cls"); presentTime();
			break;
		}
	} while (choice != 4);*/
}
void Movie::BookTicket() {
	run h;
	initiateHall(h);
	controlHallSeat(h);

}
