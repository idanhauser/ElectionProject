#pragma once
namespace elec {
	class resultsArr
	{
	private:
		static int _districtsAmount;
		static int _partiesAmount;
		int** _partiesByID; //arr of parties holding in each cell all districts votes
		int** _repsPartiesByID; //arr of reps by order of PartyID holding in each cell all districts given reps
		int* _PMsRepsByPartyID; //KEEPING NUMBER OF REPS A PM GOT AFTER ALL VOTING
		int* TotalPMsReps=0;
	//	int* AmountOfVotesForParty;
	public:
		resultsArr();

		~resultsArr(); //todo

		int* findPartysDistrictsPntrByPartyID(int partyID);
		void AddSingleVoteToArr(int party_id, int district_id);

		void reallocResultsArr();

		int getdistrictsAmount();
		int getpartiesAmount();
		int* getTotalPMsRepsArr() {
			return TotalPMsReps;
		}
		int getRepsForPMinArrByInxdex(int index) {
			return TotalPMsReps[index];
		}
		int getDistrictNumberOfVotesInParty(int districtSN, int partyID);
		int getPMNumberOfRepsInDistrict(int partyID, int districtSN);
		int setPmsRepsByPartyID(int index) {
			return _PMsRepsByPartyID[index];
		}
		int getPmsRepsByPartyID(int index) {
			return _PMsRepsByPartyID[index];
		}
		bool setPMsArrByIndex(int partyId, int votes);
		bool addToTotalPMsReps(int PartyPmID, int reps);
		bool AddToPMRepsCount(int DistrictID, int RepPartyID , int amountOfReps) {
			_repsPartiesByID[RepPartyID][DistrictID-100] = _repsPartiesByID[RepPartyID][DistrictID-100] + amountOfReps;
			return true;
		}
		bool addParty() {
			_partiesAmount++;
			return true;
		}
		bool addDistrict() {
			_districtsAmount++;
			return true;
		}
	//	bool addToAmountOfVotesForParty(int PartyPmID, int reps); //maybe delete
	};

}