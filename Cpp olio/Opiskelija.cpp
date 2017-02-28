#include "Opiskelija.h"

#include <iostream>
#include <string>

using std::string; using std::cout; using std::getline; using std::endl; using std::cin;

Opiskelija::Opiskelija():Henkilo(), opiskelijanumero_("000000000")
{
	//std::cout << "Opiskelija: Oletusrakentaja " << this << std::endl;
}

Opiskelija::Opiskelija(string enimi, string snimi, string osoite,string puhnro, string opnro): Henkilo(enimi,snimi, osoite, puhnro), opiskelijanumero_(opnro)
{
	//std::cout << "Opiskelija: Parametrinen rakentaja " << this << std::endl;
}

Opiskelija::Opiskelija(const Opiskelija &alkup):Henkilo(alkup), opiskelijanumero_(alkup.opiskelijanumero_)
{
	//std::cout << "Opiskelija: Kopiorakentaja " << this << std::endl;
}

Opiskelija& Opiskelija::operator = (Opiskelija const& alkup)
{
	if (this != &alkup)
	{
		Henkilo::operator=(alkup);	// kutsutaan kantaolion operatoria tekemään kannan kopiointi
		opiskelijanumero_ = alkup.opiskelijanumero_;
	}
	return *this;
}

Opiskelija::~Opiskelija()
{
	//std::cout << "Opiskelija: Purkaja" << this << std::endl;
}

void Opiskelija::kysyTiedot()
{
	Henkilo::kysyTiedot();
	cout << "Anna opiskelijanumero: ";
	cout << endl << endl;
	getline(cin, opiskelijanumero_);
}

void Opiskelija::tulosta() const
{
	Henkilo::tulosta();
	cout << "Opiskelijanumero: " << opiskelijanumero_ << endl << endl;
}

void Opiskelija::asetaOpiskelijanumero(string opnro)
{
	opiskelijanumero_ = opnro;
}

string Opiskelija::annaOpiskelijanumero() const
{
	return opiskelijanumero_;
}


