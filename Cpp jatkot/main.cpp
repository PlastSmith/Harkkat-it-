#include <iostream>
#include <istream>
#include <string>
#include <cstdlib>
#include <time.h>
#include <thread>
#include <chrono>

#include "vakiot.h"
#include "main.h"


using namespace std;
using namespace this_thread;
using namespace chrono;

int main() {
	bool ohjelmaKaynnissa = true;
	bool voidaanPelata = false;
	int laivataulu[LAUDANKOKO][LAUDANKOKO] = { 0 };
	char pelilauta[LAUDANKOKO][LAUDANKOKO] = {};
	int laivojenMaarat[LAIVOJENLKM] = { 0 };

	alustaLaivojenMaarat(laivojenMaarat);
	alustaPelilauta(pelilauta);

	while (ohjelmaKaynnissa) {
		string valinta = " ";

		tulostaValikko();

		do
		{
			cout << "Valintasi:\n";
			lueKomento(valinta);
			cout << endl;
		} while (valintaVirheellinen(valinta));

		kasitteleValinta(valinta, ohjelmaKaynnissa, laivataulu, pelilauta, laivojenMaarat, voidaanPelata);


	}
	EXIT_SUCCESS;
}



/*--------------------------------------------------
*
* nimi: kasitteleValinta
* toiminta: K‰ytt‰j‰n syˆtteen perusteella k‰ynnist‰‰ valikon toimintoa vastaavan aliohjelman. Huolehtii valikon liikkumisvaihtoehdoista voidaanPelata muuttujan
*			avulla. Pelaaminen, simulointi ja tallentamine vaativat voidaanPelata=tosi.
* parametri(t): string &valinta, bool& ohjelmaKaynnissa, int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void kasitteleValinta(string &valinta, bool& ohjelmaKaynnissa, int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata)
{
	if (valinta[0] == '1')
	{
		sijoitellaanLaivat(laivataulu, pelilauta, laivojenMaarat, voidaanPelata);
		return;
	}
	else if (valinta[0] == '2')
	{
		if (voidaanPelata)
		{
			pelaaPelia(laivataulu, pelilauta, laivojenMaarat, voidaanPelata);
		}
		else
		{
			cout << "Peli‰ ei voida pelata, koska laivoja ei ole asetettu.\n\n";
		}
	}
	else if (valinta[0] == '3')
	{
		arvoLaivojenSijainti(laivataulu, pelilauta, laivojenMaarat, voidaanPelata);
	}
	else if (valinta[0] == '4')
	{
		if (voidaanPelata)
		{
			tallennaPeli(laivataulu, pelilauta, laivojenMaarat);
		}
		else
		{
			cout << "Peli‰ ei voida tallentaa, koska peli‰ ei ole k‰ynniss‰ tai peli on jo p‰‰ttynyt.\n\n";
		}

	}
	else if (valinta[0] == '5')
	{
		lataaPelitilanne(laivataulu, pelilauta, laivojenMaarat, voidaanPelata);

	}
	else if (valinta[0] == '6')
	{
		// simuloi uuden pelin tai nykyisen pelin loppuun jos molemmat pelilaudat ok ja tai pleiapelataan
		if (voidaanPelata)
		{
			simuloiPeli(laivataulu, pelilauta, laivojenMaarat, voidaanPelata);
		}
		else
		{
			cout << "K‰ynniss‰ ei ole peli‰, jota voitaisiin simuloida.\n\n";
		}

	}
	else // L kirjaitna ei tarvitse tarkastaa, koska ainoa j‰ljell‰ oleva
	{
		ohjelmaKaynnissa = false;
	}
}


/////////////////////////////////////////
// Laivojen sijoittamisen toteuttaminen//
/////////////////////////////////////////
/*--------------------------------------------------
*
* nimi: syotetaanLaivat
* toiminta: Alustaa taulut laivataulu, pelilauta ja laivojenM‰‰r‰t. Lukee laivan koordinaatin sek‰ suunnan k‰ytt‰j‰lt‰ kunnes aliohjelmat koordinaattiMuotoiltuOikein,
*			suuntaMuotoiltuOikein ja !laivaSopiiLaudalle hyv‰ksyv‰t sen. T‰m‰n j‰lkeen laivataulu sijoitetaan laivatauluun, pienennet‰‰n laivan koon kertovaa muuttujaa
*			ja siirrtyt‰‰n seuraavalle kierrokselle. Kun kaikki laivat on saatu sijoiteltua laivatauluun, asetetaan voidaanPelata arvoon tosi, jotta peli‰ voidaan
*			siirty‰ pelaamaan p‰‰valikon kautta.
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata
* paluuarvo(t): ei ole.
*
*--------------------------------------------------*/
void sijoitellaanLaivat(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata) {
	int laivanKoko = 5;
	bool arvotaanLaivoja = false;	// vai virhe tulostusten hallintaan
	string laivanSuunta;
	string aloitusXY;
	alustaLaivataulu(laivataulu);
	alustaPelilauta(pelilauta);
	alustaLaivojenMaarat(laivojenMaarat);

	while (laivanKoko >= 2)
	{
		do
		{
			cout << "Anna " << laivanKoko << " pituisen laivan alkupiste: \n";
			lueKomento(aloitusXY);

			cout << "Anna suunta(p(ohjoinen) / i(ta) / e(tela) / l(ansi)) : \n";
			lueKomento(laivanSuunta);

			cout << endl;
		} while (koordVirheellinen(aloitusXY) || suuntaVirheellinen(laivanSuunta) || !laivaSopiiLaudalle(laivataulu, laivanSuunta, aloitusXY, laivanKoko, arvotaanLaivoja));

		sijLaivaTauluun(laivataulu, laivanKoko, aloitusXY, laivanSuunta);
		laivanKoko--;
		tulostaLaivataulu(laivataulu);
		cout << endl;
	}
	voidaanPelata = true;
}

