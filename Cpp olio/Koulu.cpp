#include "Koulutusohjelma.h"
#include "Koulu.h"

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <direct.h>
#include <exception>

using std::vector; using std::string; using std::cout; using std::getline; using std::endl; using std::cin; using std::cerr; std::ifstream; std::ofstream; using std::cerr; std::exception;


Koulu::Koulu() :nimi_(""), koulutusohjelmat_(vector<Koulutusohjelma>())
{
}

Koulu::Koulu(string nimi) : nimi_(nimi), koulutusohjelmat_(vector<Koulutusohjelma>())
{
}

Koulu::~Koulu()
{
}

void Koulu::lisaaKoulutusohjelma()
{
	cout << "Anna koulutusohjelman nimi: ";
	string apuNimi;
	getline(cin, apuNimi);
	koulutusohjelmat_.push_back( apuNimi );
	cout << endl;
}

void Koulu::tulostaKoulutusohjelmat() const
{
	cout << "KOULUTUSOHJELMAT" << endl;
	cout << "------------------------" << endl;
	for (Koulutusohjelma apuKO : koulutusohjelmat_)
	{
		cout << apuKO.annaKoulutusohjelma() << endl;
	}
	cout << endl;
}

void Koulu::tulostaKoulutusohjelmienMaara() const
{
	cout << "Koulutusohjelmien maara: " << koulutusohjelmat_.size() << endl << endl;
}

void Koulu::lisaaKoulutusohjelmaanOpettaja()
{
	cout << "Opettajan lisääminen koulutusohjelmaan:" << endl;
	int indexKO = etsiKoulutusohjelma();
	if (indexKO >= 0)
	{
		koulutusohjelmat_[indexKO].lisaaOpettaja();
	}
	else
	{
		cerr << "Koulutusohjelmaa ei ole olemassa." << endl << endl;
	}
}

void Koulu::tulostaKoulutusohjelmanOpettajat() const
{
	cout << "Koulutusohjelman opettajien tulostaminen" << endl;
	int indexKO = etsiKoulutusohjelma();
	if (indexKO >= 0)
	{
		koulutusohjelmat_[indexKO].tulostaOpettajat();
	}
	else
	{
		cerr << "Koulutusohjelmaa ei löytynyt!" << endl << endl;
	}
}

void Koulu::lisaaKoulutusohjelmaanOpiskelija()
{
	cout << "Opiskelijan lisääminen koulutusohjelmaan" << endl;
	int indexOPISK = etsiKoulutusohjelma();
	if (indexOPISK >= 0)
	{
		koulutusohjelmat_[indexOPISK].lisaaOpiskelija();
	}
	else
	{
		cerr << "Koulutusohjelmaa ei löytynyt!" << endl << endl;
	}
}

void Koulu::tulostaKoulutusohjelmanOpiskelijat() const
{
	cout << "Koulutusohjelman opiskelijoiden tulostaminen" << endl;

	int indexOPISK = etsiKoulutusohjelma();
	if (indexOPISK >= 0)
	{
		koulutusohjelmat_[indexOPISK].tulostaOpiskelijat();
	}
	else
	{
		cerr << "Koulutusohjelmaa ei löytynyt!" << endl << endl;
	}
}

void Koulu::poistaKoulutusohjelma()
{
	cout << "Koulutusohjelman poistaminen" << endl;

	int indexKO = etsiKoulutusohjelma();
	if (indexKO >= 0)
	{
		koulutusohjelmat_.erase(koulutusohjelmat_.begin() + indexKO);
	}
	else
	{
		cerr << "Poistettavaa koulutusohjelmaa ei löytynyt!" << endl << endl;
	}
}

