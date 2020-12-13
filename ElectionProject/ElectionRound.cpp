//code verison 1.0
#include "ElectionRound.h"
#include <iostream>

#include "Party.h"

#include "DistrictList.h"
#include "CitizenList.h"
#include "PartyList.h"
using namespace std;

namespace elec {
	ElectionRound::ElectionRound(int date[8]) :_districts(DistrictList()), _parties(PartyList()), _results(resultsArr())
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
				_results.AddSingleVoteToArr(partyId, tempCitizen.getDistrictNum());
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


	void ElectionRound::theResults()
	{
		resultsArr countReps;
		char* pmWithTheMostRepsName = nullptr;
		const Citizen* partyLeader = nullptr;
		int totalPartyVotesPrecentage;
		int partyVotesInDistrict;
		int districtAmount = countReps.getdistrictsAmount();
		int partiesAmount = countReps.getpartiesAmount();
		int votingCitizensAmount;
		int allVotes = 0;
		if (!_results.isResultsAllowed()){
			cout << "Sorry...Not enough details to get results" << endl;
		}
		else {
			for (int i = 0; i < partiesAmount; i++)
				for (int n = 0; n < districtAmount; n++)
					allVotes = allVotes + _results.getDistrictNumberOfVotesInParty(i, n + DISTRICT_ID_INIT);



			for (int j = 0; j < districtAmount; j++) {
				District& tempDis = _districts.getDistcritByIndex(j);
				cout << "----------------------------------------------------" << endl;
				//present each district name
				cout << "From District Name: " << tempDis.getName() << endl;
				//num of representatives each district gives
				cout << "with Amount Of Reps: " << tempDis.getNumOfReps() << ", each party got:" << endl;
				for (int k = 0; k < partiesAmount; k++)  {
					partyVotesInDistrict = _results.getDistrictNumberOfVotesInParty(k, j + DISTRICT_ID_INIT);
					votingCitizensAmount = tempDis.getVotingCitizensAmountInDistrict();
					if (votingCitizensAmount == 0)
						totalPartyVotesPrecentage = 0;
					else
						totalPartyVotesPrecentage = partyVotesInDistrict / votingCitizensAmount * 100;
					
					//number of votes and precentages for each party
					cout << "The party: " << _parties.getPartyByIndex(k).getPartyName() << " Got " << partyVotesInDistrict << " votes." << endl <<
						"Which are " << totalPartyVotesPrecentage << "% of voting citizens in the district" << endl;
				}
				cout << "--The precentage of voting citizens in the District is: " <<
					double(tempDis.getVotingCitizensAmountInDistrict() * 100 / tempDis.getNumberOfCitizens()) << " --" << endl;
			}



			//how many from each party to each district
			double partyLeaderRepsFromDist;
			double votesForSingleRep;
			double* leftRepsDivision = new double[partiesAmount];
			for (int j = 0; j < partiesAmount; j++)
				leftRepsDivision[j] = 0;
			double partyLeaderRepsLeftOver = 0;
			for (int k = 0; k < districtAmount; k++) {
				for (int l = 0; l < partiesAmount; l++) {
					votesForSingleRep = double(allVotes) / double(_districts.getDistcritByIndex(l).getNumOfReps());
					partyLeaderRepsFromDist = double(_results.getTotalPartyNumberOfVotes(l)) / double(votesForSingleRep);
					countReps.AddToPMRepsCount(k + DISTRICT_ID_INIT, l, abs(partyLeaderRepsFromDist));
					countReps.setPmsRepsTotalByPartyID(l, abs(countReps.getPmsRepsTotalByPartyID(l) + (partyLeaderRepsFromDist)));
					partyLeaderRepsLeftOver = _results.getTotalPartyNumberOfVotes(l) - double(votesForSingleRep * int(partyLeaderRepsFromDist));
					leftRepsDivision[l] = leftRepsDivision[l] + partyLeaderRepsLeftOver;
				}

			}
			int leftReps = 0;
			for (int l = 0; l < districtAmount; l++) {
				int leftReps = _districts.getDistcritById(l + DISTRICT_ID_INIT).getNumOfReps() - countReps.getPmsRepsTotalByDistrictID(l + DISTRICT_ID_INIT);
				for (int p = 0; p < leftReps; p++) {
					int partyId;
					/*bug with deletting the max from leftRepsDivision*/
					partyId = deleteMax(leftRepsDivision, partiesAmount); //func deletes the max cell in arr and returns the index
					if (leftRepsDivision[partyId] != 0) {
						countReps.AddToPMRepsCount(l + DISTRICT_ID_INIT, partyId, 1);
						leftReps--;
						leftRepsDivision[partyId] = 0;
					}
				}
			}

		
	
			//present for each district the representatives list elected
			int partyLeaderReps;
			int maxRepsForPm = 0;
			for (int k = 0; k < districtAmount; k++) {
				cout << "The district " << _districts.getDistcritById(k+DISTRICT_ID_INIT).getName() << " Reps are: " << endl;
				for (int l = 0; l < partiesAmount; l++) {
					int num = countReps.getPMNumberOfRepsInDistrict(k + DISTRICT_ID_INIT, l);
					_parties.getPartyByIndex(l).printPartyRepsFromDistrictByAmount(num, k + DISTRICT_ID_INIT);
					// cout << "---namesOfReps---" << endl; //bug of not printing the reps... logicSize of partyrepsList is zero
					partyLeader = &(_parties.getPartyByIndex(l).getPartyLeader());
					partyLeaderReps = countReps.getPMNumberOfRepsInDistrict(k + DISTRICT_ID_INIT, l);
					cout << "The Party leader " << partyLeader->getCitizenName() << " got " <<
						partyLeaderReps << " Reps" << endl;
					if (partyLeaderReps > maxRepsForPm) {
						maxRepsForPm = partyLeaderReps;
						pmWithTheMostRepsName = new char[strlen(partyLeader->getCitizenName() + 1)];
						strcpy(pmWithTheMostRepsName, partyLeader->getCitizenName());
					}

				}
				//district winner check:
					//the party representativethe district belongs to
				cout << "the Pm party with the most reps is: " << pmWithTheMostRepsName << " who gets all " <<
					_districts.getDistcritById(k+DISTRICT_ID_INIT).getNumOfReps() << " reps " << endl;
				countReps.setPmsRepsTotalByPartyID(partyLeader->getParty()->getPartyID(), _districts.getDistcritById(k+DISTRICT_ID_INIT).getNumOfReps());
				_districts.getDistcritById(k + DISTRICT_ID_INIT).setLeaderInDist(partyLeader);
				maxRepsForPm = 0;
			}

			/***************************************************************************************/
			pair* pmCandidatesRepsArrSorted = new pair[partiesAmount];
			for (int m = 0; m < partiesAmount; m++) {
				pmCandidatesRepsArrSorted[m].index = m;
				pmCandidatesRepsArrSorted[m].repsAmount = countReps.getPmsRepsTotalByPartyID(m);
			}
			bubbleSort(pmCandidatesRepsArrSorted, partiesAmount);
			/*************************/

			int totalPartyVotes = 0;

			for (int i = 0; i < partiesAmount; i++) {
				
				//present for each party its candidate for PM, his amount of electors he got and amount of votes each party gor in all districts
				for (int l = 0; l < partiesAmount; l++)
					totalPartyVotes = totalPartyVotes + _results.getDistrictNumberOfVotesInParty(l, i + 100);
				cout << _parties.getPartyByIndex(pmCandidatesRepsArrSorted[i].index).getPartyLeader().getCitizenName() <<
					" got total amount of " << countReps.getPmsRepsTotalByPartyID(pmCandidatesRepsArrSorted[i].index) << " reps " <<
					endl << "His party got total amount of " << totalPartyVotes << " votes" << endl;
			}
			cout << "the ELECTIONS WINNER is: " << _parties.getPartyByIndex(pmCandidatesRepsArrSorted[partiesAmount-1].index).getPartyLeader().getCitizenName()
				<< " with " << countReps.getPmsRepsTotalByPartyID(pmCandidatesRepsArrSorted[partiesAmount - 1].index) << " electors" << endl;

			delete[] pmCandidatesRepsArrSorted;

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