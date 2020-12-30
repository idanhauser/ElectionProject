//code verison 2.0
#include "resultsArr.h"
#include "Utils.h"
#include "Party.h"
#include <algorithm>

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
	int resultsArr::getPMNumberOfRepsInDistrict(int districtID, int partyID) const
	{
		return _repsPartiesByID[partyID][districtID - DISTRICT_ID_INIT];
	}
	
	int* resultsArr::getPMNRepsArrInDistrict(int partyID)
	{
		return _repsPartiesByID[partyID];
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


	bool resultsArr::addToPmsRepsTotalByPartyID(int partyID, int reps)
	{
		_PMsRepsTotalByPartyID[partyID] = _PMsRepsTotalByPartyID[partyID] + reps;
		return true;
	}


	bool resultsArr::AddToPMRepsCount(int DistrictID, int RepPartyID, int amountOfReps)
	{
		_repsPartiesByID[RepPartyID][DistrictID - DISTRICT_ID_INIT] = _repsPartiesByID[RepPartyID][DistrictID - DISTRICT_ID_INIT] + amountOfReps;
		return true;
	}
	bool resultsArr::setNewNumForPMRepsCount(int DistrictID, int RepPartyID, int amountOfReps)
	{
		_repsPartiesByID[RepPartyID][DistrictID - DISTRICT_ID_INIT] = amountOfReps;
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
	{  //todo: check if delete pntrs is needed
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
	{ 

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


	bool resultsArr::VotesToRepsInDistrictByDistrictID(int districtID, int repsAmount, District* district) {
		int leftReps;
		double amountOfElectedFromDistrict;
		pair* leftForPartyForElector = new pair[partiesLogicSize];
		int allVotesInDis = 0;
		for (int n = 0; n < partiesLogicSize; n++)
		{
			allVotesInDis = allVotesInDis + getDistrictNumberOfVotesInParty(n + PARTY_ID_INIT, districtID);
		}

		//CALCULATING NUMBER OF REPS FROM EACH PARTY
		if (allVotesInDis)
		{
			double minVotesForRep = double(allVotesInDis) / repsAmount;
			for (int i = 0; i < partiesLogicSize; i++)
			{
				if (minVotesForRep)
					amountOfElectedFromDistrict = getDistrictNumberOfVotesInParty(i, districtID) / minVotesForRep;
				else
					amountOfElectedFromDistrict = 0;
				AddToPMRepsCount(districtID, i, amountOfElectedFromDistrict);
				if (amountOfElectedFromDistrict == repsAmount)
					leftForPartyForElector[i].repsAmount = 0;
				else
					leftForPartyForElector[i].repsAmount = getDistrictNumberOfVotesInParty(i, districtID) -
					double(amountOfElectedFromDistrict * minVotesForRep);
				leftForPartyForElector[i].index = i;
			}
			leftReps = repsAmount;
			for (int k = 0; k < partiesLogicSize; k++)
			{
				leftReps = leftReps - getPMNumberOfRepsInDistrict(districtID, k);
			}
			bubbleSort(leftForPartyForElector, partiesLogicSize);
			for (int l = 0; l < min(partiesLogicSize, leftReps); l++)
			{
				AddToPMRepsCount(districtID, leftForPartyForElector[l].index, 1);
			}
			// copy all values from _repsPartiesByID[districtID] to parameter "district" reps member
			for (int i = 0; i < partiesLogicSize; i++)
			{
				district->setRepsArrByPartyID(i, getPMNumberOfRepsInDistrict(districtID, i));
			}
			delete[] leftForPartyForElector;
		}
		return true;
	}

	//bool resultsArr::setWinnerInUnifiedDistrictByDistrictID(int districtID, int repsAmount, District* district) {
	//	int max = 0;
	//	int leaderWithMostRepsPartyID = 0;
	//	for (int p = 0; p < partiesLogicSize; p++)
	//	{
	//		int curRepsAmount = getPMNumberOfRepsInDistrict(districtID, p + PARTY_ID_INIT);
	//		if (max < curRepsAmount)
	//		{
	//			max = curRepsAmount;
	//			leaderWithMostRepsPartyID = p + PARTY_ID_INIT;

	//		}
	//	}
	//	//todo: update for unified district the leader
	//	district->setLeader(_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader());
	//	for (int i = 0; i < partiesLogicSize; i++)
	//	{
	//		district->setRepsArrByPartyID(i, 0);
	//	}
	//	district->setRepsArrByPartyID(leaderWithMostRepsPartyID, district->getNumOfReps());
	//	addToPmsRepsTotalByPartyID(leaderWithMostRepsPartyID, repsAmount);

	//	//todo: remove next comment after district leader is set in UnifiedDistrict.h
	//	//cout << "The district belongs to: " <<
	//	//	_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader().getCitizenName() << endl;

	//	return true;
	//}
	
	void resultsArr::swap(pair* xp, pair* yp)
	{
		pair temp = *xp;
		*xp = *yp;
		*yp = temp;
	}

	void resultsArr::bubbleSort(pair arr[], int n)
	{
		int i, j;
		for (i = 0; i < n - 1; i++)
		{
			for (j = 0; j < n - i - 1; j++)
			{
				if (arr[j].repsAmount > arr[j + 1].repsAmount)
					swap(&arr[j], &arr[j + 1]);
			}
		}
	}

	//todo: fix
	/*ostream& operator<<(ostream& os, const resultsArr& resultsArr) {
		for (int i = 0; i < resultsArr.getdistrictsAmount(); i++)
		{
			os << "The District with ID: " << i + DISTRICT_ID_INIT << " got " << endl;
			for (int j = 0; j < resultsArr.getpartiesAmount(); j++)
			{
				os << "from Party with ID: " << j + PARTY_ID_INIT << " - " <<
				resultsArr.getDistrictNumberOfVotesInParty(i + PARTY_ID_INIT, j + DISTRICT_ID_INIT)<< " votes" << endl;

			}
		}

		return os;

	}*/
}