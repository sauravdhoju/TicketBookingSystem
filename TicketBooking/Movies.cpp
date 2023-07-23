#include "Movies.h"
#include "Title.h"
#include "ConsoleSize.h"
#include "MenuAndTime.h"
#include "ConsoleColor.h"
#include "seat.h"
#include <fstream>


bool movie::update(bool DEL) {
	location loc = giveLocationFromFile(name);
	if (loc.start > loc.end) {
		std::cout << name << " is not found in file. error!";
		return false;
	}
	std::string beforeObject = "";
	std::string afterObject = "";
	std::ofstream fo;
	std::ifstream fi;
	fi.open("movies.txt", std::ios::in);
	char c;
	while (!fi.eof()) {
		fi.get(c);
		if (fi.tellg() < loc.start) beforeObject += c;
		else if (fi.tellg() > loc.end) afterObject += c;
		else {}
	}
	fi.close();
	fo.open("movies.txt", std::ios::trunc);
	fo << beforeObject;
	if (DEL == false) fo.write((char*)&*this, sizeof(movie));
	fo << afterObject;
	fo.close();
}

bool movie::add() {
	std::cout << "enter Movie Name to add: ";
	std::cin.getline(name, 30);
	std::string fileName = name + ".txt";
	location loc = giveLocationFromFile(name);
	std::cout << loc.start << '-' << loc.end;
	if (loc.start < loc.end) {
		std::cout << name << " already exist in the file";
		return false;
	}
	std::ofstream fo;
	fo.open("movies.txt", std::ios::app);
	fo.write((char*)&*this, sizeof(movie));
	std::string command = "notepad MoviesDetails/" + fileName;
	system(command.c_str());
	fo.close();
	return true;
}
/*

void Movie::showMovies() {
	std::string line;
	int selectedMovieIndex = 0;
	char choice;
	std::ifstream movieFile(MOVIES_NAME);
	std::vector<std::string> movieNames;

	// Read movie names from file
	while (std::getline(movieFile, line)) {
		movieNames.push_back(line);
	}
	movieFile.close();

	do {
		system("cls");
		presentTime();
		Title("Movie-Ticket Booking System", centerY - 12);

		for (int i = 0; i < movieNames.size(); i++) {
			gotoxy(centerX - 30, centerY - 8 + i);
			if (i == selectedMovieIndex) {
				highlightGreen();  // Highlight the selected movie name
			}
			std::cout << i + 1 << ". " << movieNames[i] << std::endl;
			resetHighlight();
		}

		choice = _getch();
		switch (choice) {
		case 72:  // Arrow key: Up
			if (selectedMovieIndex > 0) {
				selectedMovieIndex--;
			}
			break;
		case 80:  // Arrow key: Down
			if (selectedMovieIndex < movieNames.size() - 1) {
				selectedMovieIndex++;
			}
			break;

		case '\r':  // Enter key: Select movie
			if (selectedMovieIndex < movieNames.size()) {
				if (selectedMovieIndex == movieNames.size() - 1) {
					// Go Back option selected
					return;  // Exit the function to go back
				}
				else {
					std::ifstream movieDetailsFile;
					switch (selectedMovieIndex) {
					case 0:
						movieDetailsFile.open(MOVIES_DETAIL1);
						break;
					case 1:
						movieDetailsFile.open(MOVIES_DETAIL2);
						break;
					case 2:
						movieDetailsFile.open(MOVIES_DETAIL3);
						break;
					}
					if (movieDetailsFile.is_open()) {

						std::cout << "\n\n\n";
						std::string line;
						while (getline(movieDetailsFile, line)) {
							std::cout << line << std::endl;
						}
						movieDetailsFile.close();
						do {
							system("cls");  presentTime();
							Title("Movie-Ticket Booking System", centerY - 7);

							int innerchoice = menuInput({"Trailer", "Synopsis", "Book Ticket", "Go back" }, centerX - 3, centerY - 4);

							switch (innerchoice) {
							case 1://trailer
								//milauna baakixa hai
								system("start wmplayer.exe \"F:\cr\KhEC\Third Semester\Project\TicketBookingSystem\TicketBooking\MoviesDetails\Spiderman Home Coming.mp4\"");
								break;
							case 2://synopsis
								system("cls");	presentTime();
								Title("Movie-Ticket Booking System", centerY - 7);
								switch (selectedMovieIndex) {
								case 0:
									movieDetailsFile.open(MOVIES_DETAIL1);
									break;
								case 1:
									movieDetailsFile.open(MOVIES_DETAIL2);
									break;
								case 2:
									movieDetailsFile.open(MOVIES_DETAIL3);
									break;
								}
								//print out movie details
								if (movieDetailsFile.is_open()) {
									system("cls");
									presentTime();
									Title("Movie-Ticket Booking System", centerY - 7);
									//print out movie name
									gotoxy(0, centerY - 5);
									std::cout << movieNames[selectedMovieIndex] << std::endl << std::endl;

									std::string line;
									while (getline(movieDetailsFile, line)) {
										std::cout << line << std::endl;
									}
									movieDetailsFile.close();

								}
								else {
									std::cout << "Unable to open movie details file." << std::endl;
								}

								// Wait for user input to go back
								gotoxy(centerX - 18, centerY + 6);
								std::cout << "Press any key to go back...";
								_getch();
								break;
							case 3: //book ticket
								BookTicket();
								break;
							case 4: // go back
								return;
							}
						} while (choice != 4);
					}
					else {
						std::cout << "Unable to open movie details file." << std::endl;
					}
				}
			}
			break;
		}
	} while (choice != 4);
}


void Movie::BookTicket() {
	system("cls");	presentTime();
	run h;
	initiateHall(h);
	controlHallSeat(h);
}*/
