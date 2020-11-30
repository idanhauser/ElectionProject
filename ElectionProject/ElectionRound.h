#pragma once

using namespace std;


namespace elec {

	class ElectionRound
	{
		

		int _date[8];
	public:
		ElectionRound(int date[8]);
		~ElectionRound()=default;
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

		//void showMainMenu();
		void addDistrict();
		void addCitizen();
		void addParty();
		void addPartyRepresentative();
		void viewDistricts();
		void viewCitizens();
		void viewParties();
		void voting();//todo:roee
		void results();//todo:roee


		
	};

}