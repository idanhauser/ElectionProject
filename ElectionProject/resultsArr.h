//code verison 3.0
#pragma once
#include <fstream>
using namespace std;
#include "District.h"
namespace elec {
	class LoadElectionSystem;

	class resultsArr
	{
	private:
		int _partiesLogicSize;
		int _parPhysSize;
		int _districtsLogicSize;
		int _disPhysSize;

		int** _votesByIDs; //arr of parties holding in each cell all districts votes
		int** _repsPartiesByID; //arr of reps by order of PartyID holding in each cell all districts given reps
		int* _PMsRepsTotalByPartyID; //KEEPING NUMBER OF REPS A PM GOT AFTER ALL VOTING
	public:
		struct pair {
			int index;
			double repsAmount;
		};
		resultsArr(int partiesAmount, int districtAmount);
		resultsArr(LoadElectionSystem& loader, int partiesAmount, int districtAmount);
		resultsArr() = delete;
		~resultsArr();


		/// <summary>
		/// adding a vote an array to counts all the votes
		/// </summary>
		/// <param name="party_id">the party id the citizen voted to.</param>
		/// <param name="district_id">the distcrit id of the cizitizen </param>
		void AddSingleVoteToArr(int party_id, int district_id);
		/// <summary>
		///the function retuns how many vote the party got in a specific distcrit
		/// </summary>
		/// <param name="partyID">the party id</param>
		/// <param name="districtSN">the dist id</param>
		/// <returns></returns>
		int getDistrictNumberOfVotesInParty(int partyID, int districtSN)const;
		/// <summary>
		/// util function to manage the arr. this function dose realloc (like in c) to the array.
		/// </summary>
		/// <param name="newSize">the new size of the arr.</param>
		void reallocVotesArr(int newSize);
		/// <summary>
		/// util function to manage the arr. this function dose realloc (like in c) to the array.
		/// </summary>
		/// <param name="newSize">the new size of the arr.</param>
		void reallocVotesArrDistricts(int newSize);
		/// <summary>
		/// util function to manage the arr. this function dose realloc (like in c) to the array.
		/// </summary>
		/// <param name="newSize">the new size of the arr.</param>
		void reallocRepsArr(int newSize);
		/// <summary>
		///this function initialize all the arrays.
		/// </summary>
		void initResults();
		int getpartiesAmount()const;
		int getdistrictsAmount() const;
		bool addParty();
		bool addDistrict();

		/// <summary>
		///returns how many reps party leader got in a party.
		/// </summary>
		/// <param name="index">the id of dist.</param>
		/// <returns>the amount of reps</returns>
		int getPmsRepsTotalByDistrictID(int index) const;
		/// <summary>
		/// returns how many citizens vote to a specific party.
		/// </summary>
		/// <param name="partyID">the party id.</param>
		/// <returns>the amounts of vote to the party/</returns>
		int getTotalPartyNumberOfVotes(int partyID) const;
		/// <summary>
		/// returns an arr with the amount of reps by dist.
		/// </summary>
		/// <param name="partyID">the id of the party</param>
		/// <returns>amount of reps each dist gave to the party</returns>
		int* getPMNRepsArrInDistrict(int partyID);
		/// <summary>
		/// returns an arr with the amount of reps by a specific dist.
		/// </summary>
		///<param name="districtSN">the id of the dist</param>
		/// <param name="partyID">the id of the party</param>
		/// <returns>amount of reps each dist gave to the party</returns>
		int getPMNumberOfRepsInDistrict(int districtSN, int partyID) const;
		/// <summary>
		/// adding to the counter of the reps more reps.
		/// </summary>
		/// <param name="DistrictID">dist id</param>
		/// <param name="RepPartyID">the party id.</param>
		/// <param name="amountOfReps">how many reps he got.</param>
		/// <returns>retuns true if everything is good else false.</returns>
		bool AddToPMRepsCount(int DistrictID, int RepPartyID, int amountOfReps);

		/// <summary>
		/// get the amount of all the reps party leader got
		/// </summary>
		/// <param name="index">the id of the party</param>
		/// <returns></returns>
		int getPmsRepsTotalByPartyID(int index) const;
		bool setPmsRepsTotalByPartyID(int partyID, int reps);
		bool addToPmsRepsTotalByPartyID(int partyID, int reps);
		bool setNewNumForPMRepsCount(int DistrictID, int RepPartyID, int amountOfReps);
	
		bool setPartiesAmount();
		bool setDistrictsAmount();
		/// <summary>
		/// saving this class to an array
		/// </summary>
		/// <param name="outFile">the writer</param>
		void save(ofstream& outFile) const;

		resultsArr& operator=(const resultsArr& other);

		/// <summary>
		/// CALCULATING all the votes any party got from all the dists.
		/// </summary>
		/// <param name="districtID">the dist id</param>
		/// <param name="repsAmount">the amount of reps from a dist</param>
		/// <param name="district">pointer to the dist so we can setRepsArrByPartyID.</param>
		/// <returns>return true if evryhirng is good</returns>
		bool VotesToRepsInDistrictByDistrictID(int districtID, int repsAmount, District* district);




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


		bool isResultsAllowed()const;
	};

}
