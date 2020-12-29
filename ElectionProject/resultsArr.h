//code verison 2.0
#pragma once
#include <fstream>
using namespace std;
namespace elec {
	class LoadElectionSystem;

	class resultsArr
	{
	private:
		int _partiesLogicSize;
		int _parPhysSize;
		int _districtslogicSize;
		int _disPhysSize;

		int**  _votesByIDs; //arr of parties holding in each cell all districts votes
		int** _repsPartiesByID; //arr of reps by order of PartyID holding in each cell all districts given reps
		int* _PMsRepsTotalByPartyID; //KEEPING NUMBER OF REPS A PM GOT AFTER ALL VOTING
	public:
		resultsArr(int partiesAmount, int districtAmount);
		//idan added:
	//	resultsArr(LoadElectionSystem& loader, int partiesAmount, int districtAmount);
	//	resultsArr();
		~resultsArr(); 

	//	friend ostream& operator<<(ostream& os, const resultsArr& results);


		void AddSingleVoteToArr(int party_id, int district_id, int partiesAmount, int districtsAmount);
		int getDistrictNumberOfVotesInParty( int partyID, int districtSN)const;

		void reallocVotesArr(int newSize);
		void reallocVotesArrDistricts(int newSize);
		void reallocRepsArr(int newSize);
		
		void initResults();

		int getpartiesAmount()const;
		int getdistrictsAmount() const;
		bool addParty();
		bool addDistrict();

		int getPmsRepsTotalByDistrictID(int index) const;
		int getTotalPartyNumberOfVotes(int partyID) const;
		int getPMNumberOfRepsInDistrict(int districtSN, int partyID);
		bool AddToPMRepsCount(int DistrictID, int RepPartyID, int amountOfReps);
	
		
		int getPmsRepsTotalByPartyID(int index) const;
		bool setPmsRepsTotalByPartyID(int partyID, int reps);

		bool setpartiesAmount();
		bool setdistrictsAmount();


		bool isResultsAllowed()const;
		//idan added//void save(ofstream& outFile) const;
	};

}