void Koulu::poistaOpettajaKoulutusohjelmasta()
{
	int indexKO = etsiKoulutusohjelma();
	cout << indexKO << endl;
	int indexOPE = -1;

	if (indexKO >= 0)
	{
		indexOPE = etsiOpettaja(indexKO);
	}

	if (indexKO < 0)
	{
		cerr << "Koulutusohjelmaa ei löytynyt!" << endl << endl;
	}
	else if (indexOPE >= 0)
	{
		koulutusohjelmat_[indexKO].poistaOpettaja(indexOPE);
	}
	else
	{
		cerr << "Opettajaa ei löytynyt!" << endl << endl;
	}
}

void Koulu::poistaOpiskelijaKoulutusohjelmasta()
{
	int indexKO = etsiKoulutusohjelma();
	int indexOPISK = -1;
	
	if (indexKO >= 0)
	{
		indexOPISK = etsiOpiskelija(indexKO);
	}

	if (indexKO < 0)
	{
		cerr << "Koulutusohjelmaa ei löytynyt!" << endl << endl;
	}
	else if (indexOPISK >= 0)
	{
		koulutusohjelmat_[indexKO].poistaOpiskelija(indexOPISK);
	}
	else
	{
		cerr << "Opiskelijaa ei löytynyt!" << endl << endl;
	}
}

void Koulu::paivitaKoulutusohjelmanNimi()
{
	int indexKO = 0;

		indexKO = etsiKoulutusohjelma();

		if (indexKO >= 0)
		{
			cout << "Koulutusohjelma loytyi!" << endl << endl;
			cout << "Anna koulutusohjelmalle uusi nimi: ";
			string uusiNimi = "";
			getline(cin, uusiNimi);
			koulutusohjelmat_[indexKO].asetaKoulutusohjelma(uusiNimi);
			cout << "Uusi nimi asetettu " << endl << endl;
		}
		else
		{
			cerr << "Koulutusohjelmaa ei loytynyt!" << endl << endl;
		}
}

void Koulu::paivitaOpettajanTiedot()
{
		int indexKO = etsiKoulutusohjelma();
		int indexOPE = 0; 

		if (indexKO >= 0)
		{
			indexOPE = etsiOpettaja(indexKO);
		}

		if (indexKO < 0)
		{
			cerr << "Koulutusohjelmaa ei löytynyt!" << endl << endl;
		}
		else if (indexOPE < 0)
		{
			cerr << "Opettajaa ei löytynyt!" << endl << endl;
		}
		else
		{
			koulutusohjelmat_[indexKO].paivitaOpettaja(indexOPE);
			cerr << "Opettajan tiedot asetettu." << endl << endl;
		}
}

void Koulu::paivitaOpiskelijanTiedot()
{
		int indexKO = etsiKoulutusohjelma();
		int indexOPISK = -1;

		if (indexKO >= 0)
		{
			indexOPISK = etsiOpiskelija(indexKO);
		}

		if (indexKO < 0)
		{
			cerr << "Koulutusohjelmaa ei löytynyt!" << endl << endl;
		}
		else if (indexOPISK < 0)
		{
			cerr << "Opiskelijaa ei löytynyt!" << endl << endl;
		}
		else
		{
			koulutusohjelmat_[indexKO].paivitaOpiskelija(indexOPISK);
			cout << "Opiskelijaa tiedot asetettu." << endl << endl;
		}
}

void Koulu::asetaNimi(string nimi)
{
	nimi_ = nimi;
}

string Koulu::annaNimi() const
{
	return nimi_;
}

int Koulu::etsiOpiskelija(int indexKO)
{
	cout << "Anna oppilaan opiskelijanumero: ";
	string apuOppilas = "";
	getline(cin, apuOppilas);

	if (!koulutusohjelmat_[indexKO].annaOpiskelijat().empty())
	{
		for (int i = 0; i < koulutusohjelmat_.size(); i++)
		{
			if (koulutusohjelmat_[indexKO].annaOpiskelijat()[i].annaOpiskelijanumero() == apuOppilas)
			{
				return i;
			}
		}
	}
	return -1;
}

