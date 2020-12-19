//code verison 1.0
#include "ElectionRound.h"
#include <iostream>

#include "Party.h"

#include "DistrictList.h"
#include "CitizenList.h"
#include "PartyList.h"
using namespace std;

namespace elec {
	ElectionRound::ElectionRound(int date[8]) :_districts(DistrictList()), _parties(PartyList()),
		_results(resultsArr(_parties.getLogicSize(), _districts.getLogicSize()))
	{

		for (int i = 0; i < 8; ++i)
		{
			this->_date[i] = date[i];
		}
	}

	void ElectionRound::printElectionDate() const
	{
		for (int i = 0; i < 8; ++i)
		{
			cout << static_cast<char>(_date[i] + '0');
			if (i == 1 || i == 3)
			{
				cout << '.';
			}
		}
	}

	bool ElectionRound::addNewDistrict(char name[MAX_SIZE], int numberResentatives, int& districtId)
	{
		bool districtAdded = false;
		District* dist = new District(name, numberResentatives);
		districtId = dist->getSerialNum();
		districtAdded = _districts.addToList(*dist);
		for (int i = 0; i < _parties.getLogicSize(); ++i)
		{
			_parties.getPartyByIndex(i).AddAnotherColumn();
		}
		_results.addDistrict();
		_results.setdistrictsAmount();
		return districtAdded;
	}


	bool ElectionRound::addNewCitizen(char* name, int id, int birthyear, int districtId)
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

	bool ElectionRound::addNewParty(char* name, int pdId, int& partyid)
	{
		int distIndex;

		Citizen* leader = nullptr;
		bool partyAdded = false;
		if (_districts.isCitizenExist(pdId, distIndex))
		{
			leader = &(_districts.getDistcritByIndex(distIndex).getCitizenById(pdId));
			Party* par = new Party(name, pdId, _districts.getLogicSize(), *leader);
			partyid = par->getPartyID();
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
				Party& currParty = _parties.getPartyByIndex(abs(partyId - PARTY_ID_INIT));
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
				int lenofcitizen = _districts.getDistcritByIndex(i).getNumberOfCitizens();
				if (lenofcitizen > 0)
					cout << "The citizens who live in " << _districts.getDistcritByIndex(i).getName() << "are: " << endl;

				for (int j = 0; j < lenofcitizen; ++j)
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
		if (_districts.isCitizenExist(citizenId, distIndex))
		{
			Citizen& tempCitizen = _districts.getDistcritByIndex(distIndex).getCitizenById(citizenId);
			if (tempCitizen.hasVoted() == false) {
				tempCitizen.setHasVoted(true);
				
				_results.AddSingleVoteToArr(partyId, tempCitizen.getDistrictNum(), _parties.getLogicSize(), _districts.getLogicSize() );
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
		resultsArr countReps(_parties.getLogicSize(), _districts.getLogicSize());
		int districtAmount = _districts.getLogicSize();
		int partiesAmount = _parties.getLogicSize();
		int allVotesInDis = 0;
		double minVotesForRep;
		int amountOfElectedFromDistrict;
		pair* leftForPartyForElector = new pair[partiesAmount];
		int leftReps;
		pair* totalRepsForPmByID = new pair[partiesAmount];
		if (!_results.isResultsAllowed()) { //todo: need to fix
			cout << "Sorry...Not enough details to get results" << endl;
			return false;
		}
		else {

			for (int j = 0; j < districtAmount; j++) {
				for (int n = 0; n < partiesAmount; n++)
					allVotesInDis = allVotesInDis + _results.getDistrictNumberOfVotesInParty(n, j + DISTRICT_ID_INIT);
				District& tempDis = _districts.getDistcritByIndex(j);
				cout << "----------------------------------------------------" << endl;
				//present each district name
				cout << "From District Name: " << tempDis.getName() << endl;
				//num of representatives each district gives
				cout << "with Amount Of Reps: " << tempDis.getNumOfReps() << ", each party got:" << endl;
				//CALCULATING NUMBER OF REPS FROM EACH PARTY

				minVotesForRep = double(allVotesInDis) / double(tempDis.getNumOfReps());
				for (int i = 0; i < partiesAmount; i++) {
					amountOfElectedFromDistrict = _results.getDistrictNumberOfVotesInParty(i, j + DISTRICT_ID_INIT)
						/ (minVotesForRep);
					_results.AddToPMRepsCount(j + DISTRICT_ID_INIT, i, amountOfElectedFromDistrict);
					leftForPartyForElector[i].repsAmount = _results.getDistrictNumberOfVotesInParty(i, j + DISTRICT_ID_INIT) -
						double(amountOfElectedFromDistrict * (allVotesInDis / tempDis.getNumOfReps()));
					leftForPartyForElector[i].index = i;
				}
				leftReps = tempDis.getNumOfReps();
				for (int k = 0; k < partiesAmount; k++)
					leftReps = leftReps - _results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, k);
				//todo: func sorting leftForPartyForElector by max
				bubbleSort(leftForPartyForElector, partiesAmount);
				for (int l = 0; l < min(partiesAmount,leftReps); l++)
					_results.AddToPMRepsCount(j + DISTRICT_ID_INIT, leftForPartyForElector[l].index, 1);
				for (int m = 0; m < partiesAmount; m++) {
					cout << _parties.getPartyByIndex(m).getPartyName() << ":" << endl;
					cout << _results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, m) << " Reps" << endl;
					cout << "The Reps are: " << endl;
					//todo: fix - logicSize of representives is zero for some reason
					_parties.getPartyByIndex(m).printPartyRepsFromDistrictByAmount(_results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, m), j + DISTRICT_ID_INIT);
					cout << "Amount of Votes For The Party from Voting Citizens In The District: " << _results.getDistrictNumberOfVotesInParty(m, j + DISTRICT_ID_INIT) << endl;
					cout << "Precentage of votes For The Party from Voting Citizens In The District is: " <<
						double(_results.getDistrictNumberOfVotesInParty(m, j + DISTRICT_ID_INIT)) / double(tempDis.getVotingCitizensAmountInDistrict()) * 100 << "%" << endl;

				} //todo: update voters precentage in district
				cout << "Voting Citizens Precentage In The District: " << tempDis.getVotersPercentage() << "%" << endl;
				cout << "The district belongs to: " <<
					_parties.getPartyByIndex(leftForPartyForElector[0].index).getPartyLeader().getCitizenName() << endl;
				_results.setPmsRepsTotalByPartyID(leftForPartyForElector[0].index, tempDis.getNumOfReps());
				tempDis.setLeaderInDist(&(_parties.getPartyByIndex(leftForPartyForElector[0].index).getPartyLeader()));
			}
			for (int n = 0; n < partiesAmount; n++) {
				totalRepsForPmByID[n].index = n;
				totalRepsForPmByID[n].repsAmount = _results.getPmsRepsTotalByPartyID(n);
			}
			bubbleSort(totalRepsForPmByID, partiesAmount);

			for (int p = 0; p < partiesAmount; p++) {

				cout << _parties.getPartyByIndex(totalRepsForPmByID[p].index).getPartyLeader().getCitizenName()
					<< " got " << totalRepsForPmByID[p].repsAmount << " reps ";
				cout << "his party got total amount of " << _results.getTotalPartyNumberOfVotes(p) << " votes" << endl;

			}
			delete[] leftForPartyForElector;
			delete[] totalRepsForPmByID;
			return true;
		}

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
		int res=0;
		for (i = 1; i < size; i++)
			if (parr[i] > max)
				res=i;
		parr[i] = 0;
		return res;

	
	
	}
}