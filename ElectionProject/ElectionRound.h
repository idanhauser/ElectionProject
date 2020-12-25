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

		const ElectionRound& operator=(const ElectionRound&);

	public:
		struct pair {
			int index;
			double repsAmount;
		};
		ElectionRound() = delete;
		ElectionRound(int date[DATE_SIZE]);
		virtual ~ElectionRound() = default;

		void printElectionDate() const;
		virtual	bool addNewDistrict(const char str[MAX_SIZE], int number_representatives, int& districtId) = 0;


		constexpr int getYear() const
		{
			int year = _date[DATE_SIZE - 1];
			year += _date[DATE_SIZE - 2] * 10;
			year += _date[DATE_SIZE - 3] * 100;
			year += _date[DATE_SIZE - 4] * 1000;
			return year;

		}


		bool addNewCitizen(const char* name, int id, int birthyear, int districtId);
		bool addNewParty(const char* name, int pdId, int& partyId);
		bool addNewPartyRepresentative(int representId, int partyId, int districtId);
		void viewAllDistricts() const;
		void viewAllCitizens() const;
		void viewAllParties() const;
		bool votingAction(int citizenId, int partyId);
		bool theResults();





		void swap(pair* xp, pair* yp);
		void bubbleSort(pair arr[], int n);
		int  deleteMax(double* parr, int size);
	};


}
