

#include <iostream>
#include <conio.h>
#include <Windows.h>
extern bool debug = true;
#include "Title.h"
#include "User.h"
#include "ConsoleSize.h"
#include "seat.h"
#include "Admin.h"
#include "MenuAndArrow.h"


int main() {
    setConsoleSizeAndCenter();
    Admin admin;
    //admin.CustomerDetails();
    //hall h;
    //initiateHall(h);
   // controlHallSeat(h);
   
    std::string username, password;
    int choice;

    User user;
    Title("Movie-Ticket Booking System", centerY);
    _getch();
    do {
        system("cls");
        Title("Movie-Ticket Booking System", centerY - 4);
        Title("1. Login", centerY);
        Title("   2. Register", centerY + 1);
        Title("3. Exit", centerY + 2);

      //  gotoxy(centerX, centerY + 4);
        choice =menuInput(centerY, 73, 3);
        //arrow(FirstEnter, FirstUp, FirstDown);
        switch (choice) {
        case 1:
            system("cls");
            Title("Movie-Ticket Booking System", centerY - 12);
            Title("LOGIN", centerY - 8);
            user.Login();
            break;

        case 2:
            system("cls");
            Title("Movie-Ticket Booking System", centerY - 12);
            Title("CREATE ACCOUNT", centerY - 8);
            user.getUserInfo();
            std::cout << "Registration Successfull";
            break;

        }
    } while (choice != 3);

    return 0;
}