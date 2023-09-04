#pragma once

#include "Movies.h"
#include "qrcode.hpp"
#include "MenuAndTime.h"
#include "ConsoleColor.h"
#include <iomanip>
static const std::string USER_FILE {"UserData/users.txt"};
static const std::string ADMIN_FILE {"UserData/admin.txt"};

struct ticket {
	std::string id;
	std::string movieName;
	int scheduleIndex;
	int seatNo;
	void displayTicket(int sx=10, int sy=10);
};

class User {
	std::vector<ticket> tickets;
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
	void loadTickets();
	void displayTickets();
};
