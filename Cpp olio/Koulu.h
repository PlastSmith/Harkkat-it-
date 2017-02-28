#pragma once
#include <string>
#include <vector>
#include "Koulutusohjelma.h"

class Koulu
{
public:
	Koulu();
	Koulu(string nimi);
	// Koulu(const Koulu &alkup);	// v�ltet��n k�ytt�� koska iso kilke
	//Koulu& operator = (const Koulu& vanha);
	virtual ~Koulu();

	void lisaaKoulutusohjelma();
	void tulostaKoulutusohjelmat() const;
	void tulostaKoulutusohjelmienMaara() const;
	void lisaaKoulutusohjelmaanOpettaja();
	void tulostaKoulutusohjelmanOpettajat() const;
	void lisaaKoulutusohjelmaanOpiskelija();
	void tulostaKoulutusohjelmanOpiskelijat() const;

	void poistaKoulutusohjelma();
	void poistaOpettajaKoulutusohjelmasta();
	void poistaOpiskelijaKoulutusohjelmasta();

	void paivitaKoulutusohjelmanNimi();
	void paivitaOpettajanTiedot();
	void paivitaOpiskelijanTiedot();

	int etsiOpiskelija(int indexKO);
	int etsiOpettaja(int indexKO);

	void avaaTiedot();
	void tallennaTiedot();

	void asetaNimi(string nimi);
	string annaNimi() const;

private:
	string nimi_;
	vector<Koulutusohjelma> koulutusohjelmat_;
	int etsiKoulutusohjelma() const;	// palauttaa -1 jos ei loydy



};

