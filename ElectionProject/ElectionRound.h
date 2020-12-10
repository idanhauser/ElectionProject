//code verison 1.0
#pragma once
#include "resultsArr.h"


#include "DistrictList.h"
#include "PartyList.h"
#include "Citizen.h"
#include "District.h"

using namespace std;



namespace elec {
	class DistrictList;
	class PartyList;
	
	class ElectionRound
	{
	private:
		int _date[8];
		resultsArr _results;
		DistrictList _districts;
		PartyList _parties;

		const ElectionRound& operator=(const ElectionRound&);

	public:
		ElectionRound() = delete;//todo:idan delete or defult?
		ElectionRound(int date[8]);
		~ElectionRound() = default;

		void printElectionDate() const;
		bool addNewDistrict(char str[MAX_SIZE], int number_representatives,int& districtId);

		
		constexpr int getYear() const
		{
			int year = _date[7];
			year += _date[6] * 10;
			year += _date[5] * 100;
			year += _date[4] * 1000;
			return year;

		}


		bool addNewCitizen(char* name,int id,int birtyear,int districtId);
		bool addNewParty(char* name, int pdId,int& partyId);
		bool addNewPartyRepresentative(int representId,int partyId,int districtId);
		void viewAllDistricts() const;
		void viewAllCitizens() const;
		void viewAllParties() const;
		void votingAction();//todo:roee
		void theResults();//todo:roee


		////void showMainMenu();
		//void addNewDistrict();
		//void addNewCitizen();
		//void addNewParty();
		//void addNewPartyRepresentative();
		//void viewAllDistricts();
		//void viewAllCitizens();
		//void viewAllParties();

		
		//--------roee
		void votingAction(CitizenList& _citizens, resultsArr& results);//todo:roee // check if results refrence is fine
		void theResults(resultsArr& results);//todo:roee
		int checkWinningPMInDistrict(int districtID, resultsArr results);//inside theResults
		int checkWinnigPMRepsAmountInDistrict(resultsArr repsCountArr, int districtId);//inside theResults
		int checkTotalPartyVotesAmount(resultsArr results, int partyID);//inside theResults
	/*	int checkWinningPMInDistrict(int districtID, resultsArr results) {
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
		*/
	};
}