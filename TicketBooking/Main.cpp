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

 //bool debug = true;
int actualMain();

int main() {
    std::thread mainThread(actualMain);
    std::thread timeThread(updatePresentTime);
    timeThread.join();
    mainThread.join();
    return 0;
}

int actualMain() {
    setConsoleSizeAndCenter();
    
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
            system("cls");  presentTime();
            user.Login();
            break;

        case 2:
            system("cls");  presentTime();
            Title("Movie-Ticket Booking System", centerY - 12);
            Title("CREATE ACCOUNT", centerY - 8);
            user.getUserInfo();
            std::cout << "Registration Successfull";
            break;

        case 3:
            system("cls");
            system("exit");
            //exit(0);
            return 0;
        }
    } while (true);

    return 0;
}