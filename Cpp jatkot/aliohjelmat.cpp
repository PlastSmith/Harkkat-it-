#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#include <ctime>
#include <cstdlib>

#include "vakiot.h"
#include "aliohjelmat.h"


using namespace std;

/*--------------------------------------------------
*
* nimi: alustaLaivojenMaarat
* toiminta: Asettaa laivojemMaarat taulukkoon laivan kokoa vastaavan indeksin arvoksi laivan koon.
* parametri(t): int laivojenMaarat[LAIVOJENLKM]
* paluuarvo(t): ei ole, muokkaa laivojenMaarat sisältöä.
*
*--------------------------------------------------*/
void alustaLaivojenMaarat(int laivojenMaarat[LAIVOJENLKM]) {
	for (int i = 2; i < LAIVOJENLKM; i++) {
		laivojenMaarat[i] = i;
	}
}

/*--------------------------------------------------
*
* nimi: alustaPelilauta
* toiminta: Tallentaa pelilaudan jokaiseen ruutuun " " merkin.
* parametri(t): char pelilauta[LAUDANKOKO][LAUDANKOKO]
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void alustaPelilauta(char pelilauta[LAUDANKOKO][LAUDANKOKO])
{
	for (int i = 0; i < LAUDANKOKO; i++)
	{
		for (int j = 0; j < LAUDANKOKO; j++)
		{
			pelilauta[i][j] = ' ';
		}
	}
}

/*--------------------------------------------------
*
* nimi: tulostaValikko
* toiminta: Tulostaa jokaisen päävalikonrivin.
* parametri(t): ei ole
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void tulostaValikko()
{
	cout << "Laivanupotuspeli\n";
	cout << "================\n\n";
	cout << "Valinnat:\n";
	cout << "1) Syota laivat\n";
	cout << "2) Pelaa\n";
	cout << "3) Arvo laivojen sijainnit\n";
	cout << "4) Tallenna peli\n";
	cout << "5) Lataa peli\n";
	cout << "6) Simuloi peli\n";
	cout << "L) Lopeta\n\n";
}

/*--------------------------------------------------
*
* nimi: lueKomento
* toiminta: Lukee käyttäjältä rivin tekstiä ja muuttaa kaikki tekstin kirjaimet isoiksi kirjaimiksi
* parametri(t): string &komento
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void lueKomento(string &komento)
{
	getline(cin, komento);
	kirjaimetIsoiksi(komento);
}

/*--------------------------------------------------
*
* nimi: valintaVirheellinen
* toiminta: Tarkastaa käyttäjän syötteen oikeellisuuden. Ei tyhjä, pituus ok ja jokin sallituista
* parametri(t): string &valinta
* paluuarvo(t): true jos syöte on muotoiltu väärin, false jos muotoiltu väärin.
*
*--------------------------------------------------*/
bool valintaVirheellinen(string &valinta)
{
	string virhe = "Valinta virheellinen. Vaihtoehtoa ei olemassa.\n\n";
	if (valinta.empty())
	{
		cout << virhe;
		return true;
	}
	else if (valinta.length() < 1 || valinta.length() >= 2)
	{
		cout << virhe;
		return true;
	}
	else if (valinta[0] == '1' || valinta[0] == '2' || valinta[0] == '3' || valinta[0] == '4' || valinta[0] == '5' || valinta[0] == 'L' || valinta[0] == '6') {
		return false;
	}
	else {
		cout << virhe;
		return true;
	}
}

