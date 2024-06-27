#ifndef LIBRARY_H
#define LIBRARY_H

#include "Header.h"

class Library
{
public:
	friend Book;
	friend User;
	Library() {}
	~Library() {}

	void addBook(string nameBook, string author, int year);

	void printArrBooks(bool flagName);

	static void printMainInfo();

	static void printHelloUser(string name);

	static void mainMenu(Library& library, User* user, string& login, bool& mainFlag);

	static void menuUser(Library& library, User* user, string& login, bool mainFlag);

private:
	vector<Book> books;
};

#endif