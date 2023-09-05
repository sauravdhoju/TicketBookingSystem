#include "Movies.h"
#include "Title.h"
#include "ConsoleSize.h"
#include "MenuAndTime.h"
#include "ConsoleColor.h"
#include "seat.h"
#include <fstream>



bool movie::update(bool DEL) {
	location loc = giveLocationFromFile(name);
	//std::cout << loc.start << "," << loc.end;
	if (loc.start > loc.end) {
		std::cout << name << " is not found in file. error!";
		return false;
	}
	std::string beforeObject = "";
	std::string afterObject = "";
	std::ofstream fo;
	std::ifstream fi;
	fi.open(moviesDir, std::ios::in);
	char c;
	movie gl = *this;
	while (!fi.eof()) {
		fi.get(c);
		if (fi.tellg() < loc.start&&loc.start!=0) beforeObject += c;
		else if (fi.tellg() > loc.end) afterObject += c;
		else {}
	}
	fi.close();
	fo.open(moviesDir, std::ios::trunc);
	fo << beforeObject;
	if (DEL == false) {
		fo.write((char*)&gl, sizeof(movie));
	}
	fo << afterObject;
	fo.close();
}

bool movie::add() {
	location loc;
	std::string name_s;
	do {
		system("cls");  presentTime();

		Title("Movie-Ticket Booking System", centerY - 12);
		gotoxy(centerX -30, 12);
		std::cout << "Enter Movie Name to add: ";
		std::cin.getline(name, 30);
		gotoxy(centerX, 6);
		name_s = name;
		loc = giveLocationFromFile(name);
		if (loc.start < loc.end) {
			std::cout << name << " already exist in the file"; _getch();
		}
		if (name_s.length() < 1) {
			std::cout << "Enter valid name"; _getch();
		}
	} while (loc.start < loc.end || name_s.length() < 1);
	std::ofstream fo;
	fo.open(moviesDir, std::ios::app);
	fo.write((char*)&*this, sizeof(movie));
	std::string command = "mkdir \"" + moviesDetailsDir + name+'\"';
	system(command.c_str());
	command = "notepad "+ moviesDetailsDir + name +"\\synopsis.txt";
	system(command.c_str());
	fo.close();
	return true;
}
