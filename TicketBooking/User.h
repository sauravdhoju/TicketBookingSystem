#pragma once

#include "qrcode.hpp"
#include "MenuAndTime.h"
#include "Movies.h"
#include "ConsoleColor.h"
#include <iomanip>
static const std::string USER_FILE {"UserData/users.txt"};
static const std::string ADMIN_FILE {"UserData/admin.txt"};

std::string currentlyLoggedUsername;//imp
struct ticket {
	std::string id;
	std::string movieName;
	int scheduleIndex;
	int seatNo;
	void displayTicket() {
		movie m;
		m = find(movieName);
		printQr(id.c_str(), 10, 10, Black, Default_white);
		int sx=30, sy=10;
		gotoxy(sx, sy);
		std::cout << "Movie Name: " << movieName << "  Ticket Id: " << id;
		gotoxy(sx, sy++);
		std::cout << "Movie StartTime: " << m.schedule[scheduleIndex].startTime.dateString();
		gotoxy(sx, sy++);
		std::cout << "Movie Length: " << m.length;
		std::cout <<"\tValid Seat: " <<std::boolalpha<< (m.schedule[scheduleIndex].s[seatNo].id == this->id);
	}
};

class User {
	//std::vector<ticket> tickets;
	std::string username;
	std::string password;
	std::string phonenumber;
	std::string email;
public:
	User(){}
	User(std::string username, std::string password, std::string phonenumber, std::string email){}
	void CustomerDetails();
    void getUserInfo();
	void Login();
	void checkTickets();
};
