//code verison 3.0
#pragma once
#pragma  warning(disable:4996)
#include <ostream>
#include <vector>


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


	//for first menu
	enum class ElectionType
	{
		RegularElectionRound = 1,
		SimpleElectionRound
	};



	enum class DistcritType
	{
		
		UnifiedDistrict =1,
		DividedDistrictType,
	};


	enum class Months
	{

		January = 1,
		February,// has 28 days(29 days in leap yers)
		March,// has 31 days
		April,// has 30 days
		May,// has 31 days
		June,// has 30 days
		July,// has 31 days
		August,// has 31 days
		September, //has 30 days
		October ,//has 31 days
		November,//has 30 days
		December,
	};
	const vector<string> MONTHS_NAME = {
		"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November",
		"December"
	};


	
}

