#include "seat.h"
#include "Title.h"
#include "User.h"
#include "Global.h"
#include "MenuAndTime.h"
#include "ConsoleColor.h"
#include "ConsoleSize.h"

void wout(const wchar_t* c) {//prints out wide characters
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD written = 0;
	// explicitly call the wide version (which always accepts UTF-16)
	WriteConsoleW(handle, c, 1, &written, NULL);
}

std::string createTicket(std::string username, std::string movieName, int scheduleIndex, int seatNumber) {
	std::ifstream user(USER_FILE, std::ios::in);
	std::ofstream temp(USER_FILE_TEMP, std::ios::out);
	if (!user||!temp) {
		std::cout << "File could not open";
		return "";
	}
	std::string userLine;
	std::string storedUsername;
	std::string ticketId = generateRandomString(6) + std::to_string(scheduleIndex);
	if (seatNumber < 10) ticketId += '0';
	ticketId += std::to_string(seatNumber);
	std::string ticketString = ',' + ticketId + ','+ movieName + ',' + std::to_string(scheduleIndex) + ',' + std::to_string(seatNumber);
	while (std::getline(user, userLine)) {
		std::stringstream iss(userLine);
		std::getline(iss, storedUsername, ',');
		if (storedUsername == username) {
			temp << userLine << ticketString<<'\n';
		}
		else temp << userLine << '\n';
	}
	user.close();
	temp.close();
	std::remove(USER_FILE.c_str());
	std::rename(USER_FILE_TEMP.c_str(), USER_FILE.c_str());
	return ticketId;
}
void User::deleteTicket(ticket t) {
	std::string ticketString = ',' + t.id + ',' + t.movieName + ',' + std::to_string(t.scheduleIndex) + ',' + std::to_string(t.seatNo);
	std::ifstream user(USER_FILE, std::ios::in);
	std::ofstream temp(USER_FILE_TEMP, std::ios::out);
	if (!user || !temp) {
		std::cout << "File could not open";
		return;
	}
	std::string userLine, storedUsername;
	while (std::getline(user, userLine)) {
		std::stringstream iss(userLine);
		std::getline(iss, storedUsername, ',');
		if (storedUsername == username) {
			std::string::size_type i = userLine.find(ticketString);
			if (i != std::string::npos) userLine.erase(i, ticketString.length());
		}
		temp << userLine << '\n';
	}
	user.close();
	temp.close();
	std::remove(USER_FILE.c_str());
	std::rename(USER_FILE_TEMP.c_str(), USER_FILE.c_str());
}

void drawSeat(int x, int y, colorCode c) {
	int Block = 219;
	gotoxy(x, y);
	highlight(c);
	std::cout << char(Block) << char(Block) << " ";//size 1
	resetHighlight();
}