int Koulu::etsiOpettaja(int indexKO) 
{
	cout << "Anna opettajan tunnus: ";
	string apuOpe = "";
	getline(cin, apuOpe);

	if (!koulutusohjelmat_[indexKO].annaOpettajat().empty())
	{
		for (int i = 0; i < koulutusohjelmat_.size(); i++)
		{
			if (koulutusohjelmat_[indexKO].annaOpettajat()[i].annaTunnus() == apuOpe)
			{
				return i;
			}
		}
	}
	return -1;
}

void Koulu::avaaTiedot()
{
	// sama taalla isfstream halusi jostain syysta std:: vaikka importattu ???
	std::ifstream luku_tied; // luodaan tiedosto-olio lukua varten inputfilestream

	string apuKO, etunimi, sukunimi, osoite, puhelinnumero, opNro, tunnus, opetusala, palkka;

	luku_tied.open("koulutusohjelmat.csv");
	if (luku_tied.is_open())
	{
		while (luku_tied.peek() != EOF) // luetaan tiedosto loppuu, End Of File
		{
			// luetaan apu-stringeihin
			getline(luku_tied, apuKO, '\n');

			koulutusohjelmat_.push_back(apuKO);
		}
		luku_tied.close();
	}
	else
	{
		cout << "Tiedostoa ei voitu avata! " << endl << endl;
	}

	luku_tied.open("opiskelijat.csv");
	if (luku_tied.is_open())
	{
		while (luku_tied.peek() != EOF) // luetaan tiedosto loppuu, End Of File
		{
			// luetaan apu-stringeihin
			getline(luku_tied, apuKO, ';');
			getline(luku_tied, etunimi, ';');
			getline(luku_tied, sukunimi, ';');
			getline(luku_tied, osoite, ';');
			getline(luku_tied, puhelinnumero, ';');
			getline(luku_tied, opNro, '\n');

			for (int i = 0; i < koulutusohjelmat_.size(); i++)
			{
				if (koulutusohjelmat_[i].annaKoulutusohjelma() == apuKO)
				{
					Opiskelija apuOPISK(etunimi, sukunimi, osoite, puhelinnumero, opNro); // luodaan hlo-olio
					koulutusohjelmat_[i].asetaOpiskelija(apuOPISK);
				}
			}
		}

		luku_tied.close();
	}
	else
	{
		cout << "Tiedostoa ei voitu avata! " << endl << endl;
	}

	// 	Opettaja(string enimi, string snimi, string osoite, string puhnro, string tunnus, double palkka, string oala);

	luku_tied.open("opettajat.csv");
	if (luku_tied.is_open())
	{
		while (luku_tied.peek() != EOF) // luetaan tiedosto loppuu, End Of File
		{
			// luetaan apu-stringeihin
			getline(luku_tied, apuKO, ';');
			getline(luku_tied, etunimi, ';');
			getline(luku_tied, sukunimi, ';');
			getline(luku_tied, osoite, ';');
			getline(luku_tied, puhelinnumero, ';');
			getline(luku_tied, tunnus, ';');
			getline(luku_tied, palkka, ';');
			getline(luku_tied, opetusala, '\n');

			for (int i = 0; i < koulutusohjelmat_.size(); i++)
			{
				if (koulutusohjelmat_[i].annaKoulutusohjelma() == apuKO)
				{
					//std::string::size_type size;
					Opettaja apuOPE(etunimi, sukunimi, osoite, puhelinnumero, tunnus, stod(palkka), opetusala); // luodaan hlo-olio
					koulutusohjelmat_[i].asetaOpettaja(apuOPE);
				}
			}
		}

		luku_tied.close();
	}
	else
	{
		cout << "Tiedostoa ei voitu avata! " << endl << endl;
	}

}

