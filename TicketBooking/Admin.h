#pragma once
#include <iostream>
#include <conio.h>
#include <fstream>

#ifndef ADMIN_H
#define ADMIN_H
static const std::string MOVIES_NAME	{"MoviesDetails/Movie.txt"};
static const std::string MOVIES_DETAIL1 {"MoviesDetails/Spiderman Home Coming.txt"};
static const std::string MOVIES_DETAIL2 {"MoviesDetails/Spiderman Away From Home.txt"};
static const std::string MOVIES_DETAIL3 {"MoviesDetails/The Amazing Spiderman.txt"};

static const std::string MOVIES_DETAIL4 {"MoviesDetails/Spiderman Home Coming.txt"};


class Admin {
public:
	void ListOfMovies();
	void CustomerDetails();
};

#endif