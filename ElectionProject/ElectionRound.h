//code verison 1.0
#pragma once


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
		DistrictList _districts;
		PartyList _parties;

		const ElectionRound& operator=(const ElectionRound&);

	public:
		ElectionRound() = default;
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
		void addNewPartyRepresentative();
		void viewAllDistricts() const;
		void viewAllCitizens() const;
		void viewAllParties() const;
		void votingAction();//todo:roee
		void theResults();//todo:roee



	};

}