#pragma once
#include <iostream>
#include <ostream>
#include "Party.h"
#include "District.h"
#include "Citizen.h"
using namespace elec;
using namespace std;

namespace elecMain
{


	enum class Menu_Choices
	{
		addDistrict = 1,
		addCitizen,
		addParty,
		addPartyRepresentative,
		viewCountie,
		viewCitizens,
		viewParties,
		voting,
		results,
		exit_menu
	};

	 void mainMenu();

	void addDistrict();
	void addCitizen();
	void addParty();
	void addPartyRepresentative();
	void viewCountie();
	void viewParties();
	void voting();
	void results();

	
}