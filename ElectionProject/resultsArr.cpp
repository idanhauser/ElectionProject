#include "resultsArr.h"
namespace elec
{
	resultsArr::resultsArr():
		_partiesByID(new int* [_partiesAmount]), _repsPartiesByID(new int* [_partiesAmount]), _PMsRepsByPartyID(new int[_partiesAmount]), TotalPMsReps(new int [_partiesAmount])
	{
		for (int i = 0; i < _partiesAmount; i++) {
			_partiesByID[i] = new int[_districtsAmount];
			for (int j = 0; j < _districtsAmount; j++)
				_partiesByID[i][j] = 0;
		}
		for (int i = 0; i < _partiesAmount; i++) {
			_repsPartiesByID[i] = new int[_partiesAmount];
			for (int j = 0; j < _partiesAmount; j++)
				_partiesByID[i][j] = 0;
		}
	}


	resultsArr::~resultsArr() {
		for (int i = 0; i < _partiesAmount; i++) {
			delete[] _partiesByID[i];
		}
		delete _partiesByID;
		for (int i = 0; i < _partiesAmount; i++) {
			delete[] _repsPartiesByID[i];
		}
		delete _repsPartiesByID;
	}


	int* resultsArr::findPartysDistrictsPntrByPartyID(int partyID) {
		return _partiesByID[partyID - 100];
	}

	void resultsArr::AddSingleVoteToArr(int party_id, int district_id) {
		reallocResultsArr(); //roee:realloc every vote cause u i dont know if districts/parties amount was change since last time. should I keep it in static variable maybe?
		_partiesByID[party_id][district_id - 100]++;
	}

	void resultsArr::reallocResultsArr()
	{
		int** newPartiesByID = new int* [_partiesAmount];

		for (int i = 0; i < _partiesAmount; i++)
		{
			newPartiesByID[i] = _partiesByID[i];
		}
		if (_partiesAmount >= 1) //roee: not sure if correct
		{
			delete[] _partiesByID;
		}

		_partiesByID = newPartiesByID;
	}


	int resultsArr::getpartiesAmount() {
		return _partiesAmount;
	}

	int resultsArr::getdistrictsAmount() {
		return _districtsAmount;
	}

	int resultsArr::getDistrictNumberOfVotesInParty(int partyID, int districtSN ) {
		return _partiesByID[partyID][districtSN-100];
	}
	int resultsArr::getPMNumberOfRepsInDistrict(int districtID, int partyID) {
		return _repsPartiesByID[partyID][districtID - 100];
	}

	bool resultsArr::setPMsArrByIndex(int partyId, int votes) {
		_PMsRepsByPartyID[partyId] = votes;
		return true;
	}

	bool resultsArr::addToTotalPMsReps(int PartyPmID, int reps) {
		TotalPMsReps[PartyPmID] = TotalPMsReps[PartyPmID] + reps;
		return true;
	}

	/*bool resultsArr::addToAmountOfVotesForParty(int PartyPmID, int votes) {
		AmountOfVotesForParty[PartyPmID] = AmountOfVotesForParty[PartyPmID] + votes;
		return true;
	}*/
}