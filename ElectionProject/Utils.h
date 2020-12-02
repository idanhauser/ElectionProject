#pragma once
#pragma  warning(disable:4996)
#include <iostream>
#include <ostream>

#include "Citizen.h"
class District;
class Citizen;
class Party;

using namespace std;


namespace elec
{
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

