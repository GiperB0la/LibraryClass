#ifndef BOOK_H
#define BOOK_H

#include "Header.h"

class Book
{
public:
	friend Library;
	friend User;
	Book(string nameBook, string author, int year) : nameBook(nameBook), author(author), year(year) {}
	~Book() {}

	void printInfo(bool flagName);

private:
	string nameBook, author;
	int year;
};

#endif