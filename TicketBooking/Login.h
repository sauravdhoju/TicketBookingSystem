#ifndef LOGIN_H
#define LOGIN_H

static const std::string USER_FILE {"UserData/users.csv"};
static const std::string ADMIN_FILE {"UserData/admin.csv"};

class User {
	int id = 0;
	std::string username;
	std::string password;
	std::string phonenumber;
	std::string email;
	std::string storedUsername, storedPassword;
public:
	void getUserInfo();
	void Login();
	

};

#endif
