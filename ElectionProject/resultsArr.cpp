//code verison 2.5
#include "resultsArr.h"
#include "Utils.h"
#include "Party.h"
#include <algorithm>
#include "LoadElectionSystem.h"
using namespace std;
namespace elec
{

	resultsArr::resultsArr(int partiesAmount, int districtAmount) : _partiesLogicSize(partiesAmount),
		_parPhysSize(MAX_SIZE), _districtslogicSize(districtAmount), _disPhysSize(MAX_SIZE),
		_votesByIDs(new int*[partiesAmount]), _repsPartiesByID(new int*[partiesAmount]),
		_PMsRepsTotalByPartyID(new int[partiesAmount])
	{
		initResults();
	}

	resultsArr::resultsArr(LoadElectionSystem& loader, int partiesAmount, int districtAmount):
		_partiesLogicSize(partiesAmount), _parPhysSize(MAX_SIZE + partiesAmount), _districtslogicSize(districtAmount),
		_disPhysSize(MAX_SIZE + districtAmount), _votesByIDs(new int*[partiesAmount]),
		_repsPartiesByID(new int*[partiesAmount]), _PMsRepsTotalByPartyID(new int[partiesAmount])
	{
		initResults();
		ifstream& reader = loader.getReader();
		for (int i = 0; i < _partiesLogicSize; ++i)
		{
			for (int j = 0; j < _districtslogicSize; ++j)
			{
				reader.read(rcastc(&_votesByIDs[i][j]), sizeof(int));
			}
		}
	}


	void resultsArr::initResults() {
		for (int i = 0; i < _partiesLogicSize; i++) {
			_votesByIDs[i] = new int[_districtslogicSize];
			for (int j = 0; j < _districtslogicSize; j++)
				_votesByIDs[i][j] = 0;
		}
		for (int i = 0; i < _partiesLogicSize; i++) {
			_repsPartiesByID[i] = new int[_districtslogicSize];
			for (int j = 0; j < _districtslogicSize; j++)
				_repsPartiesByID[i][j] = 0;
		}
		for (int k = 0; k < _partiesLogicSize; k++)
			_PMsRepsTotalByPartyID[k] = 0;
	}


	resultsArr::~resultsArr()
	{
		for (int i = 0; i < _partiesLogicSize; i++) {
			delete _votesByIDs[i];
		}
			delete[] _votesByIDs;
		for (int j = 0; j < _partiesLogicSize; j++) {
			delete _repsPartiesByID[j];
		}
		delete[] _repsPartiesByID;
		delete[] _PMsRepsTotalByPartyID;
	}

	void resultsArr::AddSingleVoteToArr(int party_id, int district_id, int partiesAmount, int districtsAmount)
	{
		if (_partiesLogicSize == _parPhysSize)
		{
			reallocVotesArr(_parPhysSize * 2);

		}

		_votesByIDs[party_id][district_id - DISTRICT_ID_INIT]++;


	}

	void resultsArr::reallocVotesArr(int newSize)
	{

		int** newVotesByPartiesIDs = new int* [newSize];
		for (int i = 0; i < min(newSize, _parPhysSize); i++) {
			newVotesByPartiesIDs[i] = _votesByIDs[i];

		}

		if (_partiesLogicSize >= 1)
		{
			delete[] _votesByIDs;
		}
		_parPhysSize = newSize;
		_votesByIDs = newVotesByPartiesIDs;
	}

	void resultsArr::reallocVotesArrDistricts(int newSize)
	{
		int** newVotesByPartiesIDs = new int* [_partiesLogicSize];
		for (int i = 0; i < min(newSize, _disPhysSize); i++) {
			for (int j = 0; j < min(newSize, _disPhysSize); j++) {
				newVotesByPartiesIDs[i][j] = _votesByIDs[i][j];
			}
			newVotesByPartiesIDs[i][newSize] = 0;
		}

		if (_partiesLogicSize >= 1)
		{
			delete[] _votesByIDs;
		}
		_parPhysSize = newSize;
		_votesByIDs = newVotesByPartiesIDs;
	}


	void resultsArr::reallocRepsArr(int newSize)
	{

		int** newRepsArr = new int* [newSize];
		for (int i = 0; i < min(newSize, _parPhysSize); i++) {
			newRepsArr[i] = _repsPartiesByID[i];

		}

		if (_partiesLogicSize >= 1)
		{
			delete[] _repsPartiesByID;
		}
		_parPhysSize = newSize;
		_repsPartiesByID = newRepsArr;
	}


	int resultsArr::getpartiesAmount()const
	{
		return _partiesLogicSize;
	}

	int resultsArr::getdistrictsAmount()const
	{
		return _districtslogicSize;

	}

	int resultsArr::getDistrictNumberOfVotesInParty(int partyID, int districtSN)const
	{
		return _votesByIDs[partyID][districtSN - DISTRICT_ID_INIT];
	}
	int resultsArr::getTotalPartyNumberOfVotes(int partyID) const
	{
		int res = 0;
		for (int i = 0; i < _partiesLogicSize; i++)
			res = res + getDistrictNumberOfVotesInParty(partyID, i + DISTRICT_ID_INIT);
		return res;
	}
	int resultsArr::getPMNumberOfRepsInDistrict(int districtId, int partyId) const
	{
		return _repsPartiesByID[partyId][districtId - DISTRICT_ID_INIT];
	}
	
