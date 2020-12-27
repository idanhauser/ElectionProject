//code verison 2.0
#include "ElectionRound.h"
#include <iostream>
#include <algorithm>
#include "Party.h"

#include "DistrictList.h"
#include "CitizenList.h"
#include "PartyList.h"
#include "UnifiedDistrict.h"
#include "DividedDistrict.h"
using namespace std;

namespace elec {
	ElectionRound::ElectionRound(int date[8]) :_districts(), _parties(),
		_results(_parties.getLogicSize(), _districts.getLogicSize())
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

	void ElectionRound::viewAllDistricts()
	{
		int len = _districts.getLogicSize();

		if (len > 0)
		{
			calcReps();
			for (int i = 0; i <len; i++)
			{
				cout << _districts.getDistcritByIndex(i) << endl;
			}
		}
		else
		{
			cout << "There are no districts to show." << endl;
		}
	}

	bool ElectionRound::calcReps() {
		if (!isResultsAllowed())
			return false;
		int districtAmount = _districts.getLogicSize();
		int partiesAmount = _parties.getLogicSize();
		for (int j = 0; j < districtAmount; j++)
		{
			_results.VotesToRepsInDistrictByDistrictID(_districts.getDistcritByIndex(j).getSerialNum(),
				_districts.getDistcritByIndex(j).getNumOfReps(), _districts.getDistcritByIndex(j));

			if (typeid(_districts.getDistcritByIndex(j)) == typeid(UnifiedDistrict))
			{
				_results.setWinnerInUnifiedDistrictByDistrictID(_districts.getDistcritByIndex(j).getSerialNum(), _districts.getDistcritByIndex(j).getNumOfReps(), _districts.getDistcritByIndex(j));
				
			}
			else
			{
				//todo: copy all values from Reps arr in _results.repsPartiesById member to dividedDistrict reps arr
				for (int i = 0; i < partiesAmount; i++)
				{
					_districts.getDistcritByIndex(j).setRepsArrByPartyID(i + PARTY_ID_INIT, _results.getPMNumberOfRepsInDistrict(_districts.getDistcritByIndex(j).getSerialNum(), i + PARTY_ID_INIT));
				}
			}
		}
		return true;

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

				double votingForPartyFromVotersInDistrictPrecentage = double(_results.getDistrictNumberOfVotesInParty(partyId - PARTY_ID_INIT, distIndex + DISTRICT_ID_INIT)) /
					double(_districts.getDistcritById(distIndex + DISTRICT_ID_INIT).getVotingCitizensAmountInDistrict()) * 100;
				_parties.getPartyByIndex(partyId - PARTY_ID_INIT).setVotingPercentagesDistrict(votingForPartyFromVotersInDistrictPrecentage, distIndex + DISTRICT_ID_INIT);

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
	{ // todo: fix - not sure if needed. we can just call from outside the if and "calcReps"
		if (!isResultsAllowed())
			return false;
		calcReps();
		
		return true;
	}
	
	//todo: fix
	ostream& operator<<(ostream& os, ElectionRound& electionRound) {
		os << electionRound._date << endl;
		if (!electionRound.isResultsAllowed())
		{
			os << "Sorry...Not enough details to get results" << endl;
			return os;
		}
		else
		{
			int districtAmount = electionRound._districts.getLogicSize();
			int partiesAmount = electionRound._parties.getLogicSize();
			for (int j = 0; j < districtAmount; j++)
			{
				//present each district 
				//and num of representatives each district gives
				
				os << electionRound._districts.getDistcritByIndex(j) << endl;
				os << "each party got:" << endl;
				//todo: delete
				//electionRound.VotesToRepsInDistrictByDistrictID(j + DISTRICT_ID_INIT);
				//print results:
				if (typeid(electionRound._districts.getDistcritByIndex(j)) == typeid(UnifiedDistrict))
				{
					for (int m = 0; m < partiesAmount; m++)
					{
						os << electionRound._parties.getPartyByIndex(m) << endl;
						os << electionRound._results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, m) << " Reps" << endl;
						os << "The Reps are: " << endl;
						//todo: fix - logicSize of representives is zero for some reason
						electionRound._parties.getPartyByIndex(m).printPartyRepsFromDistrictByAmount(electionRound._results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, m), j + DISTRICT_ID_INIT);
						os << "Amount of Votes For The Party from Voting Citizens In The District: " <<
							electionRound._results.getDistrictNumberOfVotesInParty(m, j + DISTRICT_ID_INIT) << endl;
						os << "Precentage of votes For The Party from Voting Citizens In The District is: " <<
							electionRound._parties.getPartyByIndex(m).getVotingPercentagesDistrict(j + DISTRICT_ID_INIT) <<
							"%" << endl;

					}

					//todo: delete
					//electionRound.setWinnerInUnifiedDistrictByDistrictID(j + DISTRICT_ID_INIT);

					//todo: apply line after fix for getdistrictbyid to return pointer to any kind of district (polimorphysm)
					// os << "The district belongs to: " << static_cast<UnifiedDistrict*>(electionRound._districts.getDistcritById(j))->getPartyLeader(); 
				}
				else
				{
					  // = its a divided district - Only needed to present reps in max to min order
						for (int m = 0; m < partiesAmount; m++)
						{
							int* PartyIndexesSotedByReps = electionRound._results.getPMNRepsArrInDistrict(m+PARTY_ID_INIT);
							for (int w = 0; w < districtAmount; w++)
							{
								electionRound.sortDistrictWinners(w + DISTRICT_ID_INIT, PartyIndexesSotedByReps);
							}
							os << electionRound._parties.getPartyByIndex(PartyIndexesSotedByReps[m]) << endl;
							os << electionRound._results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, PartyIndexesSotedByReps[m]) << " Reps" << endl;
							os << "The Reps are: " << endl;
							//todo: fix - logicSize of representives is zero for some reason
							electionRound._parties.getPartyByIndex(PartyIndexesSotedByReps[m]).printPartyRepsFromDistrictByAmount(electionRound._results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, PartyIndexesSotedByReps[m]), j + DISTRICT_ID_INIT);
							os << "Amount of Votes For The Party from Voting Citizens In The District: " <<
								electionRound._results.getDistrictNumberOfVotesInParty(PartyIndexesSotedByReps[m], j + DISTRICT_ID_INIT) << endl;
							os << "Precentage of votes For The Party from Voting Citizens In The District is: " <<
								electionRound._parties.getPartyByIndex(PartyIndexesSotedByReps[m]).getVotingPercentagesDistrict(j + DISTRICT_ID_INIT) << "%" << endl;

						}//no need to check for winner, printing sorted is enough
				}
					


