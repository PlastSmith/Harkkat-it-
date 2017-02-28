#include<string>
#include<vector>
#include<iostream>
#include <stdlib.h> 

#include "Koulutusohjelma.h"

using std::string; using std::cout; using std::endl; using std::getline; using std::cin; using std::vector;

Koulutusohjelma::Koulutusohjelma() : nimi_(""), opiskelijat_(vector<Opiskelija>()), opettajat_(vector<Opettaja>())
{
	//cout << "Koulutusohjelma: Oletusrakentaja " << this << endl;
}

Koulutusohjelma::Koulutusohjelma(string nimi) : nimi_(nimi), opiskelijat_(vector<Opiskelija>()), opettajat_(vector<Opettaja>())
{
	//cout << "Koulutusohjelma: Parametrinen rakentaja " << this << endl;
}

Koulutusohjelma::Koulutusohjelma(const Koulutusohjelma& alkup) : nimi_(alkup.nimi_), opiskelijat_(alkup.opiskelijat_), opettajat_(alkup.opettajat_)
{
	//cout << "Koulutusohjelma: Kopiorakentaja " << this << endl;
}

Koulutusohjelma& Koulutusohjelma::operator=(Koulutusohjelma const& alkup)
{
	if (this != &alkup)
	{
		nimi_ = alkup.nimi_;
		opiskelijat_ = alkup.opiskelijat_;	// kutsuvatko kopioituessaan sitten omia = operaattoreitaan???
		opettajat_ = alkup.opettajat_;
	}
	return *this;
}


Koulutusohjelma::~Koulutusohjelma()
{
	// cout << "Koulutusohjelma: Purkaja " << this << endl;
}

void Koulutusohjelma::lisaaOpettaja()
{
	cout << "Anna etunimi:";
	string enimi;
	getline(cin, enimi);

	cout << "Anna sukunimi:";
	string snimi;
	getline(cin, snimi);

	cout << "Anna osoite:";
	string osoite;
	getline(cin, osoite);

	cout << "Anna puhnro:";
	string puhnro;
	getline(cin, puhnro);

	cout << "Anna tunnus:";
	string tunnus;
	getline(cin, tunnus);

	cout << "Anna palkka:";
	string txtPalkka;
	getline(cin, txtPalkka);
	double palkka = atof(txtPalkka.c_str());

	cout << "Anna opetusala:";
	string oala;
	getline(cin, oala);

	Opettaja ope(enimi, snimi, osoite, puhnro, tunnus, palkka, oala);
	opettajat_.push_back(ope);
	
	cout << endl;

}

void Koulutusohjelma::lisaaOpiskelija()
{
	cout << "Anna opiskelijan etunimi:";
	string enimi;
	getline(cin, enimi);

	cout << "Anna opiskelijan sukunimi:";
	string snimi;
	getline(cin, snimi);

	cout << "Anna opiskelijan osoite:";
	string osoite;
	getline(cin, osoite);

	cout << "Anna opiskelijan puhnro:";
	string puhnro;
	getline(cin, puhnro);

	cout << "Anna opiskelijan opiskelijanumero:";
	string onro;
	getline(cin, onro);

	Opiskelija oppilas(enimi, snimi, osoite, puhnro, onro);
	opiskelijat_.push_back(oppilas);

	cout << endl;

}

void Koulutusohjelma::poistaOpiskelija(int indexOPISK)
{
	cout << "Opiskelija: \"" << opiskelijat_[indexOPISK].annaEtunimi() << " " << opiskelijat_[indexOPISK].annaSukunimi();
	opiskelijat_.erase(opiskelijat_.begin() + indexOPISK);
	cout << "\" poistettu!" << endl << endl;
}

void Koulutusohjelma::poistaOpettaja(int indexOPE)
{
	cout << "Opettaja: \"" << opettajat_[indexOPE].annaEtunimi() << " " << opettajat_[indexOPE].annaSukunimi() ;
	opettajat_.erase(opettajat_.begin() + indexOPE);
	cout << "\" poistettu!" << endl << endl;
}

void Koulutusohjelma::paivitaOpiskelija(int indexOPISK)
{
	opiskelijat_[indexOPISK].kysyTiedot();
}

void Koulutusohjelma::paivitaOpettaja(int indexOPE)
{
	opettajat_[indexOPE].kysyTiedot();
}

void Koulutusohjelma::tulostaOpettajat() const
{
	cout << "OPETTAJAT(" << nimi_ << "):" << endl;
	cout << "-----------" << endl;

	for (Opettaja ope : opettajat_)
	{
		ope.tulosta();
	}
	cout << endl;
}

void Koulutusohjelma::tulostaOpiskelijat() const
{
	cout << "OPISKELIJAT(" << nimi_ << "):" << endl;
	cout << "-----------" << endl;
	for (Opiskelija oppilas : opiskelijat_)
	{
		oppilas.tulosta();
	}
	cout << endl;
}


void Koulutusohjelma::asetaKoulutusohjelma(string nimi)
{
	nimi_ = nimi;
}

void Koulutusohjelma::asetaOpiskelija(Opiskelija oppilas)
{
	opiskelijat_.push_back(oppilas);
}

void Koulutusohjelma::asetaOpettaja(Opettaja ope)
{
	opettajat_.push_back(ope);
}

string Koulutusohjelma::annaKoulutusohjelma() const
{
	return nimi_;
}

vector<Opiskelija> Koulutusohjelma::annaOpiskelijat()
{
	return opiskelijat_;
}

vector<Opettaja> Koulutusohjelma::annaOpettajat()
{
	return opettajat_;
}