void Koulu::tallennaTiedot()
{
	string polku = _getcwd(NULL, 0); // ei pakollinen, mutta mukava tietää c://temp// oltava tuplat koska / erikosimerkki
	cout << "Oletuspolku " << polku << endl;


	//Opiskelija hessu("Hessu", "Hopo", "Katu 2", "0501234567", "opNro");
	//Opiskelija jaana("Jaana", "Jämäkkä", "Katu 3", "0407654321", "OpNro2");

	// Latkitaan opsikelijat vektoriin
	//vector <Opiskelija> opiskelijat;

	std::ofstream kirj_tied; // luodaan tiedosto-olio kirjoitusta varten


	kirj_tied.open("koulutusohjelmat.csv");

	if (kirj_tied.is_open()) // tarkistetaan onko auki
	{
		for (int i = 0; i < koulutusohjelmat_.size(); i++)	// korjasin <=
		{
			//opiskelijat.push_back(koulutusohjelmat_[i].annaOpiskelijat()[j]);
			kirj_tied << koulutusohjelmat_[i].annaKoulutusohjelma() << endl;
		}
		kirj_tied.close();
	}
	else
	{
		cout << "Tiedostoa ei voitu avata! " << endl << endl;
	}



	kirj_tied.open("opettajat.csv");

	if (kirj_tied.is_open()) // tarkistetaan onko auki
	{
		for (int i = 0; i < koulutusohjelmat_.size(); i++)	// korjasin <=
		{
			for (int j = 0; j < koulutusohjelmat_[i].annaOpettajat().size(); j++) // korjasin <=
			{
				kirj_tied <<
					koulutusohjelmat_[i].annaKoulutusohjelma() << ";"
					<< koulutusohjelmat_[i].annaOpettajat()[j].annaEtunimi() << ";"
					<< koulutusohjelmat_[i].annaOpettajat()[j].annaSukunimi() << ";"
					<< koulutusohjelmat_[i].annaOpettajat()[j].annaOsoite() << ";"
					<< koulutusohjelmat_[i].annaOpettajat()[j].annaPuhelinnumero() << ";"
					<< koulutusohjelmat_[i].annaOpettajat()[j].annaTunnus() << ";"
					<< koulutusohjelmat_[i].annaOpettajat()[j].annaPalkka() << ";"
					<< koulutusohjelmat_[i].annaOpettajat()[j].annaOpetusala() << endl;
			}
		}
		kirj_tied.close();
	}
	else
	{
		cout << "Tiedostoa ei voitu avata! " << endl << endl;
	}




	kirj_tied.open("opiskelijat.csv");

	if (kirj_tied.is_open()) // tarkistetaan onko auki
	{
		for (int i = 0; i < koulutusohjelmat_.size(); i++)	// korjasin <=
		{
			for (int j = 0; j < koulutusohjelmat_[i].annaOpiskelijat().size(); j++) // korjasin <=
			{
				//opiskelijat.push_back(koulutusohjelmat_[i].annaOpiskelijat()[j]);
				kirj_tied <<
					koulutusohjelmat_[i].annaKoulutusohjelma() <<
					";" << koulutusohjelmat_[i].annaOpiskelijat()[j].annaEtunimi() <<
					";" << koulutusohjelmat_[i].annaOpiskelijat()[j].annaSukunimi() <<
					";" << koulutusohjelmat_[i].annaOpiskelijat()[j].annaOsoite() <<
					";" << koulutusohjelmat_[i].annaOpiskelijat()[j].annaPuhelinnumero() <<
					";" << koulutusohjelmat_[i].annaOpiskelijat()[j].annaOpiskelijanumero() << endl;
			}
		}
		kirj_tied.close();
	}
	else
	{
		cout << "Tiedostoa ei voitu avata! " << endl << endl;
	}
}

//////////////////
//   PRIVATET  //
/////////////////
int Koulu::etsiKoulutusohjelma() const
{
	cout << "Anna koulutusohjelman nimi: ";
	string apuKO = "";
	getline(cin, apuKO);

	if (!koulutusohjelmat_.empty())
	{
		for (int i = 0; i < koulutusohjelmat_.size(); i++)
		{
			if (koulutusohjelmat_[i].annaKoulutusohjelma() == apuKO)
			{
				return i;
			}
		}
	}
	return -1;
}