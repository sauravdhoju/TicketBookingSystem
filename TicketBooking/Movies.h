#pragma once

#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <conio.h>
#include "seat.h"

#include "Admin.h"
#include "title.h"
#include "MenuAndTime.h"
#include <fstream>
#include <vector>
#include <string.h>
#include<sstream>
//#include<iomanip>
#include<windows.h>

inline std::string moviesDir = "movies.txt";
inline std::string moviesDetailsDir = "movieDetails\\";
struct location {
    unsigned int start, end;
};


class movie
{
	char name[30];
	
public: run schedule[8];
	movie() {}
	bool update(bool DEL = FALSE);
	bool add();
	friend std::vector<std::string> search(std::string);
	friend location giveLocationFromFile(std::string);
	friend movie find(std::string);
	void modifySchedule();
	void selectSchedule();
	void moviePageForAdmin() {
		system("cls");
		std::cout << std::endl << name << '\n';
		std::ifstream file;
		file.open(moviesDetailsDir + name + "\\synopsis.txt", std::ios::in);
		std::string line;
		int i = 0;
		while (getline(file, line)) {
			std::cout << line << std::endl;
			i++;
		}
		int choice;
		do {
			 choice = menuInput({ "Trailer", "Edit Schedules","Delete", "Back"}, 1, i + 5);
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
				update(TRUE);
				break;
			default: break;
			}
		} while (choice!=4);
	}
	void moviePageForUser() {
		system("cls");
		std::cout << std::endl << name << '\n';
		std::ifstream file;
		file.open(moviesDetailsDir + name + "\\synopsis.txt", std::ios::in);
		std::cout << moviesDetailsDir + name + "\\synopsis.txt";
		std::string line;
		int i = 0;
		while (getline(file, line)) {
			std::cout << line << std::endl;
			i++;
		}
		int choice;
		do {
			int choice = menuInput({ "Trailer", "Book Ticket", "Back" }, 1, i + 5);
			std::string command;
			switch (choice) {
				case 1:
					command = "wmplayer.exe " + moviesDetailsDir + name + "\\trailer.mp4";
					std::cout << std::endl << command;
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
inline std::vector<std::string> search(std::string s = "")
{
	movie m;
	std::vector<std::string> listOfMovies;
	std::string movieName;
	listOfMovies.reserve(32);
	std::ifstream f;
	f.open(moviesDir, std::ios::in);
	if (f.eof()) return {};
	while (f.read((char*)&m, sizeof(m)))
	{
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
	while (true) {
		std::vector <std::string> availableSchedules = {};
		for (int i = 0; i < 9; i++) {
			if (i == 8) availableSchedules.push_back("Exit");
			else if (schedule[i].startTime.year > 0) availableSchedules.push_back(schedule[i].startTime.dateString() + " [" + std::to_string(i) + "]");
			else availableSchedules.push_back("~Empty Schedule Slot");
		}
		int chosedSchedule = menuInput(availableSchedules, 15, 15);
		if (chosedSchedule == 9) break;
		schedule[chosedSchedule].startTime.modifyTime();
		std::cout << "Do you want to Continue? (y/n)";  choice = _getch();
		if (choice == 'n'||choice=='N') break;
	}
	std::cout << update();
	_getch();
}
inline void movie::selectSchedule() {
	std::vector <std::string> availableSchedules;
	std::vector<int> indexOfAvailableSchedules;
	for (int i = 0; i < 8; i++) {
		if (schedule[i].startTime.year > 0) {
			availableSchedules.push_back(schedule[i].startTime.dateString() + " [" + std::to_string(i) + "]");
			indexOfAvailableSchedules.push_back(i);
		}
	}
	if (availableSchedules.size() == 0) {
		std::cout << "No Schedule Available!";
		return;
	}
	std::cout << "all good";
	system("cls"); presentTime();
	int selectedScheduleIndex = indexOfAvailableSchedules.at(menuInput(availableSchedules, 15, 15));
	controlHallSeat(schedule[selectedScheduleIndex]);
}
#endif