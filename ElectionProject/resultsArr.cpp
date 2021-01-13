//code verison 3.1
#include "resultsArr.h"
#include "Utils.h"
#include "Party.h"
#include <algorithm>
#include <vector>
#include <utility>
#include "LoadElectionSystem.h"
using namespace std;
namespace elec
{

	resultsArr::resultsArr(LoadElectionSystem& loader)
	{
		int size1;
		ifstream& reader = loader.getReader();
		reader.read(rcastc(&size1), sizeof(int));
		for (int i = 0; i < size1; ++i)
		{
			int size2;
			reader.read(rcastc(&size2), sizeof(int));
			for (int j = 0; j < size2; ++j)
			{
				reader.read(rcastc(&_votesByIDs[i][j]), sizeof(int));
			}
		}
	}

	//void resultsArr::save(ofstream& outFile) const
	//{
	//	//saving _votesByIDs:
	//	int size = _votesByIDs.size();
	//	outFile.write(rcastcc(&size), sizeof(int));
	//	for (int i = 0; i < size; i++)
	//	{
	//		int size2 = _votesByIDs.size();
	//		outFile.write(rcastcc(&size2), sizeof(int));
	//		for (int j = 0; j < size2; j++)
	//		{
	//			outFile.write(rcastcc(&_votesByIDs[i][j]), sizeof(int));
	//		}
	//	}
	//}



	resultsArr::~resultsArr()
	{
		for_each(_votesByIDs.begin(), _votesByIDs.end(), [](vector<int>& votesInVec)
		{
			fill(votesInVec.begin(), votesInVec.end(), 0);
		});
		for_each(_repsPartiesByID.begin(), _repsPartiesByID.end(), [](vector<int>& repsInVec)
		{
			fill(repsInVec.begin(), repsInVec.end(), 0);
		});

	}

	void resultsArr::AddSingleVoteToArr(int party_id, int district_id)
	{

		_votesByIDs[party_id + PARTY_ID_INIT].at(district_id - DISTRICT_ID_INIT)++;


	}





	int resultsArr::getDistrictNumberOfVotesInParty(int partyID, int districtSN)const
	{
		int value = _votesByIDs[partyID][districtSN - DISTRICT_ID_INIT];
		if (value < 0)
		{
			return 0;
		}
		return value;

	}
	int resultsArr::getTotalPartyNumberOfVotes(int partyID) const
	{
		int res = 0;
		for (int i = 0; i < _votesByIDs[partyID - PARTY_ID_INIT].size(); i++)
		{
			res = res + getDistrictNumberOfVotesInParty(partyID, i + DISTRICT_ID_INIT);
		}
		return res;
	}
	int resultsArr::getPMNumberOfRepsInDistrict(int districtId, int partyId) const
	{
		return _repsPartiesByID[partyId][districtId - DISTRICT_ID_INIT];
	}

	vector<int> resultsArr::getPMRepsVecInDistrict(int partyId)
	{
		return _repsPartiesByID[partyId];
	}

