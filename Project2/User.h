// User.h
#pragma once
#include <string>

class User {
private:
	std::string username;
	std::string firstName;
	std::string lastName;
	std::string email;
	std::string password;

public:
	User(std::string username, std::string firstName, std::string lastName, std::string email, std::string password);

	// CRUD methods
	static bool InsertUser(std::string username, std::string firstName, std::string lastName, std::string email, std::string password);
	static User* GetUserByUsername(std::string username);
	bool UpdateUser();
	bool DeleteUser();

	// Getters and Setters
	std::string GetUsername();
	std::string GetFirstName();
	std::string GetLastName();
	std::string GetEmail();
	std::string GetPassword();
};
