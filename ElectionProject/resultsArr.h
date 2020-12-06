#pragma once
namespace elec {
	class resultsArr
	{
	private:
		int** _districtsByID; //
		const static int _districtsAmount = 1, _partiesAmount = 1;
		int* _PMsRepsByPartyID; //KEEPING NUMBER OF REPS A PM GOT AFTER ALL VOTING
		int* TotalPMsReps=0;
	public:
		resultsArr();

		~resultsArr(); //todo

		int* findDistrictPartiesPntrByID(int districtID);
		void AddVoteToResultsArr(int party_id, int district_id);

		void reallocResultsArr();

		int getdistrictsAmount();
		int getpartiesAmount();
		int* getTotalPMsRepsArr() {
			return TotalPMsReps;
		}
		int getRepsForPMinArrByInxdex(int index) {
			return TotalPMsReps[index];
		}
		int getPartyNumberOfVotesFromDistrict(int districtSN, int partyID);
		int getPmsVotesByPartyID(int index) {
			return _PMsRepsByPartyID[index];
		}
		bool setPMsArrByIndex(int partyId, int votes);
		bool addToTotalPMsReps(int PartyPmID, int reps);
	};

}