	int* resultsArr::getPMNRepsArrInDistrict(int partyId)
	{
		return _repsPartiesByID[partyId];
	}
	int resultsArr::getPmsRepsTotalByDistrictID(int index) const
	{
		int res = 0;
		for (int i = 0; i < _partiesLogicSize; i++)
			res = res + _repsPartiesByID[i][index - DISTRICT_ID_INIT];
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

		_partiesLogicSize++;
		return true;
	}

	bool resultsArr::setdistrictsAmount()
	{

		_districtslogicSize++;
		return true;

	}

	void resultsArr::save(ofstream& outFile) const
	{
		//saving _votesByIDs:
		for (int i = 0; i < _partiesLogicSize; i++) {
			for (int j = 0; j < _districtslogicSize; j++)
				outFile.write(rcastcc(&_votesByIDs[i][j]), sizeof(int));
		}
	}

	resultsArr& resultsArr::operator=(const resultsArr& other)
	{
		if(this != &other)
		{
			_partiesLogicSize = other._partiesLogicSize;
			_parPhysSize = other._parPhysSize;
			_districtslogicSize = other._districtslogicSize;
			_disPhysSize = other._disPhysSize;

			for (int i = 0; i < _partiesLogicSize; i++) {
				_votesByIDs[i] = new int[_districtslogicSize];
				for (int j = 0; j < _districtslogicSize; j++)
					_votesByIDs[i][j] = other._votesByIDs[i][j];
			}
			for (int i = 0; i < _partiesLogicSize; i++) {
				_repsPartiesByID[i] = new int[_districtslogicSize];
				for (int j = 0; j < _districtslogicSize; j++)
					_repsPartiesByID[i][j] = other._repsPartiesByID[i][j];
			}
			for (int k = 0; k < _partiesLogicSize; k++)
				_PMsRepsTotalByPartyID[k] = other._PMsRepsTotalByPartyID[k];
		}
		return *this;
	}


	bool resultsArr::addParty()
	{  //check if delete pntrs is needed
		reallocVotesArr(_partiesLogicSize + 1);
		_partiesLogicSize++;
		int* districts = new int[_districtslogicSize];
		for (int i = 0; i < _districtslogicSize; i++) {
			districts[i] = 0;
		}
		_votesByIDs[_partiesLogicSize - 1] = districts;


		reallocRepsArr(_partiesLogicSize + 1);
		int* party = new int[_districtslogicSize];
		_repsPartiesByID[_partiesLogicSize - 1] = party;
		for (int j = 0; j < _districtslogicSize; j++) {
			_repsPartiesByID[_partiesLogicSize - 1][j] = 0;
		}

		int* newPMsRepsTotalByPartyID = new int[_partiesLogicSize + 1];
		for (int k = 0; k < _partiesLogicSize; k++) {
			newPMsRepsTotalByPartyID[k] = _PMsRepsTotalByPartyID[k];
		}
		newPMsRepsTotalByPartyID[_partiesLogicSize - 1] = 0;
		_PMsRepsTotalByPartyID = newPMsRepsTotalByPartyID;


		return true;

	}





	bool resultsArr::addDistrict()
	{

		for (int i = 0; i < _partiesLogicSize; i++) {
			int* districts = new int[_districtslogicSize];
			for (int j = 0; j < _districtslogicSize - 1; j++)
				districts[j] = _votesByIDs[i][j];
			districts[_districtslogicSize - 1] = 0;
			_votesByIDs[i] = districts;
		}



		for (int i = 0; i < _partiesLogicSize; i++) {
			int* dists = new int[_districtslogicSize];
			for (int j = 0; j < _districtslogicSize - 1; j++)
				dists[j] = _repsPartiesByID[i][j];
			dists[_districtslogicSize - 1] = 0;
			_repsPartiesByID[i] = dists;
		}
		return true;

	}


	bool resultsArr::VotesToRepsInDistrictByDistrictID(int districtID, int repsAmount, District* district) {
		int leftReps;
		double amountOfElectedFromDistrict;
		pair* leftForPartyForElector = new pair[_partiesLogicSize];
		int allVotesInDis = 0;
		for (int n = 0; n < _partiesLogicSize; n++)
		{
			allVotesInDis = allVotesInDis + getDistrictNumberOfVotesInParty(n + PARTY_ID_INIT, districtID);
		}

		//CALCULATING NUMBER OF REPS FROM EACH PARTY
		if (allVotesInDis)
		{
			double minVotesForRep = double(allVotesInDis) / repsAmount;
			for (int i = 0; i < _partiesLogicSize; i++)
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
			for (int k = 0; k < _partiesLogicSize; k++)
			{
				leftReps = leftReps - getPMNumberOfRepsInDistrict(districtID, k);
			}
			bubbleSort(leftForPartyForElector, _partiesLogicSize);
			for (int l = 0; l < min(_partiesLogicSize, leftReps); l++)
			{
				AddToPMRepsCount(districtID, leftForPartyForElector[l].index, 1);
			}
			// copy all values from _repsPartiesByID[districtID] to parameter "district" reps member
			for (int i = 0; i < _partiesLogicSize; i++)
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
	//	//todo:roee update for unified district the leader
	//	district->setLeader(_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader());
	//	for (int i = 0; i < partiesLogicSize; i++)
	//	{
	//		district->setRepsArrByPartyID(i, 0);
	//	}
	//	district->setRepsArrByPartyID(leaderWithMostRepsPartyID, district->getNumOfReps());
	//	addToPmsRepsTotalByPartyID(leaderWithMostRepsPartyID, repsAmount);

	//	//todo:roee remove next comment after district leader is set in UnifiedDistrict.h
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

	//todo:roee fix
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