/*--------------------------------------------------
*
* nimi: kirjaimetIsoiksi
* toiminta: Muuttaa annetun merkkijonon kirjaimet isoiksi.
* parametri(t): string &merkkijono
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void kirjaimetIsoiksi(string &merkkijono)
{
	for (unsigned int i = 0; i < merkkijono.length(); i++)
	{
		merkkijono[i] = toupper(merkkijono[i]);
	}
}

/*--------------------------------------------------
*
* nimi: tallennaPeli
* toiminta: Tarkastaa tallennustiedoston olemassa olon ja pyytää sen perusteella varmistuksen tallennukselle. Tarkistaa syötten aliohjelamlla
*			tallennusKomentoEiMuotoiltuOikein. Tallentaa parametrien tiedot tekstitiedostoon aliohjelman tallenna() avulla rivi kerrallaan.
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM]
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void tallennaPeli(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM])
{

	if (tiedostoOlemassa())
	{
		string komento;
		cout << "Sinulla on jo yksi tallennus olemassa. Jos jatkat tallentamista, vanha tallennus menetetään. Haluatko jatkaa tallentamista? K(ylla) / E(i)\n";

		// Pyydetään syöte uudestaan kunnes se voidaan hyväksyä.
		do
		{
			lueKomento(komento);
		} while (tallKomMuotVaarin(komento));

		if (komento[0] == 'E')
		{
			return;
		}
		else
		{
			ofstream outClientFile("pelitilanne.txt", ios::out);
			if (!outClientFile)
			{
				cerr << "Virhe tiedostoa ladattaessa." << endl;
			}
			else
			{
				tallenna(laivataulu, pelilauta, laivojenMaarat);
			}
		}
	}
	else
	{
		tallenna(laivataulu, pelilauta, laivojenMaarat);
	}
}

/*--------------------------------------------------
*
* nimi: tiedostoOlemassa
* toiminta: Aukaistaan pelin tallennustiedosto pelitilanne.txt
* parametri(t): ei ole
* paluuarvo(t): palauttaa tosi, jos tiedosto saadaan aukaistua(=on jo olemassa). Epätosi jos teidostoa ei ole olemassa.
*
*--------------------------------------------------*/
bool tiedostoOlemassa()
{
	ifstream filestreami;
	filestreami.open("pelitilanne.txt");

	return filestreami.is_open();
}


/*--------------------------------------------------
*
* nimi: tallenna
* toiminta: Tulostaa pelitilanne.txt tiedostoon parametrit järjestyksessä laivataulu, pelilauta ja laivojeMaarat rivikerrallaan.
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM]
* paluuarvo(t): ei ole.
*
*--------------------------------------------------*/
void tallenna(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM])
{
	ofstream outClientFile("pelitilanne.txt", ios::out);
	if (!outClientFile)
	{
		cerr << "Virhe tiedostoa ladattaessa." << endl;
	}
	else
	{
		for (int i = 0; i < LAUDANKOKO; i++)
		{
			for (int j = 0; j < LAUDANKOKO; j++)
			{
				outClientFile << laivataulu[i][j];
			}
			outClientFile << endl;
		}

		for (int i = 0; i < LAUDANKOKO; i++)
		{
			for (int j = 0; j < LAUDANKOKO; j++)
			{
				outClientFile << pelilauta[i][j];
			}
			outClientFile << endl;
		}

		// Tallentaa laivojen osien kirjanpitoon tarvittavan taulukon sisällön tiedostoon
		for (int j = 0; j < LAIVOJENLKM; j++)
		{
			outClientFile << laivojenMaarat[j];
		}
		outClientFile << endl;
		outClientFile.close();
	}
}

/*--------------------------------------------------
*
* nimi: tallKomMuotVaarin
* toiminta: Tarkastaa onko syötetty komento tyhjä, oikean mittainen, tai muu merkki kuin hyväksytyt E||K
* parametri(t): string komento
* paluuarvo(t): jos komentoa ei voida hyväksyä palautetaan epätosi
*
*--------------------------------------------------*/
bool tallKomMuotVaarin(string komento) {
	string virhe = "Komento virheellinen. Syota joko K(kylla) / E(i)\n\n";

	if (komento.empty())
	{
		cout << virhe;
		return true;
	}

	if (komento.length() < 1 || komento.length() >= 2)
	{
		cout << virhe;
		return true;
	}

	if (komento[0] == 'E' || komento[0] == 'K')
	{
		return false;
	}
	else {
		cout << virhe;
		return true;
	}
}


