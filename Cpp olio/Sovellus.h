#pragma once
#include "Opiskelija.h"
#include "Opettaja.h"
#include "Koulutusohjelma.h"
#include "Koulu.h"
#include "Sovellus.h"

#include <string>

using std::string;

class Sovellus
{
public:
	Sovellus();
	virtual ~Sovellus();
	
	void aja();
	string tulostaValikko() const;

private:
};