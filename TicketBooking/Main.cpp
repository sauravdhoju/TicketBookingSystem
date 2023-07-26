#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "Title.h"
#include "User.h"
#include "ConsoleSize.h"
#include "seat.h"
#include "Admin.h"
#include "MenuAndTime.h"
#include "Global.h"
#include "Movies.h"
#include "qrcode.hpp"
int actualMain();

int main() {
    std::thread mainThread(actualMain);
   //std::thread timeThread(updatePresentTime);
    //timeThread.join();
    mainThread.join();
    return 0;
}

int actualMain() {
    setConsoleSizeAndCenter();
    int i;
    while (true) {
        do {
            i = rand() % 15;
        } while (i == 7);
        printQr(generateRandomString(12).c_str(), 10, 10, static_cast<colorCode>(i));
    }
    /*std::istringstream iss(ID);
    std::tm t = {};
    iss >> std::get_time(&t, "%y%m%d");
    if (iss.fail()) {
        // do something, like throw an exception ...
    }
    int day = t.tm_mday;
    int month = 1 + t.tm_mon;
    int year = 1900 + t.tm_year;
    std::cout<<year<<"\\" <<month<< "\\" << day;*/
    Admin admin;
    
    /*DateAndTime a =   { 2010,10,4,6,50,36,0 },
                b  =  { 2010,10,4,3,36,40,0  };
	DateAndTime c= timeDiff(a, b);
    std::cout << c.year << ' ' << c.month << ' ' << c.day << ' ' << c.hour << ' ' << c.minute << ' ' << c.second << ' ';
    */
    //admin.CustomerDetails();
    //run h;
    //initiateHall(h);
    //controlHallSeat(h);

    //movie m;
   // m.add();
    //find(movieMenu(search(""), 10, 10)).showPage();*/

    std::string username, password;
    int choice;


    User user;
    Title("Movie-Ticket Booking System", centerY-0);
    
    _getch();
    do {
        system("cls");  presentTime();
        Title("Movie-Ticket Booking System", centerY-7);
        choice = menuInput({"Login", "Register", "Exit"}, centerX-3, centerY-4);

        switch (choice) {
        case 1:
            user.Login();

            break;

        case 2:
            user.getUserInfo();
            break;

        case 3:
            system("cls");
            exit(0);
        }
    } while (choice != 3);

    return 0;
}

// loggedInId = login();