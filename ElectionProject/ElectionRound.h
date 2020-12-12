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
		struct pair {
			int index;
			int repsAmount;
		};
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
		void votingAction();
		void theResults();



		
		//--------roee
		bool votingAction(int citizenId, int partyId);
		void theResults(resultsArr& results);
		int checkWinningPMInDistrict(int districtID, resultsArr results);//inside theResults
		int checkWinnigPMRepsAmountInDistrict(resultsArr repsCountArr, int districtId);//inside theResults
		int checkTotalPartyVotesAmount(resultsArr results, int partyID);//inside theResults

		//TODO: ROEE need to check if to delete or not
		//int checkWinningPMInDistrict(int districtID, resultsArr results);	
		//int checkWinnigPMRepsAmountInDistrict(resultsArr repsCountArr, int districtId);//to delete
		//int checkTotalPartyVotesAmount(resultsArr results, int partyID);
		void swap(pair* xp, pair* yp);
		void bubbleSort(pair arr[], int n);
	};
}