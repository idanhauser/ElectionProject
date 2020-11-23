#pragma once
namespace elec
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