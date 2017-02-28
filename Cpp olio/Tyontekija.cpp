#include "Tyontekija.h"
#include <stdlib.h> 

#include <iostream>
#include <string>

using std::string; using std::cout; using std::endl; using std::getline; using std::cin;

Tyontekija::Tyontekija() :Henkilo(	), tunnus_("N/A"), palkka_(0)
{
	//std::cout << "Tyontekija: Oletusrakentaja" << this << std::endl;
}

Tyontekija::Tyontekija(string enimi, string snimi, string osoite,
	string puhnro, string tunnus, double palkka) : Henkilo(enimi, snimi, osoite, puhnro), tunnus_(tunnus), palkka_(palkka)
{
	//std::cout << "Tyontekija: Parametrinene rakentaja" << this << std::endl;
}

Tyontekija::Tyontekija(const Tyontekija &alkup) : Henkilo(alkup), tunnus_(alkup.tunnus_), palkka_(alkup.palkka_)
{
	//std::cout << "Tyontekija: Kopiorakentaja" << this << std::endl;
}

Tyontekija& Tyontekija::operator = (Tyontekija const& alkup)	// Tyontekija& alussa estää kopioinnin return käskyssä
{
	if (this != &alkup)
	{
		Henkilo::operator=(alkup);	// kutsutaan kantaolion operatoria tekemaan kannan kopiointi
		tunnus_ = alkup.palkka_;
		palkka_ = alkup.palkka_;
	}
	return *this; // eiks tämä nyt ole *&this eli on olio itse osoitin ja viite kumoavat toisensa osoitin muistipaikkaan, jossa alkup olio?
}

Tyontekija::~Tyontekija()
{
	//std::cout << "Tyontekija: Purkaja" << this << std::endl;
}

void Tyontekija::kysyTiedot()
{
	Henkilo::kysyTiedot();
	cout << "Anna Tunnus: ";
	getline(cin, tunnus_);
	cout << "Anna palkka: ";
	string palkka;
	getline(cin, palkka);
	palkka_ = atof(palkka.c_str());
}

void Tyontekija::tulosta() const
{
	Henkilo::tulosta();
	cout << "Tunnus: " << tunnus_ << endl;
	cout << "Palkka: " << palkka_ << endl;
}

double Tyontekija::annaPalkka() const
{
	return palkka_;
}

void Tyontekija::asetaPalkka(double palkka)
{
	palkka_ = palkka;
}

void Tyontekija::asetaTunnus(string tunnus)
{
	tunnus_ = tunnus;
}

string Tyontekija::annaTunnus()
{
	return tunnus_;
}
