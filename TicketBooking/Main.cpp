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
    std::thread timeThread(updatePresentTime);
    timeThread.join();
    mainThread.join();
    return 0;
}

int actualMain() {
    setConsoleSizeAndCenter();
    /*int i;
    while (true) {
        do {
            i = rand() % 15;
        } while (i == 7);
        printQr(generateRandomString(12).c_str(), 10, 10, static_cast<colorCode>(i));
    }*/

    //printQr("rise is god", 10, 10, Black);


    //movie m;
    //m.add();
    //find(movieMenu(search(""), 10, 10));
    //m.schedule[0].startTime.modifyTime();
    //m.update();
    //find(movieMenu(search(""), 10, 10));
    ////m.selectSchedule();
    //_getch();

    std::string username, password;
    int choice;

    Admin admin;
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