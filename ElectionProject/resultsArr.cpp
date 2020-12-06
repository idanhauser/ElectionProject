#include "resultsArr.h"
namespace elec
{
	resultsArr::resultsArr():
		_PMsRepsByPartyID(new int[_partiesAmount]), _districtsByID( new int* [_districtsAmount]), TotalPMsReps(new int [_partiesAmount])
	{
		for (int i = 0; i < _districtsAmount; i++) {
			_districtsByID[i] = new int[_partiesAmount];
			for (int j = 0; j < _partiesAmount; j++)
				_districtsByID[i][j] = 0;
		}
	}


	int* resultsArr::findDistrictPartiesPntrByID(int districtID) {
		return _districtsByID[districtID - 100];
	}

	void resultsArr::AddVoteToResultsArr(int party_id, int district_id) {
		reallocResultsArr();
		_districtsByID[party_id][district_id - 100]++;
	}

	void resultsArr::reallocResultsArr()
	{
		int** newDistrictsByID = new int* [_districtsAmount];

		for (int i = 0; i < _districtsAmount; i++)
		{
			newDistrictsByID[i] = _districtsByID[i];
		}
		if (_districtsAmount >= 1) //roee: not sure if correct
		{
			delete[] _districtsByID;
		}

		_districtsByID = newDistrictsByID;
	}


	int resultsArr::getpartiesAmount() {
		return _partiesAmount;
	}

	int resultsArr::getdistrictsAmount() {
		return _districtsAmount;
	}

	int resultsArr::getPartyNumberOfVotesFromDistrict(int districtSN, int partyID) {
		return _districtsByID[districtSN][partyID];
	}


	bool resultsArr::setPMsArrByIndex(int partyId, int votes) {
		_PMsRepsByPartyID[partyId] = votes;
		return true;
	}

	bool resultsArr::addToTotalPMsReps(int PartyPmID, int reps) {
		TotalPMsReps[PartyPmID] = TotalPMsReps[PartyPmID] + reps;
		return true;
	}
}