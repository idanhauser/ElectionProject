#pragma once
namespace elec {
	class resultsArr
	{
	private:
		bool firsDistrict = true;
		bool firstParty = true;
		static int _districtsAmount;
		static int _partiesAmount;
		int** _partiesByID; //arr of parties holding in each cell all districts votes
		int** _repsPartiesByID; //arr of reps by order of PartyID holding in each cell all districts given reps
		int* _PMsRepsTotalByPartyID; //KEEPING NUMBER OF REPS A PM GOT AFTER ALL VOTING
	public:
		resultsArr();

		~resultsArr(); //todo

		void AddSingleVoteToArr(int party_id, int district_id);
		int getDistrictNumberOfVotesInParty( int partyID, int districtSN);

		void reallocResultsArr();

		int getdistrictsAmount();
		int getpartiesAmount();
		bool addParty();
		bool addDistrict();

	
		int getPMNumberOfRepsInDistrict(int partyID, int districtSN);
		bool AddToPMRepsCount(int DistrictID, int RepPartyID, int amountOfReps);
	
		
		int getPmsRepsTotalByPartyID(int index);
		bool setPmsRepsTotalByPartyID(int partyID, int reps);

		bool isResultsAllowed();

	};

}