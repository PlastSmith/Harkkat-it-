#include "Sovellus.h"
#include <iostream>
#include <exception>

using std::cerr; using std::endl; using std::exception;

int main() {
	Sovellus sovellus;

	try {
		sovellus.aja();
	}
	catch (exception const& virhe)
	{
		cerr << "Virhe   " << virhe.what() << endl;
	}
	catch (...) // napppaa kaikki virheet
	{
		cerr << "Virhe " << endl;
	}

	
	return 0;
}