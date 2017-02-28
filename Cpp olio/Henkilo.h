#pragma once
#include<string>

class Henkilo
{
public:
	Henkilo();
	Henkilo(std::string enimi, std::string snimi, std::string osoite, std::string puhnro);
	Henkilo(const Henkilo &alkup);
	Henkilo& operator = (const Henkilo& alkup); // = uudelleen m‰‰rittely
	virtual ~Henkilo();

	void kysyTiedot();
	void tulosta() const;
	
	std::string annaEtunimi() const;  // rutiini jota voi k‰ytt‰‰ vakio viittauksena ja oliona ik‰‰n kuin read only
	std::string annaOsoite() const;
	std::string annaPuhelinnumero() const;
	std::string annaSukunimi() const;

	void asetaEtunimi(std::string);	// ei const koska muokataan!
	void asetaOsoite(std::string);
	void asetaPuhelinnumero(std::string);
	void asetaSukunimi(std::string);

private:
	std::string etunimi_;
	std::string sukunimi_;
	std::string osoite_;
	std::string puhelinnumero_;
	
};

