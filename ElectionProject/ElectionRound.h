#pragma once


using namespace std;



namespace elec {
	//idan todo: need to add an operator to print the election round.
	class DistrictList;
	class CitizenList;
	class PartyList;
	
	class ElectionRound
	{
	private:
		int _date[8];

	/*	DistrictList &_districts;
		CitizenList &_citizens;
		PartyList &_parties;
		*/

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
		void votingAction();//todo:roee
		void theResults();//todo:roee



	};

}