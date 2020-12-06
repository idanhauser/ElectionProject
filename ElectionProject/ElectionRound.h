//code verison 1.0
#pragma once
#include "Citizen.h"
#include "resultsArr.h"
#include "DistrictList.h"
#include "District.h"
#include "Party.h"

using namespace std;



namespace elec {
	//idan todo: need to add an operator to print the election round.
	class DistrictList;
	class CitizenList;
	class PartyList;

	class Citizen;
	class Party;


	class ElectionRound
	{
	private:
		int _date[8];
		int _citizenID;
		int _PartyID;

		DistrictList& _districts;
		CitizenList& _citizens;
		PartyList& _parties;

		
		const ElectionRound& operator=(const ElectionRound&);

	public:


		ElectionRound() = delete;
		ElectionRound(int date[8]);
		~ElectionRound() = default;





		void printElectionDate() const;

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
		void addNewDistrict();
		void addNewCitizen();
		void addNewParty();
		void addNewPartyRepresentative();
		void viewAllDistricts();
		void viewAllCitizens();
		void viewAllParties();
		void votingAction(CitizenList _citizens);//todo:roee
		void theResults();//todo:roee
		int checkWinnerInDistrict(int districtID, resultsArr results);
		int checkWinnigPM(int* TotalPMsRepsArr);

	};
}