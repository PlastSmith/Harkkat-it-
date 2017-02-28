// main ja valikot
bool tallKomMuotVaarin(std::string komento);

// Laivojen asettaminen
void kirjaimetIsoiksi(std::string &merkkijono);
bool laivaMahtuuTauluun(std::string laivanSuunta, std::string aloitusXY, int laivanKoko, bool arvotaanLaivoja);
bool ruudutOvatTyhjia(int laivataulu[LAUDANKOKO][LAUDANKOKO], std::string laivanSuunta, std::string aloitusXY, int laivanKoko);

// pelin pelaaminen
void merkataanUponneeksi(int laukauksenX, int laukauksenY, int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO]);

// Pelitilanteen tallentaminen
bool tiedostoOlemassa();
void tallenna(int laivataulu[LAUDANKOKO][LAUDANKOKO], char pelilauta[LAUDANKOKO][LAUDANKOKO], int laivojenMaarat[LAIVOJENLKM]);