#pragma once

#include "Movies.h"
#include "qrcode.hpp"
#include "MenuAndTime.h"
#include "ConsoleColor.h"
#include <iomanip>
static const std::string USER_FILE {"UserData/users.txt"};
static const std::string USER_FILE_TEMP {"UserData/usersTemp.txt"};
static const std::string ADMIN_FILE {"UserData/admin.txt"};

//inline std::string currentlyLoggedUser;
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
	User(std::string username){
		this->username = username;
	}
	friend void findUserDetails();
	void CustomerDetails(int);
    void getUserInfo();
	void Login();
	bool loadTicketsAndOtherInfo();
	void displayTickets(bool adminControl =false);
	void deleteTicket(ticket);
};