/*--------------------------------------------------
*
* nimi: lataaPelitilanne
* toiminta: Tallentaa pelitilanne.txt tiedostosta keskeneräisen pelin tiedot rivikerrallaan laivatauluun, pelilautaan ja laivojenaMaaraan.
*           Kun tiedot on saatu tallennettua asetetaan voidaan pelata arvoon tosi, jotta voidaan siirtyä pelaamaan tai simuloimaan ladattua peliä
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void lataaPelitilanne(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata)
{
	ifstream inClientFile("pelitilanne.txt", ios::in);
	if (!inClientFile)
	{
		cerr << "Virhe tiedosto ei aukea\n";
		return;
	}

	// luetaan 14 riviä
	for (int i = 0; i < 15; i++)
	{
		string line;

		getline(inClientFile, line);

		//ensin laivataulun merkit
		if (i < 7)
		{
			for (int j = 0; j < LAUDANKOKO; j++)
			{
				// tekstitiedostosta tulee string muutetaan numeroksi vähentämällä '0'. 
				laivataulu[i][j] = line[j] - '0';
			}
		}
		// Sitten pelilaudan merkit
		else if (i < 14)
		{
			for (int j = 0; j < LAUDANKOKO; j++)
			{
				pelilauta[i - 7][j] = line[j];
			}
		}
		// Lopuksi luetaan laivajenlukumäärä tiedot
		else {
			for (int j = 0; j < LAIVOJENLKM; j++)
			{
				laivojenMaarat[j] = line[j] - '0';
			}
		}

	}
	inClientFile.close();
	cout << "Peli ladattiin onnistuneesti.\n\n";
	voidaanPelata = true;
}



/////////////////////////////////////////////////
// Laivojen syöttämiseen liittyvät aliohjelmat //
/////////////////////////////////////////////////

/*--------------------------------------------------
*
* nimi: alustaLaivataulu
* toiminta: Sijoittaa jokaiseen parametritaulukon alkioon arvoksi 0
* parametri(t): int taulukko[LAUDANKOKO][LAUDANKOKO]
* paluuarvo(t): ei ole.
*
*--------------------------------------------------*/
void alustaLaivataulu(int taulukko[LAUDANKOKO][LAUDANKOKO])
{
	for (int i = 0; i < LAUDANKOKO; i++) {
		for (int j = 0; j < LAUDANKOKO; j++)
		{
			taulukko[i][j] = 0;
		}
	}
}

/*--------------------------------------------------
*
* nimi: koordVirheellinen
* toiminta: Tarkastaa parametrina annetusta merkkijonosta onko se tyhjä, onko syötetty koordinaatti muoto kirjain + max 2 numero ja ovatko ne oikealta väliltä
* parametri(t): string aloitusXY
* paluuarvo(t): Palauttaa arvon epätosi, jos käyttäjän syöttämä koordinaatti on muotoiltu oikein ja tosi, jos muotoilu on virheellinen.
*
*--------------------------------------------------*/
bool koordVirheellinen(string aloitusXY)
{
	string virhe = "Koordinaatti oli virheellinen! Syötä tiedot uudestaan.\n\n";
	if (aloitusXY.empty())
	{
		cout << virhe;
		return true;
	}

	if (aloitusXY.length() < 2 || aloitusXY.length() >= 4)
	{
		cout << virhe;
		return true;
	}
	else if (aloitusXY.length() == 2)
	{
		// jos ensimmäinen on kirjain ja väliltä A-G ja toinen merkki on numero ja väliltä 1-7 palautetaan epätosi
		if (isalpha(aloitusXY[0]) && (aloitusXY[0] >= 'A' && aloitusXY[0] <= 'G') && isdigit(aloitusXY[1]) && (aloitusXY[1] >= '1' && aloitusXY[1] <= '7'))
		{
			return false;
		}
		else
		{
			cout << virhe;
			return true;
		}
	}
	else
	{
		cout << virhe;
		return true;
	}
}


