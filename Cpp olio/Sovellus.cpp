#include "Sovellus.h"
#include "Koulu.h"
#include "Opiskelija.h"
#include <istream>

#include<string>
#include<iostream>

using std::string; using std::cout;using std::cin; using std::endl;
using std::istream;

Sovellus::Sovellus()
{
	//cout << "Sovellus: Oletusrakentaja" << this << endl;
}

Sovellus::~Sovellus()
{
	//cout << "Sovellus: Purkaja" << this << endl;
}

void Sovellus::aja()
{
	Koulu koulu;
	
	string valinta = "";
	do
	{
		valinta = tulostaValikko();
		cout << endl;

		if (valinta == "1")
		{
			koulu.lisaaKoulutusohjelma();
		}
		else if(valinta == "2")
		{
			koulu.tulostaKoulutusohjelmat();
		}
		else if(valinta == "3")
		{
			koulu.tulostaKoulutusohjelmienMaara();
		}
		else if(valinta =="4")
		{
			koulu.lisaaKoulutusohjelmaanOpettaja();
		}
		else if(valinta == "5")
		{
			koulu.tulostaKoulutusohjelmanOpettajat();
		}
		else if(valinta == "6")
		{
			koulu.lisaaKoulutusohjelmaanOpiskelija();
		}
		else if(valinta == "7")
		{
			koulu.tulostaKoulutusohjelmanOpiskelijat();
		}
		else if(valinta == "8")
		{
			koulu.poistaKoulutusohjelma();
			cout << "" << endl;
		}
		else if(valinta =="9")
		{
			koulu.poistaOpettajaKoulutusohjelmasta();
		}
		else if(valinta == "10")
		{
			koulu.poistaOpiskelijaKoulutusohjelmasta();
		}
		else if(valinta == "11")
		{
			koulu.paivitaKoulutusohjelmanNimi();
		}
		else if(valinta == "12")
		{
			koulu.paivitaOpettajanTiedot();
		}
		else if(valinta == "13")
		{
			// paivita opiskelijan tiedot
			koulu.paivitaOpiskelijanTiedot();
		}
		else if(valinta == "14")
		{
			// lue
			koulu.avaaTiedot();
		}
		else if(valinta == "15")
		{
			// tallenna
			koulu.tallennaTiedot();
		}
		else if (valinta == "0")
		{
			cout << "Poistutaan ohjelmasta." << endl;	
		} 
		else
		{
			cout << "Virheellinen valinta" << endl << endl;
		}

	}
	while(valinta != "0");
}

string Sovellus::tulostaValikko() const
{
	
	cout << "1) Lisaa koulutusohjelma" << endl;
	cout << "2) Tulosta koulutusohjelmien nimet" << endl;
	cout << "3) Tulosta koulutusohjelmien maara" << endl;
	cout << "4) Lisaa koulutusohjelmaan opettaja" << endl;
	cout << "5) Tulosta koulutusohjelman opettajat" << endl;
	cout << "6) Lisaa koulutusohjelmaan opiskelija" << endl;
	cout << "7) Tulosta koulutusohjelman opiskelijat" << endl;
	cout << "8) Poista koulutusohjelma" << endl;
	cout << "9) Poista opettaja" << endl;
	cout << "10) Poista opiskelija" << endl;
	cout << "11) Paivita koulutusohjelman nimi" << endl;
	cout << "12) Paivita opettajan tiedot" << endl;
	cout << "13) Paivita opiskelijan tiedot" << endl;
	cout << "14) Lue tiedot"<< endl;
	cout << "15) Tallenna tiedot" << endl;
	cout << "0) Lopeta" << endl;
	cout << "-----------------------------------------------" << endl << endl;
	
	cout << "Valitse toiminto (0 - 15):" << endl;
	string valinta="";
	getline(cin, valinta);
	return valinta;
}
