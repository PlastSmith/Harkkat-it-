#pragma once
#include "Henkilo.h"
#include<string>

using std::string;

class Opiskelija :
	public Henkilo
{
public:
	Opiskelija();
	Opiskelija(string enimi, string snimi, string osoite, string puhnro, string opnro);
	Opiskelija(const Opiskelija &alkup);
	Opiskelija& operator = (const Opiskelija& alkup); // = uudelleen m‰‰rittely
	virtual ~Opiskelija();

	void kysyTiedot();
	void tulosta() const;

	void asetaOpiskelijanumero(string);
	string annaOpiskelijanumero() const;

private:
	string opiskelijanumero_;
};