////////////////////////////////////
// Pelin pelaamisen toteuttaminen //
////////////////////////////////////
/*--------------------------------------------------
*
* nimi: pelaaPelia
* toiminta: Pelataan kierros kunnes laivat loppuvat. Joka kierroksella pyydet‰‰n k‰ytt‰j‰lt‰ ampumiskoordinaattia niin kauan kuin aliohjelmalla koordinVirheellinen
*			sen hyv‰ksyy. Hyv‰ksytty ampumiskoordinaatti k‰sitell‰‰n joko komentona ('P'), vakoiluna '\@' tai laukauksena. Laukaus k‰sitell‰‰n aliohjelmalla
*			kasitellaanLaukaus.
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata
* paluuarvo(t): ei ole.
*
*--------------------------------------------------*/
void pelaaPelia(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata) {

	string laukausXY;

	while (laivojaJaljella(laivojenMaarat))
	{
		tulostaPelilauta(pelilauta);

		do
		{
			cout << "Anna ampumiskoordinaatit: ";
			lueKomento(laukausXY);
			cout << endl;
		} while (koordinVirheellinen(laukausXY, pelilauta));	//muotoa a1 tai a10, \@, P, ei tyhj‰ 

		if (laukausXY[0] == 'P') {
			return;
		}
		// oltava \@ vakoilu
		else if (laukausXY[0] == '\\' && laukausXY[1] == '@')
		{
			tulostaLaivataulu(laivataulu);
			cout << endl;
		}
		else
		{
			kasitellaanLaukaus(laivataulu, laivojenMaarat, pelilauta, laukausXY);
		}
	}
	tulostaPelilauta(pelilauta);
	cout << endl;
	cout << "Onneksi olkoon! Upotit kaikki laivat!\n\n";
	voidaanPelata = false;
}

//////////////////////////////////////
// Laivojen arpomisen toteuttaminen //
//////////////////////////////////////
/*--------------------------------------------------
*
* nimi: arvoLaivojenSijainti
* toiminta: Alustetaan laivaTaulu, pelilauta ja laivojenMaarat, koska aloitetaan uusi peli. Niin kauan kuin syˆte on v‰‰rin arvotaan uusi sijainti ja suunta,
*			jos arvotuilla arvoilla laiva sopii laudalle, sijoitetaan se laivatauluun ja siirryt‰‰n k‰sittelem‰‰n seuraavan kokoluokan laivaa. Kun kaikki
*			laivat on saatu sijoiteltua laivatauluun, asetetaan voidaanPelata arvoon tosi ja siirryt‰‰n takaisin p‰‰valikkoon.
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void arvoLaivojenSijainti(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata)
{
	bool arvotaanLaivoja = true; // virheiden tulostuksen hallintaan aliohjelmass laivaSopiiLAudalle
	int laivanKoko = 5;
	string laivanSuunta;
	string aloitusXY;

	alustaLaivataulu(laivataulu);
	alustaPelilauta(pelilauta);
	alustaLaivojenMaarat(laivojenMaarat);

	while (laivanKoko >= 2)
	{
		srand(time(0));	// antaa varoituksen, mutta luentoaineistossa toteutettu samalla tavalla. t‰ss‰ ei v‰li‰ koska tarvitaan vain jokin luku.

		do
		{
			randSijaintiJaSuunta(laivanSuunta, aloitusXY);
		} while (!laivaSopiiLaudalle(laivataulu, laivanSuunta, aloitusXY, laivanKoko, arvotaanLaivoja) || !ruudutOvatTyhjia(laivataulu, laivanSuunta, aloitusXY, laivanKoko));

		sijLaivaTauluun(laivataulu, laivanKoko, aloitusXY, laivanSuunta);
		laivanKoko--;

	}
	voidaanPelata = true;
}


//////////////////////
// Pelin Simulointi //
//////////////////////
/*--------------------------------------------------
*
* nimi: simuloiPeli
* toiminta: Niin kauan kuin laivoja on j‰ljell‰ simuloidaan laukaus, jos ruutuun ei ole aikaisemmin ammuttu k‰sitell‰‰n se aliohjelmalla k‰sitell‰‰nLaukaus, 
*			jos taas ruutuun on jo ammuttu, simuloidaan uusi laukaus. Koodiin on sijoitettu muutama sleep_for(seconds(x)) funktio, joilla hidastetaan tulostusta.
* parametri(t): int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata
* paluuarvo(t): ei ole
*
*--------------------------------------------------*/
void simuloiPeli(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata)
{
	string laukausXY;

	tulostaPelilauta(pelilauta);

	sleep_for(seconds(1));

	while (laivojaJaljella(laivojenMaarat))
	{
		srand(time(0));	// antaa varoituksen, mutta luentoaineistossa toteutettu samalla tavalla. t‰ss‰ ei v‰li‰ koska tarvitaan vain jokin luku.
		do
		{
			simuloidaanLaukaus(laukausXY);

		} while (ruutuunOnJoAmmuttu(laukausXY, pelilauta));


		kasitellaanLaukaus(laivataulu, laivojenMaarat, pelilauta, laukausXY);
		tulostaPelilauta(pelilauta);
		sleep_for(seconds(1));

	}
	cout << "Onneksi olkoon! Upotit kaikki laivat!\n\n";
	sleep_for(seconds(3));
}