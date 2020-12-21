//code verison 2.0
#pragma once
#pragma  warning(disable:4996)
#include <ostream>
#include <iostream>



using namespace std;


namespace elec
{
	const int DISTRICT_ID_INIT = 100;
	const int PARTY_ID_INIT = 0;
	const int MAX_SIZE = 1024;

	enum class Menu_Choices
	{
		addDistrict = 1,
		addCitizen,
		addParty,
		addPartyRepresentative,
		viewDistricts,
		viewCitizens,
		viewParties,
		voting,
		results,
		exit_menu
	};




}

