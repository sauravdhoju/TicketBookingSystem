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

//rose push
//r
 //bool debug = true;
int actualMain();

int main() {
    terminateProgram = false;
    std::thread mainThread(actualMain);
    std::thread timeThread(updatePresentTime);
    timeThread.join();
    mainThread.join();
    return 0;
}

int actualMain() {
    setConsoleSizeAndCenter();
    
    Admin admin;
    //admin.CustomerDetails();
    //hall h;
    //initiateHall(h);
    //controlHallSeat(h);
   
    std::string username, password;
    int choice;

    User user;
    Title("Movie-Ticket Booking System", centerY);
    _getch();
    do {
        system("cls");  presentTime();
        Title("Movie-Ticket Booking System", centerY - 4);
        Title("1. Login", centerY);
        Title("   2. Register", centerY + 1);
        Title("3. Exit", centerY + 2);

        choice =menuInput(centerY, 73, 3);

        switch (choice) {
        case 1:
            system("cls");  presentTime();
            Title("Movie-Ticket Booking System", centerY - 12);
            Title("LOGIN", centerY - 8);
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
            terminateProgram = true;
            system("cls");
            system("exit");
            //exit(0);
            return 0;
        }
    } while (true);

    return 0;
}