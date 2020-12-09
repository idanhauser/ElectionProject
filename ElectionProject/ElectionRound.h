//code verison 1.0
#pragma once
#include "resultsArr.h"


#include "DistrictList.h"
#include "PartyList.h"
#include "Citizen.h"
#include "District.h"

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
		resultsArr results;
		DistrictList _districts;
		PartyList _parties;
		CitizenList _citizens; //_citizens should be deleted
		
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
		void votingAction(CitizenList& _citizens, resultsArr& results);//todo:roee // check if results refrence is fine
		void theResults(resultsArr& results);//todo:roee
		int checkWinningPMInDistrict(int districtID, resultsArr results);//inside theResults
		int checkWinnigPMRepsAmountInDistrict(resultsArr repsCountArr, int districtId);//inside theResults
		int checkTotalPartyVotesAmount(resultsArr results, int partyID);//inside theResults
		int checkWinningPMInDistrict(int districtID, resultsArr results) {
			int max = 0;
			int cur;
			int winnerPartyPmID = 0;
			for (int j = 0; j < _parties.getLogicSize(); j++) {
				cur = results.getPMNumberOfRepsInDistrict(j, districtID);
				if (max < cur) {
					max = cur;
					winnerPartyPmID = j;
				}
			}
			return winnerPartyPmID;
		}
		int checkWinnigPMRepsAmountInDistrict(resultsArr repsCountArr, int districtId) {// todelete
			int count = 0;
			for (int i = 0; i < _parties.getLogicSize(); i++) {
				count = count + repsCountArr.getPMNumberOfRepsInDistrict(i, districtId);
			}
			return count;
		}
		int checkTotalPartyVotesAmount(resultsArr results, int partyID) {
			int count = 0;
			for (int i = 0; i < _parties.getLogicSize(); i++) {
				count = count + results.getDistrictNumberOfVotesInParty(i + 100, partyID);
			}
			return count;
		}

	};
}