	int resultsArr::getPmsRepsTotalByDistrictID(int districtID) const
	{
		int res = 0;
		for (int i = 0; i < _votesByIDs.size(); i++)
		{
			res = res + _repsPartiesByID[i][districtID - DISTRICT_ID_INIT];
		}
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

	void resultsArr::save(ofstream& outFile) const
	{
		//saving _votesByIDs:
		int size = _votesByIDs.size();
		outFile.write(rcastcc(&size), sizeof(int));
		for (int i = 0; i < size; i++)
		{
			int size2 = _votesByIDs.size();
			outFile.write(rcastcc(&size2), sizeof(int));
			for (int j = 0; j < size2; j++)
			{
				outFile.write(rcastcc(&_votesByIDs[i][j]), sizeof(int));
			}
		}
	}

	resultsArr& resultsArr::operator=(const resultsArr& other)
	{
		if (this != &other)
		{
			vector<vector<int>> _votesByIDs;
			for (int i = 0; i < _votesByIDs.size(); i++)
			{
				for (int j = 0; j < _votesByIDs[i].size(); j++)
					_votesByIDs[i][j] = other._votesByIDs[i][j];
			}
			vector<vector<int>> _repsPartiesByID;
			for (int i = 0; i < _repsPartiesByID.size(); i++)
			{
				for (int j = 0; j < _repsPartiesByID[i].size(); j++)
					_repsPartiesByID[i][j] = other._repsPartiesByID[i][j];
			}
			vector<int> _PMsRepsTotalByPartyID;
			for (int k = 0; k < _votesByIDs.size(); k++)
				_PMsRepsTotalByPartyID[k] = other._PMsRepsTotalByPartyID[k];
		}
		return *this;
	}

	bool resultsArr::addParty(int paretiesAmount, int districtsAmount)
	{
		vector<int> districts(districtsAmount);
		_votesByIDs.push_back(districts);

		vector<int> districtsForRepsVec(districtsAmount);
		_repsPartiesByID.push_back(districtsForRepsVec);

		_PMsRepsTotalByPartyID.resize(_PMsRepsTotalByPartyID.size() + 1);

		return true;

	}





	bool resultsArr::addDistrict(int districtsAmount)
	{

		for (int i = 0; i < _votesByIDs.size(); i++)
		{
			_votesByIDs[i].resize(districtsAmount);
		}



		for (int i = 0; i < _votesByIDs.size(); i++)
		{
			_repsPartiesByID[i].resize(districtsAmount);
		}
		return true;

	}

	bool resultsArr::VotesToRepsInDistrictByDistrictID(int districtID, int repsAmount, District* district) noexcept(false) {
		try
		{
			int _partiesLogicSize = _votesByIDs.size();
			vector<pair<double,int >> leftForPartyForElector;
			//pair* leftForPartyForElector = new pair[_partiesLogicSize];
			int allVotesInDis = 0;
			for (int n = 0; n < _partiesLogicSize; n++)
			{
				allVotesInDis = allVotesInDis + getDistrictNumberOfVotesInParty(n + PARTY_ID_INIT, districtID);
			}

			//CALCULATING NUMBER OF REPS FROM EACH PARTY
			double amountOfElectedFromDistrict;

			if (allVotesInDis)
			{
				double minVotesForRep = double(allVotesInDis) / repsAmount;
				for (int i = 0; i < _partiesLogicSize; i++)
				{
					pair<double,int> p;
					if (minVotesForRep)
						amountOfElectedFromDistrict = getDistrictNumberOfVotesInParty(i, districtID) / minVotesForRep;
					else
						amountOfElectedFromDistrict = 0;
					AddToPMRepsCount(districtID, i,static_cast<int>(amountOfElectedFromDistrict));
					if (amountOfElectedFromDistrict == repsAmount)
					{
						p.first = 0;
					}
					else
					{
						p.first = getDistrictNumberOfVotesInParty(i, districtID) -
							double(amountOfElectedFromDistrict * minVotesForRep);
					}
					p.second = i;
					leftForPartyForElector.push_back(p);
				}
				int leftReps = repsAmount;
				for (int k = 0; k < _partiesLogicSize; k++)
				{
					leftReps = leftReps - getPMNumberOfRepsInDistrict(districtID, k);
				}
				sort(leftForPartyForElector.begin(), leftForPartyForElector.end());
				for (int l = 0; l < min(_partiesLogicSize, leftReps); l++)
				{
					AddToPMRepsCount(districtID, leftForPartyForElector.at(l).second, 1);
				}
				// copy all values from _repsPartiesByID[districtID] to parameter "district" reps member
				for (int i = 0; i < _partiesLogicSize; i++)
				{
					district->setRepsArrByPartyID(i, getPMNumberOfRepsInDistrict(districtID, i));
				}
				
			}
			return true;
		}
		catch (bad_alloc& ex)
		{
			throw ex;
		}
	}



	//void resultsArr::swap(pair* xp, pair* yp)
	//{
	//	pair temp = *xp;
	//	*xp = *yp;
	//	*yp = temp;
	//}






	//void resultsArr::bubbleSort(pair arr[], int n)
	//{
	//	int i, j;
	//	for (i = 0; i < n - 1; i++)
	//	{
	//		for (j = 0; j < n - i - 1; j++)
	//		{
	//			if (arr[j] > arr[j + 1])
	//				swap(&arr[j], &arr[j + 1]);
	//		}
	//	}
	//}

}