/*--------------------------------------------------
*
* nimi: suuntaVirheellinen
* toiminta: Tarkastetaan ettei käyttöjän syöttämä suunta ole tyhjä, pituudeltaan suurempi kuin 1 ja että komento vastaa hyväksyttyjä ilmansuuntien lyhenteitä (P, I, E, L)
* parametri(t): string laivanSuunta
* paluuarvo(t): Palauttaa arvon epätosi, jos käyttöjän syöttämä suunta on muotoiltu oikein ja tosi, jos muotoilu on virheellinen.
*
*--------------------------------------------------*/
bool suuntaVirheellinen(string laivanSuunta)
{
	string virhe = "Suunta oli virheellinen! Syötä tiedot uudestaan.\n\n";
	if (laivanSuunta.empty())
	{
		cout << virhe;
		return true;
	}

	if (laivanSuunta.length() > 1)
	{
		cout << virhe;
		return true;
	}
	else if (laivanSuunta[0] == 'P' || laivanSuunta[0] == 'I' || laivanSuunta[0] == 'E' || laivanSuunta[0] == 'L')
	{
		return false;
	}
	else
	{
		return true;
	}
}


/*--------------------------------------------------
*
* nimi: laivaSopiiLaudalle
* toiminta: Tarkistaa sopiiko laiva pelilaudalle aliohjelman laivaMahtuuLaudalle avulla, jos laiva mahtuu laivatauluun tarkisteaan onko sen asuttamat ruudut
*			tyhjiä aliohjelman ruudutOvatTyhjiä avulla
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], string laivanSuunta, string aloitusXY, int laivanKoko, bool &syoteVaarin
* paluuarvo(t): Palauttaa arvon tosi, jos laiva voidaan sijoittaa annetuilla parametreilla laaivatauluun ja epätosi, jos laivaa ei voida sijoittaa laivatauluun
*
*--------------------------------------------------*/
bool laivaSopiiLaudalle(int laivataulu[LAUDANKOKO][LAUDANKOKO], string laivanSuunta, string aloitusXY, int laivanKoko, bool arvotaanLaivoja)
{
	if (laivaMahtuuTauluun(laivanSuunta, aloitusXY, laivanKoko, arvotaanLaivoja))
	{

		// tarkastetaan ettei ruuduissa ole toista laivaa. Ei voida lukea laivataulun yli
		// koska sopiminen tauluun tarkastettu edellisessä if lauseessa.
		if (ruudutOvatTyhjia(laivataulu, laivanSuunta, aloitusXY, laivanKoko))
		{
			return true;
		}
		else
		{
			if (!arvotaanLaivoja)
			{
				cout << "Ruuduissa oli jo toinen laiva! Syötä tiedot uudestaan.\n\n";
			}
			return false;
		}

	}
	return false;
}


/*--------------------------------------------------
*
* nimi: laivaMahtuuTauluun
* toiminta: Tarkastaa annettujen parametrien avulla jääkö aloituskoordinaatin ja laudan reunan väliin riittävästi tilaa laivan sijoittamiselle.
* parametri(t): string laivanSuunta, string aloitusXY, int laivanKoko
* paluuarvo(t): palauttaa arvon tosi, jos laiva mahtuu alueelle ja arvon epätosi, jos laiva menee ulos pelialueelta.
*
*--------------------------------------------------*/
bool laivaMahtuuTauluun(string laivanSuunta, string aloitusXY, int laivanKoko, bool arvotaanLaivoja)
{
	// +1 muuten ruutua itseään ei huomioida.
	if (laivanSuunta[0] == 'I' && ('7' - aloitusXY[1] + 1) >= laivanKoko)
	{
		return true;
	}

	else if (laivanSuunta[0] == 'L' && (aloitusXY[1] - '0') >= laivanKoko)
	{
		return true;
	}
	else if (laivanSuunta[0] == 'P' && (aloitusXY[0] - 'A' + 1) >= laivanKoko)
	{
		return true;
	}
	// +1 muuten ruutua itseään ei huomioida.
	else if (laivanSuunta[0] == 'E' && ('G' - aloitusXY[0] + 1) >= laivanKoko)
	{
		return true;
	}
	else {
		if (!arvotaanLaivoja)
		{
			cout << "Laiva ei mahtunut pelilaudalle! Syötä tiedot uudestaan.\n\n";
		}
		return false;
	}
}


