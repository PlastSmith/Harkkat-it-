#include "Henkilo.h"
#include <iostream>

Henkilo::Henkilo() : etunimi_("N/A"), sukunimi_("N/A"), osoite_("N/A"), puhelinnumero_("N/A")
{
	//std::cout << "Henkilo: Oletusrakentaja " << this << std::endl;
}

Henkilo::Henkilo(std::string enimi, std::string snimi, std::string osoite, std::string puhnro):
	etunimi_(enimi), sukunimi_(snimi), osoite_(osoite), puhelinnumero_(puhnro)
{
	//std::cout << "Henkilo: Parametrinen rakentaja " << this << std::endl;
}

Henkilo::Henkilo(Henkilo const& alkup): etunimi_(alkup.etunimi_), sukunimi_(alkup.sukunimi_),
osoite_(alkup.osoite_), puhelinnumero_(alkup.puhelinnumero_)
{
	//std::cout << "Henkilo: Kopiorakentaja " << this << std::endl;
}

Henkilo& Henkilo::operator = (Henkilo const& alkup)
{
	if (this != &alkup)
	{
		etunimi_ = alkup.etunimi_;
		sukunimi_ = alkup.sukunimi_;
		osoite_ = alkup.osoite_;
		puhelinnumero_ = alkup.puhelinnumero_;
		return *this;
	}
	return *this;
}


Henkilo::~Henkilo()
{
	//std::cout << "Henkilo: Purkaja" << this << std::endl;
}

void Henkilo::kysyTiedot()
{
	std::cout << "Anna etunimi: ";
	std::string enimi;
	std::getline(std::cin, enimi);
	etunimi_ = enimi;

	std::cout << "Anna sukunimi: ";
	std::string snimi;
	std::getline(std::cin, snimi);
	sukunimi_ = snimi;

	std::cout << "Anna osoite: ";
	std::string osoite;
	std::getline(std::cin, osoite);
	osoite_ = osoite;

	std::cout << "Anna puhelinnumero: ";
	std::string puh;
	std::getline(std::cin, puh);
	puhelinnumero_ = puh;
}

void Henkilo::tulosta() const
{
	std::cout << "Etunimi: " << etunimi_ << std::endl;
	std::cout << "Sukunimi: " << sukunimi_ << std::endl;
	std::cout << "Osoite: " << osoite_ << std::endl;
	std::cout << "Puh.nro " << puhelinnumero_ << std::endl;
}

std::string Henkilo::annaEtunimi() const
{
	return etunimi_;
}

std::string Henkilo::annaOsoite() const
{
	return osoite_;
}

std::string Henkilo::annaPuhelinnumero() const
{
	return puhelinnumero_;
}

std::string Henkilo::annaSukunimi() const
{
	return sukunimi_;
}

void Henkilo::asetaEtunimi(std::string enimi) 
{
etunimi_ = enimi;

}

void Henkilo::asetaOsoite(std::string osoite)
{
	osoite_ = osoite;
}

void Henkilo::asetaPuhelinnumero(std::string puh)
{
	puhelinnumero_ = puh;
}

void Henkilo::asetaSukunimi(std::string snimi)
{
	sukunimi_ = snimi;
}
