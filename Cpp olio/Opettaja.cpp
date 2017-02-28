#include "Opettaja.h"

#include<string>
#include<iostream>

using std::string;

Opettaja::Opettaja():Tyontekija(), opetusala_("ei määritelty")
{
	// std::cout << "Opettaja: Oletusrakentaja" << this << std::endl;
}

Opettaja::Opettaja(string enimi, string snimi, string osoite, string puhnro, string tunnus, double palkka, string oala):
	Tyontekija(enimi, snimi, osoite, puhnro,tunnus, palkka), opetusala_(oala)
{
	// std::cout << "Opettaja: Parametrinen rakentaja" << this << std::endl;
}

Opettaja::Opettaja(const Opettaja & alkup):Tyontekija(alkup), opetusala_(alkup.opetusala_)
{
	//std::cout << "Opettaja: Kopiorakentaja" << this << std::endl;
}

Opettaja& Opettaja::operator = (Opettaja const& alkup)
{
	if (this != &alkup)
	{
		Tyontekija::operator=(alkup);
		opetusala_ = alkup.opetusala_;
	}
	return *this;
}

Opettaja::~Opettaja()
{
	//std::cout << "Opettaja: Purkaja" << this << std::endl;
}

void Opettaja::kysyTiedot()
{
	Tyontekija::kysyTiedot();

	std::cout << "Anna opetusala: ";
	std::string oala;
	std::getline(std::cin, oala);
	opetusala_ = oala;
	std::cout << std::endl << std::endl;
}

void Opettaja::tulosta() const
{
	Tyontekija::tulosta();
	std::cout << "Opetusala: " << opetusala_ << std::endl << std::endl;
}

void Opettaja::asetaOpetusala(std::string oala)
{
	opetusala_ = oala;
}

std::string Opettaja::annaOpetusala()
{
	return std::string();
}


