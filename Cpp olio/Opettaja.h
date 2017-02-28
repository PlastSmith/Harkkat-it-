#pragma once
#include "Tyontekija.h"
#include <string>

using std::string;

class Opettaja :
	public Tyontekija
{
public:
	Opettaja();
	Opettaja(string enimi, string snimi, string osoite, string puhnro, string tunnus, double palkka, string oala);
	Opettaja(Opettaja const& alkup);
	Opettaja& operator = (const Opettaja& alkup);
	virtual ~Opettaja();

	void kysyTiedot();
	void tulosta() const;

	void asetaOpetusala(std::string);
	string annaOpetusala();

private:
	string opetusala_;
};

