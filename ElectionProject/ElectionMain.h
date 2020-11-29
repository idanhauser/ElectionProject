#pragma once
#pragma  warning(disable:4996)
#include <iostream>
#include <ostream>
#include "Party.h"
#include "District.h"
#include "Citizen.h"
using namespace elec;
using namespace std;

namespace elec
{
	const int MAX_SIZE = 1024;

	Citizen**& reallocCitizenArray(Citizen** old_memory, int old_size, int new_size);
}
//TODO:To watch keren about maneger class..its going to be changed
namespace elecMain
{
	//TODO: i have a lot of errors here...we need to check it , i dont know what to do here...
	/*District** districts = new District*[MAX_SIZE];
	//Citizen** elCitizens=new Citizen*[MAX_SIZE];
	Party** parties = new Party*[MAX_SIZE];
	*

	int phySizeCitizens=MAX_SIZE;
	int logiSizeCitizens=0;

	int phySizeParties=MAX_SIZE;
	int logiSizeParties=0;


	int phySizedistricts=MAX_SIZE;
	int logiSizedistricts=0;
	*/
	//	int electionDate[8] = { 2,1,0,8,1,0,4,0 };//TODO : roee how do you want to manage the date? i dont understand. and also need to check where is get the date from.
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

	void mainMenu();
	void addDistrict();
	void addCitizen();
	void addParty();
	void addPartyRepresentative();
	void viewDistricts();
	void viewCitizens();
	void viewParties();
	void voting();//todo:roee
	void results();//todo:roee


}

