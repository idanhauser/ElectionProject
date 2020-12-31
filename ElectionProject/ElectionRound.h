//code verison 2.5
#pragma once
#include "resultsArr.h"


#include "DistrictList.h"
#include "PartyList.h"
#include "Citizen.h"
#include "District.h"

using namespace std;



namespace elec {
	class LoadElectionSystem;
	class DistrictList;
	class PartyList;

	class ElectionRound
	{
	protected:
		int _date[DATE_SIZE];

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
		ElectionRound(int date[DATE_SIZE]);
		virtual ~ElectionRound() = default;
				
	explicit ElectionRound(LoadElectionSystem& loader);
	
		/// <summary>
		/// virtual function for adding a districts.
		/// </summary>
		/// <param name="name">the name of the dist</param>
		/// <param name="numberRepresentatives">number of reps in dists</param>
		/// <param name="districtId">the id of dist</param>
		virtual	bool addNewDistrict(const char str[MAX_SIZE], int number_representatives, int& districtId, DistcritType districtType) = 0;

		/// <summary>
		/// returns the date
		/// </summary>
		/// <returns>returns the date</returns>
		constexpr int getYear() const
		{
			int year = _date[DATE_SIZE - 1];
			year += _date[DATE_SIZE - 2] * 10;
			year += _date[DATE_SIZE - 3] * 100;
			year += _date[DATE_SIZE - 4] * 1000;
			return year;

		}

		/// <summary>
		///	Adding a new citizen to a district.
		/// </summary>
		/// <param name="name">a name of the citizen</param>
		/// <param name="id">the ID of the citizen</param>
		/// <param name="birthyear">the birth year of the citizen</param>
		/// <param name="districtId">the Id of the district</param>
		/// <returns>returns true if citizen was added, else false</returns>
		bool addNewCitizen(const char* name, int id, int birthyear, int districtId);
		/// <summary>
		///Adding a new party to the election system.
		/// </summary>
		/// <param name="name">name of the party</param>
		/// <param name="pdId">the id of the party leader</param>
		/// <param name="partyId">the id of the party</param>
		/// <returns>returns true if party was added, else false</returns>
		bool addNewParty(const char* name, int pdId, int& partyId);
		/// <summary>
		///Adding a new party representatives to a party.
		/// </summary>
		/// <param name="representId">the ID of the citizen</param>
		/// <param name="partyId">the ID of the party</param>
		/// <param name="districtId">the district id of the dist the citizen live in</param>
		/// <returns>returns true if party's rep was added, else false</returns>
		bool addNewPartyRepresentative(int representId, int partyId, int districtId);
		/// <summary>
		/// prints all the Districts
		/// </summary>
		void viewAllDistricts();
		/// <summary>
		/// prints all the citizens
		/// </summary>
		void viewAllCitizens() const;
		/// <summary>
		/// prints all the parties
		/// </summary>
		void viewAllParties() const;
		/// <summary>
		/// adding a vote of a person to the party
		/// </summary>
		/// <param name="citizenId">the ID of citizen</param>
		/// <param name="partyId">the ID of the voted party</param>
		/// <returns>returns true if vote was added, else false</returns>
		bool votingAction(int citizenId, int partyId);
		/// <summary>
		/// Calculate and view the election results.
		/// </summary>
		/// <returns>returns true if can calculate, else false</returns>
		bool theResults();
		/// <summary>
		/// Saving election to file
		/// </summary>
		/// <param name="fileName">the name of the file we want to </param>
		virtual void save(ofstream& outFile) const =0;

		///utils:
		/// <summary>
		/// printing the date of the election
		/// </summary>
		void printElectionDate(ostream& os) const;
	private:

		/// <summary>
		/// swap between two pairs.
		/// </summary>
		/// <param name="xp">the first pair</param>
		/// <param name="yp">the second pair</param>
		void swap(pair* xp, pair* yp);

		/// <summary>
		/// bubble sorting
		/// </summary>
		/// <param name="arr">arr of pairs to be sorted</param>
		/// <param name="n">number of element in the arr</param>
		void bubbleSort(pair arr[], int n);
		/// <summary>
		/// deletes the max cell in arr 
		/// </summary>
		/// <param name="parr">arr of pairs</param>
		/// <param name="size">the size of the arr</param>
		/// <returns> the index maximum pair</returns>
		//int  deleteMax(double* parr, int size);
		



		//bool VotesToRepsInDistrictByDistrictID(int districtID); //todo:roee move to results
		bool setWinnerInUnifiedDistrictByDistrictID(int districtID, int repsAmount); //todo roee: move to results
		bool checkElectionsWinner(int* partiesIndexes);
		bool sortDistrictWinners(int districtID, int* partiesIndexes);
		bool isResultsAllowed() const;

		bool calcReps();

		friend ostream& operator<<(ostream& os, ElectionRound& electionRound);


		
	};


}
