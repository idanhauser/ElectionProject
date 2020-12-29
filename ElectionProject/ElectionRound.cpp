//code verison 2.0
#include "ElectionRound.h"
#include <iostream>
#include <algorithm>
#include <fstream>

#include "Party.h"

#include "DistrictList.h"
#include "CitizenList.h"
#include "LoadElectionSystem.h"
#include "PartyList.h"
using namespace std;

namespace elec {
	ElectionRound::ElectionRound(int date[DATE_SIZE]) :_districts(), _parties(),
		_results(resultsArr(_parties.getLogicSize(), _districts.getLogicSize()))
	{
		

		for (int i = 0; i < DATE_SIZE; ++i)
		{
			this->_date[i] = date[i];
		}
	}

	ElectionRound::ElectionRound(LoadElectionSystem& loader): _districts(), _parties(), _results(0,0)
	{
		bool represntAdded;
		int numberOfparties;
		int numberOfdist;
		ifstream& reader = loader.getReader();
		//Reading Date:
		reader.read(rcastc(_date), sizeof(int) * DATE_SIZE);
		//Read Dists:
			//reading number of dists:
		reader.read(rcastc(&numberOfdist), sizeof(int));

		for (int i = 0; i < numberOfdist; ++i)
		{
			District* dist = new District(loader);
			_districts.addToList(*dist);

		}

		cout << "read dists" << endl;
		//Reading parties:
		//Read Dists:
			//reading number of parties:
		reader.read(rcastc(&numberOfparties), sizeof(int));
		for (int i = 0; i < numberOfparties; ++i)
		{
			int indexOfDist;
			int partyLeaderId;
			//reading partyLeaderId:
			reader.read(rcastc(&partyLeaderId), sizeof(int));
			if (_districts.isCitizenExist(partyLeaderId, indexOfDist)) {
				Party* party = new Party(loader, _districts.getDistcritByIndex(indexOfDist).getCitizenById(partyLeaderId),numberOfdist);
				_parties.addToList(*party);
				//cout << "read " <<party->getPartyID() <<" party" << endl;
			}
		}
		cout << "read parties" << endl;

		//Reading _votesByIDs:
		//_results= resultsArr(loader, numberOfparties, numberOfdist);

		
		//-------------------------------------------------------------------------
		// match between represent to a party. and party to a dist and citizen:
		//i - dist index; j - party index; t - citizen index.
		for (int i = 0; i < numberOfdist; ++i)
		{
			District& distTemp = _districts.getDistcritByIndex(i);
			//for (int j = 0; j < numberOfparties; ++j)
			//{
			//	_parties.getPartyByIndex(i).updateParties();
			//}
			int numOfCitizens = distTemp.getNumberOfCitizens();
			for (int t = 0; t < numOfCitizens; ++t)
			{
				Citizen& citizTemp = distTemp.getCitizenByIndex(t);
				if (citizTemp.GetPartyId() != -1)
				{
					Party& currParty = _parties.getPartyByIndex(citizTemp.GetPartyId()-PARTY_ID_INIT);
					represntAdded= currParty.addPartyMember(citizTemp, i);
					citizTemp.setParty(&currParty);
					if(!represntAdded)
					{//todo:to fix that if.(to delete maybe)
						cout << "Error:Couldn't finish the loading." << endl;
						return;
					}
				}
			}
		}
	}




	void ElectionRound::printElectionDate() const
	{
		for (int i = 0; i < DATE_SIZE; ++i)
		{
			cout << static_cast<char>(_date[i] + '0');
			if (i == 1 || i == 3)
			{
				cout << '.';
			}
		}
	}

	bool ElectionRound::addNewCitizen(const char* name, int id, int birthyear, int districtId)
	{
		int saveDis;
		bool citizenAdded = false;
		if (!_districts.isCitizenExist(id, saveDis))
		{
			if (_districts.isDistcritExist(districtId))
			{
				Citizen* citiz = new Citizen(name, id, birthyear, districtId, nullptr, _districts.getDistcritById(districtId));
				citizenAdded = _districts.getDistcritById(districtId).addCitizen(citiz);
			}
		}
		return citizenAdded;
	}

	bool ElectionRound::addNewParty(const char* name,int pdId, int& partyId)
	{
		int distIndex;

		Citizen* leader = nullptr;
		bool partyAdded = false;
		if (_districts.isCitizenExist(pdId, distIndex))
		{
			leader = &(_districts.getDistcritByIndex(distIndex).getCitizenById(pdId));
			Party* par = new Party(name, pdId, _districts.getLogicSize(), *leader);
			partyId = par->getPartyID();
			leader->setParty(par);
			partyAdded = _parties.addToList(*par);
			_results.addParty();
		}
		return partyAdded;
	}