/*--------------------------------------------------
*
* nimi: ruudutOvatTyhjia
* toiminta: Tarkastaa ovatko ruudut joihin laivaa ollaan laittamassa tyhjiä. Käy lävitse ko. laivan koon mukaisen määrän ruutuja aloittaen aloitusruudusta ja
*			liikkuen annettuun ilmansuuntaan koon verran ruutuuja.
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], string laivanSuunta, string aloitusXY, int laivanKoko
* paluuarvo(t): Palauttaa arvon tosi, jos laivan reitiltä ei löydy muita laivoja ja epätoden, jos yksikin ruuduista ei ole tyhjä.
*
*--------------------------------------------------*/
bool ruudutOvatTyhjia(int laivataulu[LAUDANKOKO][LAUDANKOKO], string laivanSuunta, string aloitusXY, int laivanKoko)
{
	if (laivanSuunta[0] == 'P')
	{
		for (int i = 0; i < laivanKoko; i++)
		{
			// Annetuissa koordinaateissa ensimmäinen ruutu =1/A, mutta taulukoissa enismmäisen ruudun indeksi onkin 0.
			// ylös mentäessä pienennetään "y koordinaattia"
			if (laivataulu[aloitusXY[0] - 'A' - i][aloitusXY[1] - '1'] != 0)
			{
				return false;
			}
		}
		return true;
	}
	else if (laivanSuunta[0] == 'I')
	{
		for (int i = 0; i < laivanKoko; i++)
		{
			if (laivataulu[aloitusXY[0] - 'A'][aloitusXY[1] - '1' + i] != 0)
			{
				return false;
			}
		}
		return true;
	}
	else if (laivanSuunta[0] == 'E')
	{
		for (int i = 0; i < laivanKoko; i++)
		{
			if (laivataulu[aloitusXY[0] - 'A' + i][aloitusXY[1] - '1'] != 0)
			{
				return false;
			}
		}
		return true;
	}
	else
	{
		for (int i = 0; i < laivanKoko; i++)
		{
			if (laivataulu[aloitusXY[0] - 'A'][aloitusXY[1] - '1' - i] != 0)
			{
				return false;
			}
		}
		return true;
	}
}

