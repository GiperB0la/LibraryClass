#ifndef USER_H
#define USER_H

#include "Header.h"
#include "Book.h"

class User
{
public:
	friend Library;
	friend Book;
	User(string login) : login(login) { pathMyFolder = PATH + login; }
	~User() {}

	void listBooks(bool flagName);

	void initializing();

	void takeBook(string pathMyFolder);

	void returnBook(string pathMyFolder);

	static void registration(string newFolderPath, string login);

	static int entrance(string& login);

private:
	string login, pathMyFolder;
	vector<Book> myListBooks;
};

#endif