	bool ElectionRound::addNewPartyRepresentative(int representId, int partyId, int districtId)
	{
		int distIndex;
		bool represntAdded = false;
		if (_districts.isCitizenExist(representId, distIndex))
		{
			Citizen& citizenReprenst = _districts.getDistcritByIndex(distIndex).getCitizenById(representId);
			if (_districts.isDistcritExist(districtId) && _parties.IsPartyExist(partyId))
			{
				Party& currParty = _parties.getPartyByIndex(partyId );
				represntAdded = currParty.addPartyMember(citizenReprenst, abs(DISTRICT_ID_INIT - districtId));
				citizenReprenst.setParty(&currParty);
			}
		}
		return represntAdded;

	}

	void ElectionRound::viewAllDistricts() const
	{
		int len = _districts.getLogicSize();
		if (len > 0)
		{
			for (int i = 0; i < len; ++i)
			{
				cout << _districts.getDistcritByIndex(i) << endl;
			}
		}
		else
		{
			cout << "There are no districts to show." << endl;
		}
	}

	void ElectionRound::viewAllCitizens() const
	{
		int len = _districts.getLogicSize();
		if (len > 0)
		{
			for (int i = 0; i < len; ++i)
			{
				int lenOfCitizen = _districts.getDistcritByIndex(i).getNumberOfCitizens();
				if (lenOfCitizen > 0)
					cout << "The citizens who live in " << _districts.getDistcritByIndex(i).getName() << " are: " << endl;

				for (int j = 0; j < lenOfCitizen; ++j)
				{
					cout << _districts.getDistcritByIndex(i).getEligibleCitizens().getCitizenByIndex(j) << endl;
				}

			}
		}
		else
		{
			cout << "There are no citizens to show." << endl;
		}
	}

	void ElectionRound::viewAllParties() const
	{
		int len = _parties.getLogicSize();
		if (len > 0)
		{
			for (int i = 0; i < len; ++i)
			{
				cout << _parties.getPartyByIndex(i) << endl;
			}
		}
		else
		{
			cout << "There are no parties to show." << endl;
		}
	}


	bool ElectionRound::votingAction(int citizenId, int partyId)
	{
		int distIndex;
		bool isVotedCheck = true;
		if (_districts.isCitizenExist(citizenId, distIndex) && (_parties.IsPartyExist(partyId)))
		{
			District& tempDistrict = _districts.getDistcritByIndex(distIndex);
			Citizen& tempCitizen = tempDistrict.getCitizenById(citizenId);
			if (tempCitizen.hasVoted() == false) {
				tempCitizen.setHasVoted(true);

				_results.AddSingleVoteToArr(partyId, tempCitizen.getDistrictNum(), _parties.getLogicSize(), _districts.getLogicSize());
			}
			else
			{
				isVotedCheck = false;
			}
		}
		else
		{
			isVotedCheck = false;
		}
		return isVotedCheck;
	}