void drawHall(run& h, int current) {
	colorCode c = Default_white;
	int premiumSelected = 0;
	int nonPremiumSelected = 0;
	int totalSelected = 0;

	int startX = centerX - hallLength / 2;
	int x = startX, y = centerY - hallBreadth / 2;
	int sx = (centerX * 2 + (x + hallLength)) / 2 - 9;


	for (int i = 0; i < totalSeat; i++) {
		if (h.s[i].selected == true) {
			if (h.s[i].qlt == PREMIUM) premiumSelected++;
			if (h.s[i].qlt == NON_PREMIUM) nonPremiumSelected++;
			gotoxy(sx, y + totalSelected + 2);
			totalSelected++;
			if (h.s[i].qlt == PREMIUM) highlight(yellow);
			std::cout << "Seat   Number:     ";
			if (i < 10) std::cout << '0';
			std::cout << i;
			resetHighlight();
		}
	}



	int sy = y + 15;
	if (totalSelected == 0) {
		gotoxy(sx, y);
		std::cout << "                              \n";
		for (int i = 0; i < 8; i++) {
			gotoxy(sx, y + i + 2);
			std::cout << "                               ";

		}
		for (int i = 0; i < 3; i++) {
			gotoxy(sx, sy + i);
			std::cout << "                                                      ";
		}
	}


	

	else {
		gotoxy(sx, y);
		std::cout << "Selected Seat List\n";
		gotoxy(sx, sy);
		std::cout << "Normal  : " << nonPremiumSelected << " * Rs " << nonPremiumRate << " = Rs " << nonPremiumSelected * nonPremiumRate;
		gotoxy(sx, sy + 1);
		std::cout << "Premium : " << premiumSelected << " * Rs " << premiumRate << " = Rs " << premiumSelected * premiumRate;
		gotoxy(sx, sy + 2);
		std::cout << "Total   : " << totalSelected << "          = Rs " << nonPremiumSelected * nonPremiumRate + premiumSelected * premiumRate;
	}
	int Block = 219;
	int ssy = y;
	gotoxy(0, ssy-1);

	std::cout << "Normal    Seat      \n\n"
		<< "Premium   Seat      \n\n"
		<< "Booked    Seat      \n\n"
		<< "Selected  Seat      \n\n\n";

	std::cout << "Left		 : "; wout(L"←");
	std::cout << "\nRight	  	 : "; wout(L"→");
	std::cout << "\nUp		 : "; wout(L"↑");
	std::cout << "\nDown		 : "; wout(L"↓");


		std::cout<< "\n\n\nPayment		 : SPACE\n"
		<< "Reset Selection	 : R\n"
		<< "Quit		 : Esc";
	drawSeat(19, ssy-1, Default_white);
	drawSeat(19, ssy-1 + 2, yellow);
	drawSeat(19, ssy-1 + 4, Red);
	drawSeat(19, ssy-1 + 6, Green);



	for (int i = 0; i < totalSeat; i++) {
		if (i == current) c = Bright_blue;
		else if (h.s[i].available == false) c = Red;
		else if (h.s[i].selected == true) c = Green;
		else {
			if (h.s[i].qlt == NON_PREMIUM) c = Default_white;
			else if (h.s[i].qlt == PREMIUM) c = yellow;
		}
		drawSeat(x, y-1, c);
		//columnPartition=column/column division 12/4 = 3
		if ((i % columnPartition) == columnPartition - 1) x += corridorGap;
		if (i % column == column - 1) {
			if (i == ((row - premiumRowSeats) * column) - 1) y += 3;
			y += 2;
			x = startX;
		}
		else x += 3;
	}
}
void resetHallSeat(run& h) {
	for (int i = 0; i < totalSeat; i++) {
		h.s[i].available = true;
		h.s[i].selected = false;
	}
}
bool controlHallSeat(run& h, std::string movieName, int scheduleIndex){
	char keyPressed;
	int index = totalSeat / 2;
	int totalSelected = 0;
	drawHall(h, totalSeat / 2);
	while (true) {
		Title("Movie Ticket Management System", centerY - 12);
		Title("Seat Selection", centerY - 10);
		do {
			keyPressed = _getch();
			if (keyPressed == -32) {
				keyPressed = _getch();
				switch (keyPressed) {
				case 72: // Up arrow
					if (index > column - 1) {
						index -= column;
					}
					break;
				case 80: // Down arrow
					if (index < ((row - 1) * column)) {
						index += column;
					}
					break;
				case 77: // Right arrow
					if (index % column < column - 1) {
						index += 1;
					}
					break;
				case 75: // Left arrow
					if (index % column > 0) {
						index -= 1;
					}
					break;
				}
			}
			else if (keyPressed == '\r' && h.s[index].selected == false && h.s[index].available == true && totalSelected < 8) {
				h.s[index].selected = true;
				totalSelected++;

				gotoxy(centerX - 15, centerY + hallBreadth / 2 + 4);
				std::cout << "                                     ";
			}
			//else if (h.s[index].available == true) {
			//	gotoxy(centerX - 15, centerY + hallBreadth / 2 + 4);
			//	std::cout << "Alert"; wout(L"→"); wout(L"→");
			//	std::cout << " Seat " << (index < 10 ? "0" : "") << index << " is already booked!" << std::endl;
			//	// Redraw the hall without making any changes
			//	drawHall(h, index);
			//}
			else if (keyPressed == 'r'|| keyPressed=='R') {//reset
				for (int i = 0; i < totalSeat; i++) {
					if (h.s[i].selected) {
						h.s[i].selected = false;
					}
				}
			}
			else if (keyPressed == char(32)&& totalSelected>0) {//space button //confirm payment?
				system("cls");
				Title("Are You sure You want to Pay?", centerY);
				int choice = menuInput({ "Yes","No" }, centerX, centerY + 2);
				if (choice == 1) {//yes
					for (int i = 0; i < totalSeat; i++) {
						if (h.s[i].selected) {
							std::string idCode = createTicket(currentlyLoggedUser, movieName, scheduleIndex, i);
							std::strncpy(h.s[i].id, idCode.c_str(), sizeof(idCode));
							h.s[i].selected = false;
							h.s[i].available = false;
						}
					}

					return true;
				}
				else {//No
				}
			}
			else if (keyPressed == char(27)) {//Escape to quit
				return false;
			}
		} while (
			keyPressed != char(72) && keyPressed != char(80) && keyPressed != char(75) && keyPressed != char(77) &&
			keyPressed != '\r' && keyPressed != char(27) && keyPressed != char(32)&&keyPressed!='r'&&keyPressed!='R');
		//      enter                          escape                    space				//rR
		gotoxy(centerX - 11, centerY + hallBreadth / 2+2);
		std::cout << "Currently on Seat No:  ";
		if (index < 10)std::cout << '0';
		std::cout << index;// << " (" << h.s[index].available << h.s[index].selected << ")";
		drawHall(h, index);
	}
}