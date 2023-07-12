#pragma once

#ifndef MOVIES_H
#define MOVIES_H

#include <iostream>
#include <conio.h>
#include "seat.h"

#include "Admin.h"

class Movie {
	char movieName[30];
	unsigned int id;
	run r[10];
	//DateAndTime startTime, endTime;
public:
	void showMovies();
	void moviePage();

	void BookTicket();
};
#endif