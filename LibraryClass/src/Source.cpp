#include "Header.h"
#include "User.h"
#include "Book.h"
#include "Library.h"


Library library;


// ------- Book -------


void Book::printInfo(bool flagName)
{
	if (!flagName) {
		cout << "Book: " << this->nameBook << endl;
		cout << "Author: " << this->author << endl;
		cout << "Year of publication: " << this->year << endl;
		cout << endl;
	}
	else
		cout << "Book: " << this->nameBook << endl;

}


// ------- Library -------


void Library::addBook(string nameBook, string author, int year)
{
	books.push_back(Book(nameBook, author, year));
}

void Library::printArrBooks(bool flagName)
{
	cout << "List books in library:" << endl;
	cout << "=====================" << endl;
	int i = 1;
	for (Book& book : this->books) {
		cout << i << ". ";
		book.printInfo(flagName);
		i++;
	}
}

void Library::printHelloUser(string name)
{
	cout << "Hello, " << name << "." << endl;
	cout << "'p' - List of books in the library()" << endl;
	cout << "'t' - My list of books()" << endl;
	cout << "'d' - Take a book()" << endl;
	cout << "'s' - Return of books()" << endl;

	cout << "'c' - Clear()" << endl;
	cout << "'x' - Exit the menu()" << endl;
}

void Library::printMainInfo()
{
	cout << "Welcome to the library!" << endl;
	cout << "'p' - List of books in the library()" << endl;
	cout << "'l' - Log in to the system()" << endl;

	cout << "'c' - Clear()" << endl;
	cout << "'x' - Exit()" << endl;
}


// ------- User -------

void User::initializing()
{
	if (!(fs::is_empty(this->pathMyFolder))) {
		for (const auto& entry : fs::directory_iterator(this->pathMyFolder)) {
			vector <string> book;
			if (fs::is_regular_file(entry)) {
				ifstream inFile(entry.path());
				string line;
				while (getline(inFile, line)) {
					book.push_back(line);
				}
			}

			this->myListBooks.push_back(Book(book.at(0), book.at(1), stoi(book.at(2))));
		}
	}
}

void User::listBooks(bool flagName)
{
	cout << "A list of your books:" << endl;
	cout << "=====================" << endl;
	int i = 1;
	for (Book& book : this->myListBooks) {
		cout << i << ". ";
		book.printInfo(flagName);
		i++;
	}
	if (myListBooks.size() == 0)
		cout << "Your list of books is empty." << endl;
}

void User::takeBook(string pathMyFolder)
{
	cout << "Which book do you want to take?" << endl;
	library.printArrBooks(true);
	cout << "-";
	int val; cin >> val;
	system("cls");
	if (val > library.books.size() || val < 1)
		cout << "You entered the wrong book number!" << endl;
	else {
		ofstream outFile(pathMyFolder + "\\" + library.books.at(val - 1).nameBook + ".txt");

		outFile << library.books.at(val - 1).nameBook << endl;
		outFile << library.books.at(val - 1).author << endl;
		outFile << library.books.at(val - 1).year << endl;

		cout << "Did you take the book: " << library.books.at(val - 1).nameBook << "." << endl << endl;

		this->myListBooks.push_back(Book(library.books.at(val - 1).nameBook, library.books.at(val - 1).author, library.books.at(val - 1).year));

		library.books.erase(library.books.begin() + val - 1);
		listBooks(false);
	}
}

void User::returnBook(string pathMyFolder)
{
	if (this->myListBooks.size() == 0) {
		cout << "You have nothing to return." << endl;
	}
	else {
		cout << "Which book do you want to return?" << endl;
		listBooks(true);
		cout << "-";
		int val; cin >> val;
		system("cls");

		if (val > this->myListBooks.size() || val < 1)
			cout << "You entered the wrong book number!" << endl;
		else {
			cout << "You have chosen a book: " << this->myListBooks.at(val - 1).nameBook << "." << endl << endl;

			library.books.push_back(Book(this->myListBooks.at(val - 1).nameBook, this->myListBooks.at(val - 1).author, this->myListBooks.at(val - 1).year));

			fs::remove(pathMyFolder + "\\" + this->myListBooks.at(val - 1).nameBook + ".txt");

			this->myListBooks.erase(this->myListBooks.begin() + val - 1);

			listBooks(false);
		}
	}
}

void User::registration(string newFolderPath, string login)
{
	system("cls");
	fs::create_directory(newFolderPath);

	cout << "You are not on the list, but you are now registered.\nYour username - " << login << endl;
}

int User::entrance(string& login)
{
	system("cls");
	cout << "Enter your login to log in:\n-";
	cin >> login;
	system("cls");

	string newFolderPath = PATH + login;
	if (fs::exists(newFolderPath)) {
		cout << "You have successfully logged in to the system.\n" << endl;
	}
	else {
		char f;
		cout << "There is no such login in our system." << endl << "Register you using this username?" << " Y/N - ";
		cin >> f;
		if (f == 'Y' || f == 'y')
			registration(newFolderPath, login);
		else {
			entrance(login);
		}
	}

	return 1;
}


// ------- Library Menu -------


void Library::menuUser(Library& library, User* user, string& login, bool mainFlag)
{
	char input;
	Library::printHelloUser(login);

	while (mainFlag)
	{
		input = _getch();

		switch (input)
		{
		case 'p':
			system("cls");
			library.printArrBooks(false);
			break;

		case 't':
			system("cls");
			user->listBooks(false);
			break;

		case 'd':
			system("cls");
			user->takeBook(user->pathMyFolder);
			break;

		case 's':
			system("cls");
			user->returnBook(user->pathMyFolder);
			break;

		case 'c':
			system("cls");
			Library::printHelloUser(login);
			break;

		case 'x':
			system("cls");
			mainFlag = false;
			break;
		}
	}
}

void Library::mainMenu(Library& library, User* user, string& login, bool& mainFlag)
{
	char input;
	Library::printMainInfo();

	while (mainFlag)
	{
		input = _getch();

		switch (input)
		{
		case 'p':
			system("cls");
			library.printArrBooks(false);
			break;

		case 'l':
			system("cls");
			if (User::entrance(login))
			{
				user = new User(login);
				user->initializing();
				menuUser(library, user, login, mainFlag);
				delete user;
				Library::printMainInfo();
			}
			break;

		case 'c':
			system("cls");
			Library::printMainInfo();
			break;

		case 'x':
			system("cls");
			cout << "Exit." << endl;
			mainFlag = false;
			break;
		}
	}
}


// ------- Main -------


int main()
{
	library.addBook("Fight Club", "Chuck Palahniuk", 1996);
	library.addBook("Martin Eden", "Jack London", 1909);
	library.addBook("1984", "George Orwell", 1949);
	library.addBook("A hundred years of loneliness", "Gabriel Garcia Marqu ez", 1967);
	library.addBook("451 degrees Fahrenheit", "Ray Bradbury", 1953);
	library.addBook("Woe from wit", "Alexander Sergeevich Griboyedov", 1828);
	library.addBook("War and Peace", "Leo Tolstoy", 1863);
	library.addBook("Crime and punishment", "Fyodor Dostoevsky", 1865);

	bool mainFlag = true;
	User* user = NULL;
	string login;
	Library::mainMenu(library, user, login, mainFlag);




	return 0;
}