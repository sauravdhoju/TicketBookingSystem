#pragma once

#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <conio.h>
#include "seat.h"

#include "Admin.h"
#include "title.h"
#include "user.h"
#include "MenuAndTime.h"
#include <fstream>
#include <vector>
#include <string.h>
#include<sstream>
//#include<iomanip>
#include<iterator>
#include<windows.h>

inline std::string moviesDir = "movies.txt";
inline std::string moviesDetailsDir = "movieDetails\\";
struct location {
    unsigned int start, end;
};

inline location giveLocationFromFile(std::string n);

class movie{
	char name[30];
	int length=0;//in minute
	run schedule[8];
public: 
	movie() { length = 0; }
	movie(char* n, run* sc) {
		for (int i = 0; i < 30; i++) {
			name[i] = n[i];
			if (i < 8) schedule[i] = sc[i];
		}
	}
	bool update(bool DEL = FALSE);
	bool add();
	friend std::vector<std::string> search(std::string);
	friend location giveLocationFromFile(std::string);
	friend movie find(std::string);
	friend class ticket;
	void modifySchedule();
	void selectSchedule();
	void modifyLength() {
		while (true) {
			system("cls");  presentTime();
			std::cout << "Change Movie Length from "<<length<<" minutes to:";
			std::cin >> length;
			if (length <= 0 || length > 300) {
				std::cout << "give proper movie length(1-300 mins)!!";
			}
			else break;
		}
		update();
	}
	void moviePageForAdmin() {
		int choice;
		do {
			system("cls");  presentTime();
			Title(name, 3);
			std::ifstream file;
			file.open(moviesDetailsDir + name + "\\synopsis.txt", std::ios::in);
			std::string word;
			int lineCount = 1;
			int letterCountInALine = 0;
			std::cout << "\n\n";
			bool hasEnteredNewLine=false;
			while (getline(file, word, ' ')) {
				std::cout << word << ' ';
				if (letterCountInALine >= 105) {
					std::cout << std::endl;
					letterCountInALine = 0;
					lineCount++;
				}
				letterCountInALine += word.length() + 1;
			}
			std::cout << lineCount;
			 choice = menuInput({ "Trailer","Modify Schedule", "Modify Length","Delete", "Back"}, centerX - 48, lineCount + 7);// 1, i + 5
			std::string command;
			switch (choice) {
			case 1:
				command = "vlc.exe \"" + moviesDetailsDir + name + "\"\\trailer.mp4";
				gotoxy(centerX - 7, centerY);
				std::cout << "opening " << name << "'s trailer...";
				system(command.c_str());
				break;
			case 2:
				modifySchedule();
				break;
			case 3:
				modifyLength();
				break;

			case 4:
				update(true);
				return;
			case 5:
				return;
				break;
			default: break;
			}
		} while (choice!=5);
	}
	void moviePageForUser() {
		int choice;
		do {
			system("cls");  presentTime;

			Title(name, centerY - 7);
			gotoxy(0, 3);
			std::cout << "Synopsis\n";

			std::ifstream file;
			file.open(moviesDetailsDir + name + "\\synopsis.txt", std::ios::in);
			std::string word;
			int i = 0;
			std::cout << "\n\n";
			while (getline(file, word, ' ')) {
				std::cout << word << ' ';
				if (i % 14 == 0) std::cout << std::endl;
				i++;
			}
			
			choice = menuInput({ "Trailer", "Book Ticket", "Back" }, centerX - 48, i+centerY - 4);// 1, i + 5
			std::string command;
			switch (choice) {
				case 1:
					command = "vlc.exe \"" + moviesDetailsDir + name + "\"\\trailer.mp4";
					gotoxy(centerX - 7, centerY);
					std::cout << "opening " << name << "'s trailer...";
					system(command.c_str());
					break;
				case 2://Schedules
					selectSchedule();
					break;

				default: break;
			}
		} while (choice != 3);	
	}
};



inline movie find(std::string s) {
	movie m;
	std::ifstream f;
	f.open(moviesDir, std::ios::in);
	while (f.read((char*)&m, sizeof(m)))
	{
		if (s == m.name) return m;
	}
	f.close();
	std::cout << "ERROR!!! file couldn't find";
	return m;
}
inline std::vector<std::string> search(std::string s = ""){
	movie m;
	std::vector<std::string> listOfMovies;
	std::string movieName;
	listOfMovies.reserve(32);
	std::ifstream f;
	f.open(moviesDir, std::ios::in);
	if (f.eof()) return {};
	while (f.read((char*)&m, sizeof(m))){
		//std::cout <<m.name<< "\n" << f.tellg();
		movieName = m.name;
		if (s == "" || movieName.find(s) != std::string::npos) listOfMovies.push_back(m.name);
	}
	f.close();
	return listOfMovies;
}
inline location giveLocationFromFile(std::string n){
	movie m;
	location loc;
	std::ifstream f;
	f.open(moviesDir, std::ios::in);
	if (f.tellg() < 0) return{ 401,0 };
	while (!f.eof()) {
		loc.start = f.tellg();
		f.read((char*)&m, sizeof(m));
		loc.end = f.tellg();
		if (m.name == n) break;
		else if (f.eof()) return { 909,000 };
	}
	f.close();
	if (m.name == n) return loc;
}


inline std::string movieMenu(std::vector<std::string> options, int startX, int startY, char cursor = '>') {
	if (options.size() == 0) return "";
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
			return options[choice - 1];
		}
	} while (true);
}

inline void movie::modifySchedule() {
	char choice;
	system("cls");  presentTime();

	Title("Movie-Ticket Booking System", centerY - 12);
	Title("Schedules", centerY - 9);
	while (true) {
		std::vector <std::string> availableSchedules = {};
		for (int i = 0; i < 8; i++) {
			if (schedule[i].startTime.year > 0) availableSchedules.push_back(schedule[i].startTime.dateString());
			else availableSchedules.push_back("~Empty Schedule Slot");
		}
		availableSchedules.push_back("Back");
		int chosedSchedule = menuInput(availableSchedules, centerX - 48, centerY - 4);
		if (chosedSchedule == 9) return;
		schedule[chosedSchedule-1].startTime.modifyTime();
		update();
		std::cout << "Do you want to Continue? (y/n)";  choice = _getch();
		if (choice == 'n'||choice=='N') break;
	}

}
inline void movie::selectSchedule() {
	std::vector <std::string> availableSchedules;
	std::vector<int> indexOfAvailableSchedules;
	for (int i = 0; i < 8; i++) {
		if (schedule[i].startTime.year > 0) {
			availableSchedules.push_back("Starts at: " + schedule[i].startTime.dateString());
			indexOfAvailableSchedules.push_back(i);
		}
	}
	availableSchedules.push_back("Back");
	std::cout << "all good";
	system("cls"); presentTime();
	Title("Movie-Ticket Management System", centerY - 12);
	Title("Available Schedules", centerY - 9);
	int i = menuInput(availableSchedules, centerX - 48, centerY - 4) - 1;
	if (i == availableSchedules.size() - 1) return;
	int selectedScheduleIndex = indexOfAvailableSchedules.at(i);

	system("cls"); presentTime();
	controlHallSeat(schedule[selectedScheduleIndex], name, selectedScheduleIndex);
	
	update();
}
#endif