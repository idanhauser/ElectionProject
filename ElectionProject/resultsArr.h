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
		int* TotalPMsReps=nullptr;
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
		bool addParty() {  //check if delete pntrs is needed
			static bool firstParty=true;
			if (firstParty) {
				firstParty = false;
			}
			else
				_partiesAmount++;
			int** newPartiesByID = new int* [_partiesAmount];
			for (int i = 0; i < _partiesAmount-1; i++) {
				newPartiesByID[i] = _partiesByID[i];
			}
			int* districts = new int[_districtsAmount];
			newPartiesByID[_partiesAmount-1] = districts;
			for (int j = 0; j < _districtsAmount; j++) {
				newPartiesByID[_partiesAmount-1][j] = 0;
			}
			this->_partiesByID = newPartiesByID;
			return true;
		}
		bool addDistrict() { //check if delete pntrs is needed
			static bool firsDistrict = true;
			if (firsDistrict) {
				firsDistrict = false;
			}
			else
				_districtsAmount++;
			for (int i = 0; i < _partiesAmount; i++) {
				int* districts = new int [_districtsAmount];
				for (int j = 0; j < _districtsAmount-1; j++)
					districts[j] = _partiesByID[i][j];
				districts[_districtsAmount-1] = 0;
				_partiesByID[i] = districts;
			}
			return true;
		}
	//	bool addToAmountOfVotesForParty(int PartyPmID, int reps); //maybe delete
	};

}