//code verison 1.0
#pragma once

#include "CitizenList.h"
#include "DistrictList.h"
#include "PartyList.h"
#include "District.h"


using namespace std;



namespace elec {
	class DistrictList;
	class CitizenList;
	class PartyList;
	
	class ElectionRound
	{
	private:
		int _date[8];
		DistrictList _districts;
		CitizenList _citizens;
		PartyList _parties;

	const ElectionRound& operator=(const ElectionRound&);

	public:
		ElectionRound()=default;
		ElectionRound(int date[8]);
		~ElectionRound() = default;

		void printElectionDate() const;
		void addNewDistrict(char str[1024], int number_representatives);

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

		void addNewCitizen();
		void addNewParty();
		void addNewPartyRepresentative();
		void viewAllDistricts();
		void viewAllCitizens();
		void viewAllParties();
		void votingAction();//todo:roee
		void theResults();//todo:roee



	};

}