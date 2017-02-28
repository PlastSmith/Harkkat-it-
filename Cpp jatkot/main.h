#pragma once

// main ja valikot
void alustaLaivojenMaarat(int laivojenMaarat[LAIVOJENLKM]);
void alustaPelilauta(char[LAUDANKOKO][LAUDANKOKO]);
void tulostaValikko();
void lueKomento(std::string &komento);
bool valintaVirheellinen(std::string &valinta);
void kasitteleValinta(std::string &valinta, bool &ohjelmaKaynnissa, int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata);
void sijoitellaanLaivat(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata);
void pelaaPelia(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata);
void arvoLaivojenSijainti(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata);
void tallennaPeli(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM]);
void lataaPelitilanne(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata);
void simuloiPeli(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], bool &voidaanPelata);

// Laivojen asettaminen
void alustaLaivataulu(int[LAUDANKOKO][LAUDANKOKO]);
bool koordVirheellinen(std::string laivanSuunta);
bool suuntaVirheellinen(std::string laivanSuunta);
bool laivaSopiiLaudalle(int laivataulu[LAUDANKOKO][LAUDANKOKO], std::string laivanSuunta, std::string aloitusXY, int laivanKoko, bool arvotaanLaivoja);
void sijLaivaTauluun(int laivataulu[LAUDANKOKO][LAUDANKOKO], int laivoja, std::string aloitusXY, std::string laivanSuunta);
void tulostaLaivataulu(int[LAUDANKOKO][LAUDANKOKO]);

// Pelin pelaaminen
bool laivojaJaljella(int laivojenMaarat[LAIVOJENLKM]);
void tulostaPelilauta(char[LAUDANKOKO][LAUDANKOKO]);
bool koordinVirheellinen(std::string &laukausXY, char pelilauta[LAUDANKOKO][LAUDANKOKO]);
void kasitellaanLaukaus(int laivataulu[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM], char pelilauta[LAUDANKOKO][LAUDANKOKO], std::string laukausXY);

// Laivojen arpominen
void randSijaintiJaSuunta(std::string &laivanSuunta, std::string &aloitusXY);
bool ruudutOvatTyhjia(int laivataulu[LAUDANKOKO][LAUDANKOKO], std::string laivanSuunta, std::string aloitusXY, int laivanKoko);

// Simulointi
void simuloidaanLaukaus(std::string &laukausXY);
bool ruutuunOnJoAmmuttu(std::string laukausXY, char pelilauta[][LAUDANKOKO]);
