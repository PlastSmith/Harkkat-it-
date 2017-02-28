#pragma once
#include "Henkilo.h"

#include <iostream>
#include <string>

using std::string;

class Tyontekija : public Henkilo
{
public:
	Tyontekija();
	Tyontekija(string enimi, string snimi, string osoite, string puhnro, string tunnus, double palkka);
	Tyontekija(const Tyontekija &alkup);
	Tyontekija& operator = (const Tyontekija& alkup);  // TARKATA ETTÄ MUISSA ON NÄIN KIRJOITTETTU OLI VIRHE JÄRJESTYKSESSÄ EI OLLUT KIRJAsSA OHJEISTETTIIN TOISIN
	// voitaisiin kutsua esim. t.oprator=(te);
	virtual ~Tyontekija(); 

	void kysyTiedot();
	void tulosta() const;

	double annaPalkka() const;
	void asetaPalkka(double);
	void asetaTunnus(string tunnus);
	string annaTunnus();

private:
	double palkka_;
	string tunnus_;
};