/*--------------------------------------------------
*
* nimi: sijLaivaTauluun
* toiminta: Tallentaa laivan ruudut laivatauluun parametreina saadun laivan koon, aloituskoordinaatin ja suunnan avulla.
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], int laivanKoko, string aloitusXY, string laivanSuunta
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
// sijoitetaan laiva taulukkoon tunnistamalla suunta ja kasvatetaan laivaa oikeaan suuntaan.
void sijLaivaTauluun(int laivataulu[LAUDANKOKO][LAUDANKOKO], int laivanKoko, string aloitusXY, string laivanSuunta)
{
	if (laivanSuunta[0] == 'P')
	{
		// tallennetaan annettuun suuntaan aina laivan koon verran ruutuja, 
		for (int i = 0; i < laivanKoko; i++)
		{
			//tallentaen jokaisen ruutuun laivan koon.
			laivataulu[aloitusXY[0] - 'A' - i][aloitusXY[1] - '1'] = laivanKoko;
		}
	}
	else if (laivanSuunta[0] == 'I') {
		for (int i = 0; i < laivanKoko; i++)
		{
			laivataulu[aloitusXY[0] - 'A'][aloitusXY[1] - '1' + i] = laivanKoko;
		}
	}
	else if (laivanSuunta[0] == 'E') {
		for (int i = 0; i < laivanKoko; i++)
		{
			laivataulu[aloitusXY[0] - 'A' + i][aloitusXY[1] - '1'] = laivanKoko;
		}
	}
	else {
		for (int i = 0; i < laivanKoko; i++)
		{
			laivataulu[aloitusXY[0] - 'A'][aloitusXY[1] - '1' - i] = laivanKoko;
		}
	}
}

/*--------------------------------------------------
*
* nimi: tulostaLaivataulu
* toiminta: Tulostaa parametrina annetun laivataulukon mutoiltuna tehtävänannon mukaisesti pelinäkymää varten.
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO]
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void tulostaLaivataulu(int laivataulu[LAUDANKOKO][LAUDANKOKO])
{
	char kirjaimet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', '\0' };

	cout << "    1 2 3 4 5 6 7\n";
	cout << "  -----------------  \n";

	for (int i = 0; i < LAUDANKOKO; i++) {
		cout << kirjaimet[i] << " | ";
		for (int j = 0; j < LAUDANKOKO; j++) {
			cout << laivataulu[i][j] << " ";
		}
		cout << "| " << kirjaimet[i] << endl;
	}

	cout << "  -----------------  \n";
	cout << "    1 2 3 4 5 6 7\n";
}


/////////////////////////////////////////////
// Pelin pelaamiseen liittyvät aliohjelmat //
/////////////////////////////////////////////

/*--------------------------------------------------
*
* nimi: laivojaJaljella
* toiminta: Tarkistaa onko taulukossa laivojenMaarat arvoina vain nollia, jos taulukosta löytyy yksikin nollasta poikkeava luku.
* parametri(t): bool &peliKaynnissa, int laivojenMaarat[LAIVOJENLKM]
* paluuarvo(t): Palauttaa arvon tosi, jos taulukossa on yksikin nollasta poikkeava arvo ja epätosi, jos kaikki arvot ovat nollia.
*
*--------------------------------------------------*/
bool laivojaJaljella(int laivojenMaarat[LAIVOJENLKM])
{
	// jos ei ole enään laivoja niin lopetetaan peli
	for (int i = 0; i < LAIVOJENLKM; i++) {		
		if (laivojenMaarat[i] != 0) {
			return true;
		}
	}
	return false;
}


/*--------------------------------------------------
*
* nimi: tulostaPelilauta
* toiminta: Tulostaa parametrina annetun taulukon pelilauta muotoiltuna tehtävänannon mukaisesti pelinäkymää varten.
* parametri(t): char pelilauta[LAUDANKOKO][LAUDANKOKO]
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void tulostaPelilauta(char pelilauta[LAUDANKOKO][LAUDANKOKO])
{
	char kirjaimet[] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', '\0' };
	cout << "Pelitilanne on seuraava:\n\n";
	cout << "    1 2 3 4 5 6 7\n";
	cout << "  -----------------  \n";

	for (int i = 0; i < LAUDANKOKO; i++)
	{
		cout << kirjaimet[i] << " | ";
		for (int j = 0; j < LAUDANKOKO; j++)
		{
			cout << pelilauta[i][j] << " ";
		}
		cout << "| " << kirjaimet[i] << endl;
	}

	cout << "  -----------------  \n";
	cout << "    1 2 3 4 5 6 7\n\n";
}

/*--------------------------------------------------
*
* nimi: ruutuunOnJoAmmuttu
* toiminta: Tarkastaa onko annetussa koordinaatissa ooleva tuutu tyhjä vais sisältääkö jo jonkun merkin, jolloin siihen on ammuttu.
* parametri(t): string laukausXY, char pelilauta[LAUDANKOKO][LAUDANKOKO]
* paluuarvo(t): Palauttaa arvon epätosi, jos ruudussa on merkki ' ', muute npalauttaa arvon tosi.
*
*--------------------------------------------------*/
bool ruutuunOnJoAmmuttu(string laukausXY, char pelilauta[][LAUDANKOKO])
{

	if (pelilauta[laukausXY[0] - 'A'][laukausXY[1] - '1'] == ' ')
	{
		return false;
	}
	else
	{
		return true;
	}

}

