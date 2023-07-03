#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>

#ifndef ADMIN_H
#define ADMIN_H

static const std::string MOVIES_DETAIL1 {"MoviesDetails/Spyderman_home_homecoming.txt"};
static const std::string MOVIES_DETAIL2 {"MoviesDetails/Spiderman_away_from _home.txt"};
static const std::string MOVIES_DETAIL3 {"MoviesDetails/The_amazing_spiderman.txt"};

class Admin {
public:
	void ListOfMovies();
	void CustomerDetails();
};

#endif