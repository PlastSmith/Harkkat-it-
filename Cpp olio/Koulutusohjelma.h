#pragma once
#include "Opiskelija.h"
#include "Opettaja.h"

#include<string>
#include<vector>

using std::string; using std::vector;

class Koulutusohjelma
{
public:
	Koulutusohjelma();
	Koulutusohjelma(string nimi);
	Koulutusohjelma(const Koulutusohjelma& alkup);
	Koulutusohjelma& operator = (const Koulutusohjelma& alkup);
	virtual ~Koulutusohjelma();

	void lisaaOpettaja();
	void lisaaOpiskelija();

	void poistaOpiskelija(int indexOPISK);
	void poistaOpettaja(int indexOPE);
	void paivitaOpettaja(int indexOPE);
	void paivitaOpiskelija(int indexOPISK);

	void tulostaOpettajat() const;
	void tulostaOpiskelijat() const;
	
	void asetaKoulutusohjelma(string nimi);
	void asetaOpiskelija(Opiskelija oppilas);
	void asetaOpettaja(Opettaja ope);
	string annaKoulutusohjelma() const;
	vector <Opiskelija> annaOpiskelijat();
	vector <Opettaja> annaOpettajat();

private:
	string nimi_;
	vector <Opiskelija> opiskelijat_;
	vector <Opettaja> opettajat_;

};