	bool ElectionRound::theResults()
	{
//		resultsArr countReps(_parties.getLogicSize(), _districts.getLogicSize());
		int districtAmount = _districts.getLogicSize();
		int partiesAmount = _parties.getLogicSize();
		int allVotesInDis = 0;
		double minVotesForRep;
		int amountOfElectedFromDistrict;
		pair* leftForPartyForElector = new pair[partiesAmount];
		int leftReps;
		pair* totalRepsForPmByID = new pair[partiesAmount];
		if (!_results.isResultsAllowed())
		{ 
			cout << "Sorry...Not enough details to get results" << endl; //todo: ask idan what to do about it
			return false;
		}
		else
		{

			for (int j = 0; j < districtAmount; j++)
			{
				for (int n = 0; n < partiesAmount; n++)
				{
					allVotesInDis = allVotesInDis + _results.getDistrictNumberOfVotesInParty(n, j + DISTRICT_ID_INIT);
				}
				District& tempDis = _districts.getDistcritByIndex(j);
				//present each district 
				//and num of representatives each district gives
				cout << tempDis << endl;
				//todo: move or delete
				cout << "each party got:" << endl;
				//CALCULATING NUMBER OF REPS FROM EACH PARTY

				minVotesForRep = double(allVotesInDis) / double(tempDis.getNumOfReps());
				for (int i = 0; i < partiesAmount; i++)
				{
					amountOfElectedFromDistrict = _results.getDistrictNumberOfVotesInParty(i, j + DISTRICT_ID_INIT)
						/ (minVotesForRep);
					_results.AddToPMRepsCount(j + DISTRICT_ID_INIT, i, amountOfElectedFromDistrict);
					leftForPartyForElector[i].repsAmount = _results.getDistrictNumberOfVotesInParty(i, j + DISTRICT_ID_INIT) -
						double(amountOfElectedFromDistrict * (allVotesInDis / tempDis.getNumOfReps()));
					leftForPartyForElector[i].index = i;
				}
				leftReps = tempDis.getNumOfReps();
				for (int k = 0; k < partiesAmount; k++)
				{
					leftReps = leftReps - _results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, k);
				}
				bubbleSort(leftForPartyForElector, partiesAmount);
				for (int l = 0; l < min(partiesAmount, leftReps); l++)
				{
					_results.AddToPMRepsCount(j + DISTRICT_ID_INIT, leftForPartyForElector[l].index, 1);
				}
				for (int m = 0; m < partiesAmount; m++) {
					cout << _parties.getPartyByIndex(m) << endl;
					//todo: use ostream instead
					cout << _results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, m) << " Reps" << endl;
					cout << "The Reps are: " << endl;
					//todo: fix - logicSize of representives is zero for some reason
					_parties.getPartyByIndex(m).printPartyRepsFromDistrictByAmount(_results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, m), j + DISTRICT_ID_INIT);
					cout << "Amount of Votes For The Party from Voting Citizens In The District: " << _results.getDistrictNumberOfVotesInParty(m, j + DISTRICT_ID_INIT) << endl;
					//todo: add to party class precentage of votes in each district and add it to operator
					cout << "Precentage of votes For The Party from Voting Citizens In The District is: " <<
						double(_results.getDistrictNumberOfVotesInParty(m, j + DISTRICT_ID_INIT)) / double(tempDis.getVotingCitizensAmountInDistrict()) * 100 << "%" << endl;

				} 
				//todo: update operator and remove after
				cout << "Voting Citizens Precentage In The District: " << tempDis.getVotersPercentage() << "%" << endl;
				int max = 0;
				int leaderWithMostRepsPartyID = 0;
				for (int p = 0; p < districtAmount; p++)
				{
					int curRepsAmount = _results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, p );
					if (max < curRepsAmount)
					{
						max = curRepsAmount;
						leaderWithMostRepsPartyID = p +PARTY_ID_INIT;

					}
				}
				//todo: remove "cout" after district leader added to operator in District.h
				cout << "The district belongs to: " <<
					_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader().getCitizenName() << endl;

				_results.setPmsRepsTotalByPartyID(leftForPartyForElector[0].index, tempDis.getNumOfReps());
			//todo: add district leader member and than apply line
			//	tempDis.setLeaderInDist(&(_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader()));
			}
			//check elections winner
			for (int n = 0; n < partiesAmount; n++)
			{
				totalRepsForPmByID[n].index = n;
				totalRepsForPmByID[n].repsAmount = _results.getPmsRepsTotalByPartyID(n);
			}
			bubbleSort(totalRepsForPmByID, partiesAmount);

			for (int p = 0; p < partiesAmount; p++)
			{
				//todo: print winnig citizen leader using ostream
				cout << _parties.getPartyByIndex(totalRepsForPmByID[p].index).getPartyLeader().getCitizenName()
					<< " got " << totalRepsForPmByID[p].repsAmount << " reps ";
				cout << "his party got total amount of " << _results.getTotalPartyNumberOfVotes(p) << " votes" << endl;

			}
			delete[] leftForPartyForElector;
			delete[] totalRepsForPmByID;
			return true;
		}

	}

	void ElectionRound::save(ofstream& outFile) const
	{
		cout << "saving ElectionRound" << endl;
		int numOfParties;
		int numOfDists;

		//Saving Date:
		outFile.write(rcastcc(_date), sizeof(int) * DATE_SIZE);
		// the number of dists:		
		numOfDists = _districts.getLogicSize();
			//number of dists:
		outFile.write(rcastcc(&numOfDists), sizeof(int));
		//saving the districts:
		cout << "saving districts" << endl;
		for (int i = 0; i < numOfDists; ++i)
		{
			_districts.getDistcritByIndex(i).save(outFile);
		}
		cout << "saving parties" << endl;
		// the number of parties:
		numOfParties = _parties.getLogicSize();
			//Saving number of parties:
		outFile.write(rcastcc(&numOfParties), sizeof(int));
		//Saving the parties:
		for (int i = 0; i < numOfParties; ++i)
		{
			//saving the partyLeadr id of party[i].
			int partyLeaderId = _parties.getPartyByIndex(i).getPartyPMCandidateID();
			outFile.write(rcastcc(&partyLeaderId), sizeof(int));
			_parties.getPartyByIndex(i).save(outFile);
		}
		//Saving resultArr:
	//	_results.save(outFile);


		
		cout << "done" << endl;
	}

	//todo: fix
	ostream& operator<<(ostream& os, const ElectionRound& electionRound) {
	

		return os;
	}


	void ElectionRound::swap(pair* xp, pair* yp)
	{
		pair temp = *xp;
		*xp = *yp;
		*yp = temp;
	}

	void ElectionRound::bubbleSort(pair arr[], int n)
	{
		int i, j;
		for (i = 0; i < n - 1; i++) {
			for (j = 0; j < n - i - 1; j++) {
				if (arr[j].repsAmount > arr[j + 1].repsAmount)
					swap(&arr[j], &arr[j + 1]);
			}
		}
	}
	//func deletes the max cell in arr and returns the index
	int  ElectionRound::deleteMax(double* parr, int size) {
		int i;
		double max = parr[0];
		int res = 0;
		for (i = 1; i < size; i++)
			if (parr[i] > max)
				res = i;
		parr[i] = 0;
		return res;



	}




}