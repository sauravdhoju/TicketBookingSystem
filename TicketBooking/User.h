#pragma once

#include "qrcode.hpp"
#include "MenuAndTime.h"
#include "ConsoleColor.h"
static const std::string USER_FILE {"UserData/users.txt"};
static const std::string ADMIN_FILE {"UserData/admin.txt"};


struct ticket {
	char movieName[30]="";
	DateAndTime startTime;
	int seatNo;
	void displayTicket() {
		std::string qrText = movieName[2] + generateRandomString(2) + movieName[1];
		if(seatNo<10) qrText += '0';
		qrText += std::to_string(seatNo) + movieName[3];
		if (startTime.day < 10) qrText += '0';
		qrText += std::to_string(startTime.day);
		if (startTime.month < 10) qrText += '0';
		qrText += std::to_string(startTime.month);

		//printQr(qrText.c_str(), 10, 10, Black);
		std::cout << "Movie Name: " << movieName << "  Ticket Id: " << qrText << std::endl;
		std::cout << "Movie StartTime: " << startTime.dateString();
	}
};

class User {
	int id=0 ;
	ticket tickets[20];
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
};
