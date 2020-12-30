//code verison 2.0
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
	protected:
		int _date[8];

		DistrictList _districts;
		PartyList _parties;
		resultsArr _results;
		int NoChangeSinceLastCalc;

		const ElectionRound& operator=(const ElectionRound&);

	public:
		struct pair {
			int index;
			double repsAmount;
		};
		ElectionRound() = delete;
		ElectionRound(int date[8]);
		~ElectionRound() = default;

		void printElectionDate() const;
		bool addNewDistrict(const char str[MAX_SIZE], int number_representatives,int& districtId, int DistrictType);

		
		constexpr int getYear() const
		{
			int year = _date[7];
			year += _date[6] * 10;
			year += _date[5] * 100;
			year += _date[4] * 1000;
			return year;

		}


		bool addNewCitizen(const char* name,int id,int birtyear,int districtId);
		bool addNewParty(const char* name, int pdId,int& partyId);
		bool addNewPartyRepresentative(int representId,int partyId,int districtId);
		void viewAllDistricts();
		bool calcReps();
		void viewAllCitizens() const;
		void viewAllParties() const;
		bool votingAction(int citizenId, int partyId);
		bool theResults();



		

		void swap(pair* xp, pair* yp);
		void bubbleSort(pair arr[], int n);
	
	
		//bool VotesToRepsInDistrictByDistrictID(int districtID); //todo: move to results
		bool setWinnerInUnifiedDistrictByDistrictID(int districtID, int repsAmount); //todo: move to results
		bool checkElectionsWinner(int* partiesIndexes); 
		bool sortDistrictWinners(int districtID, int* partiesIndexes); 
		bool isResultsAllowed()const;



		friend ostream& operator<<(ostream& os, ElectionRound& electionRound);

	
	
	};


}
