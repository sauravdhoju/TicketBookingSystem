
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>

#include "Admin.h"
#include "Title.h"
#include "ConsoleSize.h"
#include "ConsoleColor.h"
#include "User.h"
#include "MenuAndTime.h"

void Admin::ListOfMovies() {
	char choice;
	std::string line;
	/*do {
		system("cls");  presentTime();
		Title("Movie-Ticket Booking System", centerY - 12);
		std::vector<std::string> movieNames = {
		"Spiderman Home Coming",
		"Spiderman Away From Home",
		"The Amazing Spiderman",
		"MainMenu"
		};
		for (int i = 0; i < movieNames.size(); i++) {
			gotoxy(centerX - 30, centerY - 8 - i);
			std::cout << i + 1 << ". " << movieNames[i] << std::endl;
		}

		std::cout << movieNames.size() + 1 << std::endl;

		/*Title("Movie-Ticket Booking System", centerY - 12);
		gotoxy(centerX - 30, centerY - 8);
		std::cout << "List of Movies";
		gotoxy(centerX - 30, centerY - 8);
		std::cout << "1. Spiderman Home Coming\n";
		gotoxy(centerX - 30, centerY - 7);
		std::cout << "2. Spiderman Away From Home\n";
		gotoxy(centerX - 30, centerY - 6);
		std::cout << "3. The Amazing Spiderman\n";
		gotoxy(centerX - 30, centerY - 5);
		std::cout << "4. Main Menu\n";
		*/
		/*std::fstream file;
		std::string command;
		choice = menuInput(movieNames, centerY - 8, centerX - 30 - 1);

		switch (choice) {
		case 1:
			command = "notepad " + MOVIES_DETAIL1;
			system(command.c_str());
			break;

		case 2:
			command = "notepad " + MOVIES_DETAIL2;
			system(command.c_str());
			break;

		case 3:
			command = "notepad " + MOVIES_DETAIL3;
			system(command.c_str());
			break;
		}
	} while (choice != 4);*/
}

void Admin::CustomerDetails() {
	
	int id1;
	std::cout << "Customer Details";
	std::ofstream file(USER_FILE, std::ios::in);
	std::cout << "ID? ";
	std::cin >> id1;
	if (!file.is_open()) {
		std::cout << "File could not open\n";
	}
	else {
		//search
		
	}
	_getch();
}