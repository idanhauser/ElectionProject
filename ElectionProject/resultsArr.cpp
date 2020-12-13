#include "resultsArr.h"
#include "Utils.h"

namespace elec
{
	
	int resultsArr::_partiesAmount = 1;
	int resultsArr::_districtsAmount = 1;
	
	resultsArr::resultsArr(): 
		_partiesByID(new int* [_partiesAmount]), _repsPartiesByID(new int* [_partiesAmount]), _PMsRepsTotalByPartyID(new int[_partiesAmount])
	{
		for (int i = 0; i < _partiesAmount; i++) {
			_partiesByID[i] = new int[_districtsAmount];
			for (int j = 0; j < _districtsAmount; j++)
				_partiesByID[i][j] = 0;
		}
		for (int i = 0; i < _partiesAmount; i++) {
			_repsPartiesByID[i] = new int[_districtsAmount];
			for (int j = 0; j < _districtsAmount; j++)
				_repsPartiesByID[i][j] = 0;
		}
		for (int k = 0; k < _partiesAmount; k++)
			_PMsRepsTotalByPartyID[k] = 0;
	}


	resultsArr::~resultsArr()
	{
		for (int i = 0; i < _partiesAmount; i++) {
			delete[] _partiesByID[i];
		}
		delete _partiesByID;
		for (int i = 0; i < _partiesAmount; i++) {
			delete[] _repsPartiesByID[i];
		}
		delete _repsPartiesByID;
		delete[] _PMsRepsTotalByPartyID;
	}

	void resultsArr::AddSingleVoteToArr(int party_id, int district_id)
	{
		reallocResultsArr(); //roee:realloc every vote cause u i dont know if districts/parties amount was change since last time.
		_partiesByID[party_id][district_id - 100]++;
	}

	void resultsArr::reallocResultsArr()
	{
		int** newPartiesByID = new int* [_partiesAmount];
		int** newRepsArr = new int* [_partiesAmount];
		for (int i = 0; i < _partiesAmount; i++){
			newPartiesByID[i] = _partiesByID[i];
			for (int j = 0; j < _districtsAmount; j++)
				newPartiesByID[i][j] = _partiesByID[i][j];
		}

		if (_partiesAmount >= 1) 
		{
			delete[] _partiesByID;
		}

		_partiesByID = newPartiesByID;
	}


	int resultsArr::getpartiesAmount()const
	{
		return _partiesAmount;
	}

	int resultsArr::getdistrictsAmount()const
	{
		return _districtsAmount;
	}

	int resultsArr::getDistrictNumberOfVotesInParty(int partyID, int districtSN )const
	{
		return _partiesByID[partyID][districtSN-DISTRICT_ID_INIT];
	}
	int resultsArr::getTotalPartyNumberOfVotes(int partyID) const
	{
		int res = 0;
		for (int i = 0; i < getpartiesAmount(); i++)
			res = res+ getDistrictNumberOfVotesInParty(partyID, i+DISTRICT_ID_INIT);
		return res;
	}
	int resultsArr::getPMNumberOfRepsInDistrict(int districtID, int partyID) 
	{
		return _repsPartiesByID[partyID][districtID - DISTRICT_ID_INIT];
	}
	
	int resultsArr::getPmsRepsTotalByDistrictID(int index) const
	{
		int res = 0;
		for (int i = 0; i < _partiesAmount; i++)
			res = res +_repsPartiesByID[i][index - DISTRICT_ID_INIT];
		return res;
	}


	int resultsArr::getPmsRepsTotalByPartyID(int index) const
	{
		return _PMsRepsTotalByPartyID[index];
	}

	bool resultsArr::setPmsRepsTotalByPartyID(int partyID, int reps)
	{
		_PMsRepsTotalByPartyID[partyID] = reps;
		return true;
	}


	bool resultsArr::AddToPMRepsCount(int DistrictID, int RepPartyID, int amountOfReps)
	{
		_repsPartiesByID[RepPartyID-PARTY_ID_INIT][DistrictID - DISTRICT_ID_INIT] = _repsPartiesByID[RepPartyID- PARTY_ID_INIT][DistrictID - DISTRICT_ID_INIT] + amountOfReps;
		return true;
	}
	
	bool resultsArr::addParty()
	{  //check if delete pntrs is needed
	
		if (firstParty) {
			firstParty = false;
		}
		else
			_partiesAmount++;
		int** newPartiesByID = new int* [_partiesAmount];
		for (int i = 0; i < _partiesAmount - 1; i++) {
			newPartiesByID[i] = _partiesByID[i];
		}
		int* districts = new int[_districtsAmount];
		newPartiesByID[_partiesAmount - 1] = districts;
		for (int j = 0; j < _districtsAmount; j++) {
			newPartiesByID[_partiesAmount - 1][j] = 0;
		}
		this->_partiesByID = newPartiesByID;
		


		int** newRepsPartiesByID = new int*[_partiesAmount];
		for (int i = 0; i < _partiesAmount - 1; i++) {
			newRepsPartiesByID[i] = _repsPartiesByID[i];
		}
		int* party = new int[_districtsAmount];
		newRepsPartiesByID[_partiesAmount - 1] = party;

		for (int j = 0; j < _districtsAmount; j++) {
			newRepsPartiesByID[_partiesAmount - 1][j] = 0;
		}
		this->_repsPartiesByID = newRepsPartiesByID;
		
		return true;

	}
	
	bool resultsArr::addDistrict() 
	{ //check if delete pntrs is needed
		if (firsDistrict) {
			firsDistrict = false;
		}
		else
			_districtsAmount++;
		for (int i = 0; i < _partiesAmount; i++) {
			int* districts = new int[_districtsAmount];
			for (int j = 0; j < _districtsAmount - 1; j++)
				districts[j] = _partiesByID[i][j];
			districts[_districtsAmount - 1] = 0;
			_partiesByID[i] = districts;
		}
		


		for (int i = 0; i < _partiesAmount; i++) {
			int* dists = new int[_districtsAmount];
			for (int j = 0; j < _districtsAmount - 1; j++)
				dists[j] = _repsPartiesByID[i][j];
			dists[_districtsAmount - 1] = 0;
			_repsPartiesByID[i] = dists;
		}
		return true;

	}
	
	bool resultsArr::isResultsAllowed()const
	{
		if (!firsDistrict && !firstParty)
			return true;
		else
			return false;
	}
}