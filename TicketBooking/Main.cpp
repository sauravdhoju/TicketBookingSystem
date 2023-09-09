#include <iostream>
#include <conio.h>
#include <Windows.h>

#include "User.h"
#include "Title.h"
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
    std::thread timeThread(updatePresentTime);
    timeThread.join();
    mainThread.join();
    return 0;
}

int actualMain() {
    setConsoleSizeAndCenter();
    int i;
    
    std::string username, password;
    int choice;

    Admin admin;
    User user;
    Title("Movie-Ticket Booking System", centerY-0);
    
    _getch();
    do {
        system("cls");  presentTime();
        Title("Movie-Ticket Booking System", centerY-7);
        choice = menuInput({"Login", "Register", "Exit"}, centerX-5, centerY-4);

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