//code verison 2.0
#include "ElectionRound.h"
#include <iostream>
#include <algorithm>
#include "Party.h"

#include "DistrictList.h"
#include "CitizenList.h"
#include "PartyList.h"
using namespace std;

namespace elec {
	ElectionRound::ElectionRound(int date[8]) :_districts(), _parties(),
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

	bool ElectionRound::addNewDistrict(const char name[MAX_SIZE], int numberResentatives, int& districtId)
	{
		bool districtAdded = false;
		District* dist = new District(name, numberResentatives);
		districtId = dist->getSerialNum();
		districtAdded = _districts.addToList(*dist);
		for (int i = 0; i < _parties.getLogicSize(); ++i)
		{
			_parties.getPartyByIndex(i).updateParties();
		}
		_results.addDistrict();
		_results.setdistrictsAmount();
		return districtAdded;
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

	bool ElectionRound::addNewParty(const char* name,int pdId, int& partyid)
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
				tempDistrict.settVotersPrecentage(double(tempDistrict.getVotingCitizensAmountInDistrict() / tempDistrict.getNumberOfCitizens()) * 100);
				//todo: apply after idan adds member of votersPrecentage arr in Party.h
				// _parties.getPartyByIndex(partyId+PARTY_ID_INIT).setVotersPrecetageArr(distIndex)
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
		int leftReps;
		if (!_results.isResultsAllowed())
		{ 
			 //todo: ask idan how to use with ostream to print it
			cout << "Sorry...Not enough details to get results" << endl;
			return false;
		}
		else
		{
			for (int j = 0; j < districtAmount; j++)
			{
				//present each district 
				//and num of representatives each district gives
				District& tempDis = _districts.getDistcritByIndex(j - DISTRICT_ID_INIT);
				cout << tempDis << endl;
				calcVotesInDistrictByDistrictID(j + DISTRICT_ID_INIT);
				//print results:
				//todo: use ostream instead
				for (int m = 0; m < partiesAmount; m++) 
				{
					cout << _parties.getPartyByIndex(m) << endl;
					//todo: use ostream instead cout
					cout << _results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, m) << " Reps" << endl;
					cout << "The Reps are: " << endl;
					//todo: fix - logicSize of representives is zero for some reason
					_parties.getPartyByIndex(m).printPartyRepsFromDistrictByAmount(_results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, m), j + DISTRICT_ID_INIT);
					cout << "Amount of Votes For The Party from Voting Citizens In The District: " << _results.getDistrictNumberOfVotesInParty(m, j + DISTRICT_ID_INIT) << endl;
					//todo: add to party.h arr of precentage of votes in each district/ mke sure its in operator
					int votingForPartyFromVotersInDistrictPrecentage = double(_results.getDistrictNumberOfVotesInParty(m, j + DISTRICT_ID_INIT)) /
						double(_districts.getDistcritById(j + DISTRICT_ID_INIT).getVotingCitizensAmountInDistrict()) * 100;
					cout << "Precentage of votes For The Party from Voting Citizens In The District is: " <<
						votingForPartyFromVotersInDistrictPrecentage << "%" << endl;

				} 
				//if (unified district)
				setWinnerInUnifiedDistrictByDistrictID(j + DISTRICT_ID_INIT);
			
				//	else (its a divided district)
				//no need to check for winner, the caclculation is enough
			}
			checkElectionsWinner();
		}

	}
	
	
	//todo: fix
	/*ostream& operator<<(ostream& os, const ElectionRound& electionRound) {
		for (int j = 0; j < &electionRound; j++)
		{
			District& tempDis = electionRound._districts.getDistcritByIndex(j);
			//present each district 
			//and num of representatives each district gives
			os << tempDis << endl;
			//todo: move or delete
			os << "each party got:" << endl;

		
		
		}
		os << electionRound;
			}
	}*/




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


	


	bool ElectionRound::calcVotesInDistrictByDistrictID(int districtID) {
		int leftReps;
		int amountOfElectedFromDistrict;
		pair* leftForPartyForElector = new pair[_parties.getLogicSize()];
		int allVotesInDis = 0;
		for (int n = 0; n < _parties.getLogicSize(); n++)
		{
			allVotesInDis = allVotesInDis + _results.getDistrictNumberOfVotesInParty(n, districtID);
		}
		District& tempDis = _districts.getDistcritByIndex(districtID - DISTRICT_ID_INIT);
		//present each district 
		//and num of representatives each district gives
		cout << tempDis << endl;
		//todo: move or delete
		cout << "each party got:" << endl;
		
		//CALCULATING NUMBER OF REPS FROM EACH PARTY
		double minVotesForRep = double(allVotesInDis) / double(tempDis.getNumOfReps());
		for (int i = 0; i < _parties.getLogicSize(); i++)
		{
			amountOfElectedFromDistrict = _results.getDistrictNumberOfVotesInParty(i, districtID)
				/ (minVotesForRep);
			_results.AddToPMRepsCount(districtID, i, amountOfElectedFromDistrict);
			leftForPartyForElector[i].repsAmount = _results.getDistrictNumberOfVotesInParty(i, districtID) -
				double(amountOfElectedFromDistrict * (allVotesInDis / tempDis.getNumOfReps()));
			leftForPartyForElector[i].index = i;
		}
		leftReps = tempDis.getNumOfReps();
		for (int k = 0; k < _parties.getLogicSize(); k++)
		{
			leftReps = leftReps - _results.getPMNumberOfRepsInDistrict(districtID, k);
		}
		bubbleSort(leftForPartyForElector, _parties.getLogicSize());
		for (int l = 0; l < min(_parties.getLogicSize(), leftReps); l++)
		{
			_results.AddToPMRepsCount(districtID, leftForPartyForElector[l].index, 1);
		}

		delete[] leftForPartyForElector;

		return true;
	}


	bool ElectionRound::setWinnerInUnifiedDistrictByDistrictID(int districtID) {
		//yodo: change from district to  unified district
		District& tempDis = _districts.getDistcritById(districtID);
		int max = 0;
		int leaderWithMostRepsPartyID = 0;
		for (int p = 0; p < _parties.getLogicSize(); p++)
		{
			int curRepsAmount = _results.getPMNumberOfRepsInDistrict(districtID, p + PARTY_ID_INIT);
			if (max < curRepsAmount)
			{
				max = curRepsAmount;
				leaderWithMostRepsPartyID = p + PARTY_ID_INIT;

			}
		}
		//todo: apply after first line change
		//tempDis.setLeader(_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader());

		_results.setPmsRepsTotalByPartyID(leaderWithMostRepsPartyID, tempDis.getNumOfReps());
		
		//todo: remove "cout" after district leader added to operator in District.h
		cout << "The district belongs to: " <<
			_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader().getCitizenName() << endl;
		
		return true;
	}




	bool ElectionRound::checkElectionsWinner(){
		//check elections winner
		pair* totalRepsForPmByID = new pair[_parties.getLogicSize()];
		for (int n = 0; n < _parties.getLogicSize(); n++)
		{
			totalRepsForPmByID[n].index = n;
			totalRepsForPmByID[n].repsAmount = _results.getPmsRepsTotalByPartyID(n);
		}
		bubbleSort(totalRepsForPmByID, _parties.getLogicSize());

		for (int p = 0; p < _parties.getLogicSize(); p++)
		{
			//todo: print winnig citizen leader using ostream
			cout << _parties.getPartyByIndex(totalRepsForPmByID[p].index).getPartyLeader().getCitizenName()
				<< " got " << totalRepsForPmByID[p].repsAmount << " reps ";
			cout << "his party got total amount of " << _results.getTotalPartyNumberOfVotes(p) << " votes" << endl;

		}
		delete[] totalRepsForPmByID;
		return true;
	}
}