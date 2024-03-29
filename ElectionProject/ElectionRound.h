﻿//code verison 3.2
#pragma once
#include "resultsArr.h"
#include <string>
#include "Party.h"
#include "Citizen.h"
#include "District.h"
#include <algorithm>
using namespace std;



namespace elec {
	class LoadElectionSystem;

	class ElectionRound
	{
	protected:
		int _dateDay;
		int _dateMonth;
		int _dateYear;
		vector<District*> _districts;
		vector<Party*> _parties;
		resultsArr _results;
		int NoChangeSinceLastCalc; //flag to check if current and last calculation of results is the same

		const ElectionRound& operator=(const ElectionRound&);



	public:
		ElectionRound() = delete;
		void setDate(int date_d, int date_m, int date_y) noexcept(false);
		ElectionRound(int date_d, int date_m, int date_y) noexcept(false);
		virtual ~ElectionRound();

		explicit ElectionRound(LoadElectionSystem& loader);

		/// <summary>
		/// virtual function for adding a districts.
		/// </summary>
		/// <param name="name">the name of the dist</param>
		/// <param name="numberRepresentatives">number of reps in dists</param>
		/// <param name="districtId">the id of dist</param>
		virtual	void addNewDistrict(string& name, int numbeRepresentatives, int& districtId, DistcritType districtType);

		/// <summary>
		/// returns the date
		/// </summary>
		/// <returns>returns the date</returns>
		constexpr int getYear() const
		{
			return _dateYear;
		}

		/// <summary>
		///	Adding a new citizen to a district.
		/// </summary>
		/// <param name="name">a name of the citizen</param>
		/// <param name="id">the ID of the citizen</param>
		/// <param name="birthYear">the birth year of the citizen</param>
		/// <param name="districtId">the Id of the district</param>


		void addNewCitizen(string& name, int id, int birthYear, int districtId) noexcept(false);
		/// <summary>
		///Adding a new party to the election system.
		/// </summary>
		/// <param name="name">name of the party</param>
		/// <param name="pdId">the id of the party leader</param>
		/// <param name="partyId">the id of the party</param>
		/// <returns>returns true if party was added, else false</returns>
		void addNewParty(string& name, int pdId, int& partyId) noexcept(false);
		/// <summary>
		///Adding a new party representatives to a party.
		/// </summary>
		/// <param name="representId">the ID of the citizen</param>
		/// <param name="partyId">the ID of the party</param>
		/// <param name="districtId">the district id of the dist the citizen live in</param>
		/// <returns>returns true if party's rep was added, else false</returns>
		void addNewPartyRepresentative(int representId, int partyId, int districtId)noexcept(false);
		bool IsPartyExist(int partyId) const;
		bool isDistcritExist(int id) const;
		/// <summary>
		/// prints all the Districts
		/// </summary>
		void viewAllDistricts() noexcept(false) ;
		/// <summary>
		/// prints all the citizens
		/// </summary>
		void viewAllCitizens() const noexcept(false);
		/// <summary>
		/// prints all the parties
		/// </summary>
		void viewAllParties() const noexcept(false);
		/// <summary>
		/// adding a vote of a person to the party
		/// </summary>
		/// <param name="citizenId">the ID of citizen</param>
		/// <param name="partyId">the ID of the voted party</param>
		/// <returns>returns true if vote was added, else false</returns>
		bool votingAction(int citizenId, int partyId);
		/// <summary>
		/// Calculate the election results.
		/// </summary>
		/// <returns>returns true if can calculate, else false</returns>
		void theResults() throw(const string);
		bool isCitizenExist(int id, int& distIndex) const;
		/// <summary>
		/// Saving election to file
		/// </summary>
		/// <param name="fileName">the name of the file we want to </param>
		virtual void save(ofstream& outFile) const = 0;

		///utils:
		/// <summary>
		/// printing the date of the election
		/// </summary>
		void printElectionDate(ostream& os) const;
	private:

		void setDate();


		bool setWinnerInUnifiedDistrictByDistrictID(int districtID, int repsAmount);
		bool checkElectionsWinner(vector<int>& partiesIndexes);
		bool sortDistrictWinners(int districtID, vector<int>& partiesIndexes);


		void calcReps() noexcept(false);
		void isResultsAllowed() const noexcept(false);
		friend ostream& operator<<(ostream& os, ElectionRound& electionRound);



	};


}