				//elections winner
				int* partiesIndexs = new int[partiesAmount];
				electionRound.checkElectionsWinner(partiesIndexs);
				for (int p = 0; p < partiesAmount; p++)
				{
					//todo: print winnig citizen leader using ostream
					os << electionRound._parties.getPartyByIndex(partiesIndexs[p]).getPartyLeader().getCitizenName()
						<< " got " << electionRound._results.getPmsRepsTotalByPartyID(partiesIndexs[p]) << " reps ";
					os << "his party got total amount of " << electionRound._results.getTotalPartyNumberOfVotes(partiesIndexs[p]) << " votes" << endl;

				}
				delete[] partiesIndexs;




				return os;
			}
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


	


	//bool ElectionRound::VotesToRepsInDistrictByDistrictID(int districtID) {
	//	int leftReps;
	//	int amountOfElectedFromDistrict;
	//	pair* leftForPartyForElector = new pair[_parties.getLogicSize()];
	//	int allVotesInDis = 0;
	//	for (int n = 0; n < _parties.getLogicSize(); n++)
	//	{
	//		allVotesInDis = allVotesInDis + _results.getDistrictNumberOfVotesInParty(n + PARTY_ID_INIT, districtID);
	//	}
	//	District& tempDis = _districts.getDistcritByIndex(districtID - DISTRICT_ID_INIT);
	//	
	//	//CALCULATING NUMBER OF REPS FROM EACH PARTY
	//	double minVotesForRep = double(allVotesInDis) / double(tempDis.getNumOfReps());
	//	for (int i = 0; i < _parties.getLogicSize(); i++)
	//	{
	//		amountOfElectedFromDistrict = _results.getDistrictNumberOfVotesInParty(i, districtID)
	//			/ minVotesForRep;
	//		_results.AddToPMRepsCount(districtID, i, amountOfElectedFromDistrict);
	//		leftForPartyForElector[i].repsAmount = _results.getDistrictNumberOfVotesInParty(i, districtID) -
	//			double(amountOfElectedFromDistrict * minVotesForRep);
	//		leftForPartyForElector[i].index = i;
	//	}
	//	leftReps = tempDis.getNumOfReps();
	//	for (int k = 0; k < _parties.getLogicSize(); k++)
	//	{
	//		leftReps = leftReps - _results.getPMNumberOfRepsInDistrict(districtID, k);
	//	}
	//	bubbleSort(leftForPartyForElector, _parties.getLogicSize());
	//	for (int l = 0; l < min(_parties.getLogicSize(), leftReps); l++)
	//	{
	//		_results.AddToPMRepsCount(districtID, leftForPartyForElector[l].index, 1);
	//	}

	//	delete[] leftForPartyForElector;

	//	return true;
	//}


	//bool ElectionRound::setWinnerInUnifiedDistrictByDistrictID(int districtID) {
	//	//todo: change from District& tempDis to unified district type
	//	District& tempDis = _districts.getDistcritById(districtID);
	//	int max = 0;
	//	int leaderWithMostRepsPartyID = 0;
	//	for (int p = 0; p < _parties.getLogicSize(); p++)
	//	{
	//		int curRepsAmount = _results.getPMNumberOfRepsInDistrict(districtID, p + PARTY_ID_INIT);
	//		if (max < curRepsAmount)
	//		{
	//			max = curRepsAmount;
	//			leaderWithMostRepsPartyID = p + PARTY_ID_INIT;

	//		}
	//	}
	//	//todo: apply after first line change
	//	//tempDis.setLeader(_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader());

	//	_results.addToPmsRepsTotalByPartyID(leaderWithMostRepsPartyID, tempDis.getNumOfReps());
	//	
	//	//todo: remove next line after district leader is set in UnifiedDistrict.h
	//	cout << "The district belongs to: " <<
	//		_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader().getCitizenName() << endl;
	//	
	//	return true;
	//}




	bool ElectionRound::checkElectionsWinner(int* partiesIndexes){
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
			partiesIndexes[p] = totalRepsForPmByID[p].index;

		}
		delete[] totalRepsForPmByID;
		return true;
	}


	bool ElectionRound::sortDistrictWinners(int districtID, int* partiesIndexes) {
		
		pair* totalRepsForPmByID = new pair[_parties.getLogicSize()];

		for (int n = 0; n < _districts.getLogicSize(); n++)
		{
			totalRepsForPmByID[n].index = n;
			totalRepsForPmByID[n].repsAmount = _results.getPMNumberOfRepsInDistrict(districtID, n);
		}
		bubbleSort(totalRepsForPmByID, _districts.getLogicSize());

		for (int p = 0; p < _parties.getLogicSize(); p++)
		{
			partiesIndexes[p] = totalRepsForPmByID[p].index;

		}
		delete[] totalRepsForPmByID;
		return true;
	}


	bool ElectionRound::isResultsAllowed()const
	{
		if ((_parties.getLogicSize() != 0) && (_districts.getLogicSize()!= 0))
			return true;
		else
			return false;
	}

}