//code verison 2.0
#pragma once
#pragma  warning(disable:4996)
#include <ostream>
#include <iostream>
using namespace std;


namespace elec
{
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
	//change these values if you want to change the init ids for dists and partis.
	const int DISTRICT_ID_INIT = 100;
	const int PARTY_ID_INIT = 0;

	//consts
	const int MAX_SIZE = 1024;
	const int DATE_SIZE = 8;

	//for main menu
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
		exit_menu,
		saveElection,
		loadElection
	};

	//for first menu
	enum class Start_MenuChoices
	{
		startNewElectionRound = 1,
		loadElection,
		exit_menu
	};


}

