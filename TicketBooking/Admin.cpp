#include "Admin.h"
#include "Title.h"
#include "ConsoleSize.h"
#include "ConsoleColor.h"
#include "User.h"
#include <iostream>
#include <conio.h>
#include <fstream>
#include <string>

void Admin::ListOfMovies() {
	char choice;
	std::string line;
	do {
		system("cls");
		
		Title("Movie-Ticket Booking System", centerY - 12);
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
		choice = _getch();

		if (choice == '1') {
			highlightGreen();
			gotoxy(centerX - 30, centerY - 8);
			std::cout << "1. Spiderman Home Coming\n";
			resetHighlight();
		}
		else if (choice == '2') {
			highlightGreen();
			gotoxy(centerX - 30, centerY - 7);
			std::cout << "2. Spiderman Away From Home\n";
			resetHighlight();
		}
		else if (choice == '3') {
			highlightGreen();
			gotoxy(centerX - 30, centerY - 6);
			std::cout << "3. The Amazing Spiderman\n";
			resetHighlight();
		}
		else if(choice == '4') {
			highlightGreen();
			gotoxy(centerX - 30, centerY - 5);
			std::cout << "4. Main Menu\n";
			resetHighlight();
		}
		std::fstream file;
		std::string command;
		switch (choice) {
		case '1':
			command = "notepad " + MOVIES_DETAIL1;
			system(command.c_str());
			break;

		case '2':
			command = "notepad " + MOVIES_DETAIL2;
			system(command.c_str());
			break;

		case '3':
			command = "notepad " + MOVIES_DETAIL3;
			system(command.c_str());
			break;
		}
	} while (choice != '4');
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