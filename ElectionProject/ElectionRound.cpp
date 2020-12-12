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
				represntAdded = currParty.addPartyMember(citizenReprenst, distIndex);
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

	///TODO:idan
	void ElectionRound::theResults() 
	{


		/*******************************************************************************************/
		resultsArr countReps;
		char* pmWithTheMostRepsName=nullptr;
		const Citizen* partyLeader=nullptr;
		int partyLeaderReps;
		int maxRepsForPm = 0;
		int totalPartyVotesPrecentage;
		int partyVotesInDistrict;
		int districtAmount = countReps.getdistrictsAmount();
		int partiesAmount = countReps.getpartiesAmount();

		for (int j = 0; j <= districtAmount; j++) {
			District& tempDis = _districts.getDistcritByIndex(j);
			cout << "----------------------------------------------------" << endl;
			//לכל מחוז יש לההציג את שם המחוז
			cout << "District Name: " << tempDis.getName() << endl;
			//מספר הנציגים שהמחוז מעניק
			cout <<" Amount Of Reps: " << tempDis.getNumOfReps() << endl;
			for (int k = 0; k < partiesAmount; k++) {
				partyVotesInDistrict = _results.getDistrictNumberOfVotesInParty(j, k+100);
				//מספר ואחוז הקולות שקיבלה כל מפלגה
				totalPartyVotesPrecentage = partyVotesInDistrict / tempDis.getVotingCitizensAmountInDistrict() * 100;
				//roee: checked
				cout << "The party " << _parties.getPartyByIndex(k) << " got " << partyVotesInDistrict << " votes" << endl <<
					"Which are " << partyVotesInDistrict / tempDis.getVotingCitizensAmountInDistrict() * 100 <<
					"precentages of voting citizens in the district";
				partyLeaderReps = partyVotesInDistrict / tempDis.getNumberOfCitizens() * (tempDis.getNumOfReps());
			
				countReps.AddToPMRepsCount(j + 100, k, partyLeaderReps);
				//להציג לכל מחוז את רשימת הנציגים שנבחרה מכל מפלגה
				_parties.getPartyByIndex(k).printPartyRepsFromDistrictByAmount(partyLeaderReps, j + 100);
				partyLeader = &(_parties.getPartyByIndex(k).getPartyLeader());
				cout << endl <<"The Party leader " << partyLeader->getCitizenName() << " got " <<
					partyLeaderReps << "Reps";
				if (partyLeaderReps > maxRepsForPm) {
					maxRepsForPm = partyLeaderReps;
					pmWithTheMostRepsName = new char[strlen(partyLeader->getCitizenName() + 1)];
					strcpy(pmWithTheMostRepsName, partyLeader->getCitizenName());
				}
			}
			cout << "The precentage of voting citizens in the District is: " <<
				tempDis.getVotingCitizensAmountInDistrict() / (tempDis.getNumberOfCitizens() * 100);

			//district winner check:
			//מועמד המפלגה אליה המחוז משויך
			cout << "the Pm party with the most reps is: " << pmWithTheMostRepsName << " who gets all " <<
				tempDis.getNumOfReps() << " reps ";
		
			countReps.setPmsRepsByPartyID(partyLeader->getParty()->getPartyID());
			maxRepsForPm = 0;

			tempDis.setLeaderInDist(partyLeader);

		}

		/********* ADDED creating arr with pairs and sorting the repsAmount with selectionSort *******************/
		pair* pmCandidatesRepsArrSorted = new pair[partiesAmount];

		for (int m = 0; m < partiesAmount; m++) {
			pmCandidatesRepsArrSorted[m].index = m;
			pmCandidatesRepsArrSorted[m].repsAmount = countReps.getPmsRepsByPartyID(m);
		}
		int n = sizeof(pmCandidatesRepsArrSorted) / sizeof(int);
		int min;
		pair temp;
		for (int i = 0; i < n - 1; i++) {
			min = i;
			for (int j = i + 1; j < n; j++)
				if (pmCandidatesRepsArrSorted[j].repsAmount < pmCandidatesRepsArrSorted[min].repsAmount)
					min = j;
			temp = pmCandidatesRepsArrSorted[i];
			pmCandidatesRepsArrSorted[i] = pmCandidatesRepsArrSorted[min];
			pmCandidatesRepsArrSorted[min] = temp;
		}
		/***************************************************************************************/


		int totalPartyVotes = 0;

		for (int i = 0; i < partiesAmount; i++) {
			//להציג עבור כל מפלגה את המועמד שלה לראשות המדינה, סכום הנציגים שזכה בהם וסכום הקולות שקיבלה המפלגה בכל המחוזות
			for (int l = 0; l < partiesAmount; l++)
				totalPartyVotes = totalPartyVotes + _results.getDistrictNumberOfVotesInParty(l + 100, i);
			cout << _parties.getPartyByIndex(pmCandidatesRepsArrSorted[i].index).getPartyLeader().getCitizenName() <<
				" got total amount of " << countReps.getPmsRepsByPartyID(pmCandidatesRepsArrSorted[i].index) << " reps " <<
				endl<< "His party got total amount of" << totalPartyVotes << " votes";
		}
		cout << "the ELECTIONS WINNER is: " << _parties.getPartyByIndex(pmCandidatesRepsArrSorted[0].index).getPartyLeader().getCitizenName()
			<< " with" << countReps.getPmsRepsByPartyID(pmCandidatesRepsArrSorted[0].repsAmount) << "electors";

		delete[] pmCandidatesRepsArrSorted;


	}
}