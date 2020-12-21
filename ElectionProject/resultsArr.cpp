#include "resultsArr.h"
#include "Utils.h"
#include "Party.h"
namespace elec
{
	
	resultsArr::resultsArr(int _partiesAmount, int _districtAmount): _votesByIDs(new int* [_partiesAmount]),
		partiesLogicSize(_partiesAmount) , parPhysSize(MAX_SIZE), districtslogicSize(_districtAmount), disPhysSize(MAX_SIZE),
		_repsPartiesByID(new int* [_partiesAmount]), _PMsRepsTotalByPartyID(new int[_partiesAmount])
	{
		initResults();
	}

	void resultsArr::initResults() {
		for (int i = 0; i < partiesLogicSize; i++) {
			_votesByIDs[i] = new int[districtslogicSize];
			for (int j = 0; j < districtslogicSize; j++)
				_votesByIDs[i][j] = 0;
		}
		for (int i = 0; i < partiesLogicSize; i++) {
			_repsPartiesByID[i] = new int[districtslogicSize];
			for (int j = 0; j < districtslogicSize; j++)
				_repsPartiesByID[i][j] = 0;
		}
		for (int k = 0; k < partiesLogicSize; k++)
			_PMsRepsTotalByPartyID[k] = 0;
	}


	resultsArr::~resultsArr()
	{
		for (int i = 0; i < partiesLogicSize; i++) {
			delete _votesByIDs[i];
		}
		delete[] _votesByIDs;
		for (int j = 0; j < partiesLogicSize; j++) {
			delete _repsPartiesByID[j];
		}
		delete[] _repsPartiesByID;
		delete[] _PMsRepsTotalByPartyID;
	}

	void resultsArr::AddSingleVoteToArr(int party_id, int district_id, int partiesAmount, int districtsAmount)
	{
		if (partiesLogicSize == parPhysSize)
		{
			reallocVotesArr(parPhysSize * 2);

		}

		_votesByIDs[party_id][district_id - DISTRICT_ID_INIT]++;


	}

	void resultsArr::reallocVotesArr(int newSize)
	{
		
		int** newVotesByPartiesIDs = new int* [newSize];
		for (int i = 0; i <min( newSize, parPhysSize); i++) {
			newVotesByPartiesIDs[i] = _votesByIDs[i];

		}

		if (partiesLogicSize >= 1)
		{
			delete[] _votesByIDs;
		}
		parPhysSize = newSize;
		_votesByIDs = newVotesByPartiesIDs;
	}

	void resultsArr::reallocVotesArrDistricts(int newSize)
	{
		int** newVotesByPartiesIDs = new int* [partiesLogicSize];
		for (int i = 0; i < min(newSize, disPhysSize); i++) {
			int* newVotesByDistrictsIDs = new int[newSize];
			for (int j = 0; j < min(newSize, disPhysSize); j++) {
				newVotesByPartiesIDs[i][j] = _votesByIDs[i][j];
			}
			newVotesByPartiesIDs[i][newSize] = 0;
		}

		if (partiesLogicSize >= 1)
		{
			delete[] _votesByIDs;
		}
		parPhysSize = newSize;
		_votesByIDs = newVotesByPartiesIDs;
	}


	void resultsArr::reallocRepsArr(int newSize)
	{

		int** newRepsArr = new int* [newSize];
		for (int i = 0; i < min(newSize, parPhysSize); i++) {
			newRepsArr[i] = _repsPartiesByID[i];

		}

		if (partiesLogicSize >= 1)
		{
			delete[] _repsPartiesByID;
		}
		parPhysSize = newSize;
		_repsPartiesByID = newRepsArr;
	}


	int resultsArr::getpartiesAmount()const
	{
		return partiesLogicSize;
	}
	
	int resultsArr::getdistrictsAmount()const
	{
		return districtslogicSize;

	}

	int resultsArr::getDistrictNumberOfVotesInParty(int partyID, int districtSN )const
	{
		return _votesByIDs[partyID][districtSN-DISTRICT_ID_INIT];
	}
	int resultsArr::getTotalPartyNumberOfVotes(int partyID) const
	{
		int res = 0;
		for (int i = 0; i < partiesLogicSize; i++)
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
		for (int i = 0; i < partiesLogicSize; i++)
			res = res +_repsPartiesByID[i][index - DISTRICT_ID_INIT];
		return res;
	}


	int resultsArr::getPmsRepsTotalByPartyID(int index) const
	{
		return _PMsRepsTotalByPartyID[index];
	}

	bool resultsArr::setPmsRepsTotalByPartyID(int partyID, int reps)
	{
		_PMsRepsTotalByPartyID[partyID] = _PMsRepsTotalByPartyID[partyID] + reps;
		return true;
	}


	bool resultsArr::AddToPMRepsCount(int DistrictID, int RepPartyID, int amountOfReps)
	{
		_repsPartiesByID[RepPartyID-PARTY_ID_INIT][DistrictID - DISTRICT_ID_INIT] = _repsPartiesByID[RepPartyID- PARTY_ID_INIT][DistrictID - DISTRICT_ID_INIT] + amountOfReps;
		return true;
	}
	bool resultsArr::setpartiesAmount()
	{

		partiesLogicSize++;
		return true;
	}

	bool resultsArr::setdistrictsAmount()
	{

		districtslogicSize++;
		return true;

	}
	

	bool resultsArr::addParty()
	{  //check if delete pntrs is needed
		reallocVotesArr(partiesLogicSize + 1);
		partiesLogicSize++;
		int* districts = new int[districtslogicSize];
		for (int i = 0; i < districtslogicSize; i++) {
			districts[i] = 0;
		}
		_votesByIDs[partiesLogicSize-1] = districts;

		
		reallocRepsArr(partiesLogicSize + 1);
		int* party = new int[districtslogicSize];
		_repsPartiesByID[partiesLogicSize - 1] = party;
		for (int j = 0; j < districtslogicSize; j++) {
			_repsPartiesByID[partiesLogicSize - 1][j] = 0;
		}

		int* newPMsRepsTotalByPartyID = new int[partiesLogicSize+1];
		for (int k = 0; k < partiesLogicSize; k++) {
			newPMsRepsTotalByPartyID[k] = _PMsRepsTotalByPartyID[k];
		}
		newPMsRepsTotalByPartyID[partiesLogicSize - 1] = 0;
		_PMsRepsTotalByPartyID = newPMsRepsTotalByPartyID;


		return true;

	}





	bool resultsArr::addDistrict() 
	{ //check if delete pntrs is needed

		for (int i = 0; i < partiesLogicSize; i++) {
			int* districts = new int[districtslogicSize];
			for (int j = 0; j < districtslogicSize - 1; j++)
				districts[j] = _votesByIDs[i][j];
			districts[districtslogicSize - 1] = 0;
			_votesByIDs[i] = districts;
		}
		


		for (int i = 0; i < partiesLogicSize; i++) {
			int* dists = new int[districtslogicSize];
			for (int j = 0; j < districtslogicSize - 1; j++)
				dists[j] = _repsPartiesByID[i][j];
			dists[districtslogicSize - 1] = 0;
			_repsPartiesByID[i] = dists;
		}
		return true;

	}





	bool resultsArr::isResultsAllowed()const
	{
		if ((partiesLogicSize!=0) && (districtslogicSize!=0))
			return true;
		else
			return false;
	}
}