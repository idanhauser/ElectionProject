#pragma once
#pragma  warning(disable:4996)
#include <iostream>
#include <ostream>


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

	void showMainMenu();
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

