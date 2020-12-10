//code verison 1.0
#include "ElectionRound.h"
#include <iostream>

#include "Party.h"

#include "DistrictList.h"
#include "CitizenList.h"
#include "PartyList.h"
using namespace std;

namespace elec
{
	ElectionRound::ElectionRound(int date[8]) :_districts(DistrictList()), _parties(PartyList()),_results(resultsArr())
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


}
	
	//todo:roee
	void ElectionRound::votingAction(CitizenList& _citizens, resultsArr& results)//need to change to _districts
	{
		int id, party_id;
		cout << "\nType your ID: ";
		cin >> id;
		cout << "\nEnter your vote party ID: ";
		cin >> party_id;
		//todo: fix lines after merge:
		//should  isCitizenExist() if returned distIndex => getCitizenByIndex(getDIstrictByIndex( distIndex))
		//if true: use 
		Citizen* tempCitizen = _citizens.findCitizenByID(id);//need to change to find the right way after merge or upper comment
		if (tempCitizen->hasVoted() == false) {
			tempCitizen->setHasVoted(true);
			results.AddSingleVoteToArr(party_id, tempCitizen->getCitizenDistrictNum());
		}
		else
			cout << "\nYou've voted already !! ";
	}

	void ElectionRound::theResults(resultsArr& votesResults) {
	

/*******************************************************************************************/
		District* tempDis;
		resultsArr countReps;
		char* pmWithTheMostRepsName;
		Citizen *partyLeader;
		int totalDistrictVotes = 0, partyLeaderReps, maxRepsForPm=0, totalPartyVotesPrecentage, partyVotesInDistrict;
		int districtAmount = countReps.getdistrictsAmount(), partiesAmount = countReps.getpartiesAmount();
		
		for (int j = 0; j <= districtAmount; j++) {
			tempDis = _districts.findDistrictByID(j + 100);
			cout << "\n----------------------------------------------------";
			cout << "\nDistrict Name: " << tempDis->getName();
			cout << "\nAmount Of Reps: " << tempDis->getNumOfReps();
			for (int k = 0; k < partiesAmount; k++) {
				partyVotesInDistrict = votesResults.getDistrictNumberOfVotesInParty(j + 100, k);
				totalPartyVotesPrecentage = partyVotesInDistrict / tempDis->getNumberOfCitizens() * 100;//from all citizens - not only voting ones
				cout << "\nThe party " << _parties.findPartyByID(k) << " got " << partyVotesInDistrict << " votes"<< //delete after fix of the next comment
					"\nwhich are " << totalPartyVotesPrecentage << "precentage of votes from all citizens";
				
				/*todo: allow these lines after adding "getVotingCitizensAmountInDistrict()" func:
				
				totalPartyVotesPrecentage = partyVotesInDistrict / tempDis->getVotingCitizensAmountInDistrict() * 100;
				cout << "\nThe party " << _parties.findPartyByID(k) << " got " << partyVotesInDistrict << " votes"<< 
					"\nwhich are " << partyVotesInDistrict/getVotingCitizensAmountInDistrict()*100 <<
					"precentages of voting citizens in the district";
				
				*/
				
				partyLeaderReps = partyVotesInDistrict / tempDis->getNumberOfCitizens() * (tempDis->getNumOfReps());
				
				/*todo: allow these lines after adding "printPartyRepsFromDistrictByAmount()" func:
				
				printPartyRepsFromDistrictByAmount(partyLeaderReps)
				partyLeader = _parties.findPartyByID(k).getPartyLeader();
				cout << "\nThe Party leader " << partyLeader.getCitizenName() << " got " <<
					partyLeaderReps << "Reps";
					
					*/

				if (partyLeaderReps > maxRepsForPm) {
					maxRepsForPm = partyLeaderReps;
					strcpy(pmWithTheMostRepsName, partyLeader->getCitizenName());
				}
			}
			
			/*todo: allow these lines after adding "getVotingCitizensAmountInDistrict()" func:

			cout << "The precentage of voting citizens in the District is: " <<
				tempDis.getVotingCitizensAmountInDistrict()/tempDis->getEligibleCitizens() * 100;
				
				*/


			//district winner check:


			cout << "the Pm party with the most reps is: " << partyLeader->getCitizenName() << " who get all " <<
				tempDis->getNumOfReps() << " reps ";
			
			countReps.setPmsRepsByPartyID(partyLeader->getParty()->getPartyID());
			maxRepsForPm = 0;
			/*todo: allow this line after adding "setLeader(Citizen)" func:

			tempDis.setLeader(partyLeader);
			
			*/
		}
		
		// elections winner check:
		
		/* todo: allow these lines after =>
		//=>fix  _parties.findPartyByID(i).PartyLeader() to get in some other working way the citizen partyLeader
		
		
		for (int i = 0; i < partiesAmount; i++)
			if (maxRepsForPm < countReps.getPmsRepsByPartyID(i)) {
				//Citizen winner = _parties.findPartyByID(i).PartyLeader(); 
				maxRepsForPm = countReps.getPmsRepsByPartyID(i);
			}
		cout << "the ELECTIONS WINNER is: " << winner->getCitizenName() << "with" <<
			countReps.getPmsRepsByPartyID(winner->getParty().getPartyID()) << "electors";


		*/









}