/*--------------------------------------------------
*
* nimi: koordinVirheellinen
* toiminta: Tarkastaa ettei parametrina annettu koordinaatti ole tyhjä tai väärän mittainen. Lisäksi hyväksytään komentojen lyhenteet \@ ja P.
*			Tarkistetaan myös, että 2 merkkiset koordinaatit ovat oikein muotoiltuja ja oikealta alueelta.
* parametri(t): string &laukausXY, char pelilauta[LAUDANKOKO][LAUDANKOKO]
* paluuarvo(t): Palauttaa arvon epätosi, jos koordinaatti on syötetty oikein ja arvon tosi, jos koordinaatin arvo on väärin muotoiltu.
*
*--------------------------------------------------*/
bool koordinVirheellinen(string &laukausXY, char pelilauta[LAUDANKOKO][LAUDANKOKO])
{
	string virhe = "Koordinaatti virheellinen. Syötä uusi koordinaatti.\n\n";

	if (laukausXY.empty())
	{
		cout << virhe;
		return true;
	}

	if (laukausXY.length() < 1 || laukausXY.length() >= 3)
	{
		cout << virhe;
		return true;
	}

	if (laukausXY.length() == 1 && laukausXY[0] == 'P')
	{
		return false;
	}
	else if (laukausXY.length() == 2)
	{
		if ((laukausXY[0] == '\\' && laukausXY[1] == '@'))
		{
			return false;
		}

		// koordinaatti oikein jos kirjain välillä A-G ja numero 1-7 ja ruutu on tyhjä ' '
		else if ((laukausXY[0] >= 'A' && laukausXY[0] <= 'G') && (laukausXY[1] >= '1' && laukausXY[1] <= '7') && (pelilauta[laukausXY[0] - 'A'][laukausXY[1] - '1'] == ' '))
		{
			return false;
		}
		else
		{
			cout << virhe;
			return true;
		}
	}
	else
	{
		cout << virhe;
		return true;
	}
}

/*--------------------------------------------------
*
* nimi: kasitellaanLaukaus
* toiminta: Tarkastaa käyttäjän antaman ampumiskoordinaatin vertaamalla laivataulusta ko. koordinaatista löytyvään numeroon. Jos laivataulusta löytyy nollasta
*			poikkeava luku, tarkistetaan laivojenMaarat taulukosta onko kyseessä olevan laivassa vielä paloja jäljellä ja upotetaan laiva kun viimeiseen palaan
*			osutaan. Osuttaessa vähennetään laivasta aina yksi pala pienentämällä laivojenMaarat taulukon vastaava indeksiä 1llä. 
parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], char pelilauta[LAUDANKOKO][LAUDANKOKO], string laukausXY
* paluuarvo(t): ei ole.
*
*--------------------------------------------------*/
void kasitellaanLaukaus(int laivataulu[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], char pelilauta[LAUDANKOKO][LAUDANKOKO], string laukausXY)
{
	int laukauksenX = laukausXY[1] - '1';
	int laukauksenY = laukausXY[0] - 'A';

	// Osu ja uppos, jos koordinaatissa ei ole 0 ja kohdan laivalla 1 ruutu jäljellä
	if (laivataulu[laukauksenY][laukauksenX] != 0 && laivojenMaarat[laivataulu[laukauksenY][laukauksenX]] == 1)
	{
		cout << "Laukaus kohtaan " << laukausXY << " upotti laivan.\n";

		merkataanUponneeksi(laukauksenX, laukauksenY, laivataulu, pelilauta);

		// vähennetään laivojenmaaraa 1:llä
		laivojenMaarat[laivataulu[laukauksenY][laukauksenX]] = laivojenMaarat[laivataulu[laukauksenY][laukauksenX]] - 1;
	}
	else if (laivataulu[laukauksenY][laukauksenX] != 0)
	{
		cout << "Laukaus kohtaan " << laukausXY << " osui laivaan.\n";

		laivojenMaarat[laivataulu[laukauksenY][laukauksenX]] = laivojenMaarat[laivataulu[laukauksenY][laukauksenX]] - 1;
		pelilauta[laukauksenY][laukauksenX] = '*';
	}
	else
	{
		cout << "Laukaus kohtaan " << laukausXY << " ei osunut.\n";
		pelilauta[laukauksenY][laukauksenX] = 'x';

	}
	cout << endl;
}

