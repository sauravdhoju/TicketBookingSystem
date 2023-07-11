#pragma once

#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <conio.h>

#include "Admin.h"

class Movies {
	std::string movieName;
	unsigned int id;
	//DateAndTime startTime, endTime;
public:
	void showMovies();
	void BookTicket();
};
#endif