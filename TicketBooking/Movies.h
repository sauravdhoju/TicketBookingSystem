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
#include<iomanip>
#include<windows.h>

#define totalSeat 96

struct location {
    unsigned int start, end;
};


class movie
{
    char name[30];
    run schedule[8];
public:
    movie() {}
    bool update(bool DEL=FALSE);
    bool add();
    friend std::vector<std::string> search(std::string);
    friend location giveLocationFromFile(std::string);
    friend movie find(std::string);
    void showPage() {
        std::cout << std::endl << name << '\n';
		std::ofstream o.open("MoviesDetails/"+name, std::ios::out);
		while(!o.eof()){}/*********/
        int choice = menuInput({"Trailer", "Book Ticket", "Delete"}, 15, 15);
        switch (choice) {
        case 1:
            break;
        case 2:
            int index;
            std::cin >> index;
            controlHallSeat(schedule[index]);
            update();
            break;

        case 3:
            update(TRUE);
            break;
        default: break;
        }
    }
    
};


inline movie find(std::string s) {
	movie m;
	std::ifstream f;
	f.open("movies.txt", std::ios::in);
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
	f.open("movies.txt", std::ios::in);
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
inline location giveLocationFromFile(std::string n)
{
	movie m;
	location loc;
	std::ifstream f;
	f.open("movies.txt", std::ios::in);
	if (f.tellg() < 0) return{ 401,0 };
	while (!f.eof()) {
		std::cout << f.tellg() << std::endl;
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
				//  highlightGreen();
				std::cout << cursor;
			}
			else std::cout << " ";
			std::cout << i + 1 << ". " << options.at(i);
			//resetHighlight();
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
#endif