/*--------------------------------------------------
*
* nimi: merkataanLaivaUponneeksi
* toiminta: Käy laivataulu lävitse ja kun laivataulusta löytyy sama numero kuin kohdasta johon ammuttiin merkataan pelilautaan tälle kohdalle # merkki.
*			Etsitään siis viimeksi osutun laivan palat ja merkkaa ne uponneiksi laivatauluun.
* parametri(t): int laukauksenX, int laukauksenY, int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO]
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void merkataanUponneeksi(int laukauksenX, int laukauksenY, int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO]) {
	for (int i = 0; i < LAUDANKOKO; i++)
	{
		for (int j = 0; j < LAUDANKOKO; j++)
		{
			if (laivataulu[i][j] == laivataulu[laukauksenY][laukauksenX])
			{
				pelilauta[i][j] = '#';
			}
		}
	}

}


////////////////////////////////////
// Laivojen arpomisen aliohjelmat //
////////////////////////////////////

/*--------------------------------------------------
*
* nimi: arvotaanLaivanSuunta
* toiminta: Arvotaan satunnaiset luvut väliltä 0-6 kuvamaan koordinaatteja ja satunnainen luku 0-4 joka kuvaa suuntaa. Muunnetaan nämä vastaamaan pelin tunnistamaan formaattiin, esim B2 p
* parametri(t): string &laivanSuunta, string &aloitusXY
* paluuarvo(t): ei ole.
*
*--------------------------------------------------*/
void randSijaintiJaSuunta(string &laivanSuunta, string &aloitusXY)
{

	int randX = rand() % LAUDANKOKO;		// arvotaan satunnainen koordinaatti väliltä 0-6
	int randY = rand() % LAUDANKOKO;

	// Sijoitetaan arvottu aloitus xy muuttujaan aloitusXY 
	aloitusXY = char(randY + int('A'));
	aloitusXY += char(randX + int('1'));

	int randSuunta = rand() % 4;		// arvotaan satunnainen koordinaatti väliltä 0-3

	if (randSuunta == 0)
	{
		laivanSuunta = 'P';
	}
	else if (randSuunta == 1)
	{
		laivanSuunta = 'I';
	}
	else if (randSuunta == 2)
	{
		laivanSuunta = 'E';
	}
	else {
		laivanSuunta = 'L';
	}
}

/////////////////////////////
// Simuloinnin aliohjelmat //
/////////////////////////////

/*--------------------------------------------------
*
* nimi: simuloidaanLaukaus
* toiminta: Arvotaan satunnaidet luku väliltä 0-6 ja muunnetaan vastaamaan laudan koordinaatteja.
* parametri(t): string &laukausXY
* paluuarvo(t): ei ole.
*
*--------------------------------------------------*/
void simuloidaanLaukaus(string &laukausXY)
{

	int randX = rand() % LAUDANKOKO;		// arvotaan satunnainen koordinaatti väliltä 0-6
	int randY = rand() % LAUDANKOKO;

	// Sijoitetaan arvottu aloitus xy muuttujaan aloitusXY 
	laukausXY = char(randY + int('A'));
	laukausXY += char(randX + int('1'));
}