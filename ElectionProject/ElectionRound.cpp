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
		int totalDistrictVotes = 0;
		int partyLeaderReps;
		int maxRepsForPm = 0;
		int totalPartyVotesPrecentage;
		int partyVotesInDistrict;
		int districtAmount = countReps.getdistrictsAmount();
		int partiesAmount = countReps.getpartiesAmount();

		for (int j = 0; j <= districtAmount; j++) {
			District& tempDis = _districts.getDistcritByIndex(j);//changed to by idx
			cout << "----------------------------------------------------";
			cout << "District Name: " << tempDis.getName() << endl;
			cout << "\nAmount Of Reps: " << tempDis.getNumOfReps() << endl;
			
			for (int k = 0; k < partiesAmount; k++) {
				partyVotesInDistrict = _results.getDistrictNumberOfVotesInParty(j + 100, k);
				totalPartyVotesPrecentage = partyVotesInDistrict / tempDis.getNumberOfCitizens() * 100;//from all citizens - not only voting ones
				cout << "\nThe party " << _parties.getPartyByIndex(k) << " got " << partyVotesInDistrict << " votes" << //delete after fix of the next comment
					"\nwhich are " << totalPartyVotesPrecentage << "precentage of votes from all citizens" <<endl;

		
				totalPartyVotesPrecentage = partyVotesInDistrict / tempDis.getVotingCitizensAmountInDistrict() * 100;

				cout << "The party " << _parties.getPartyByIndex(k) << " got " << partyVotesInDistrict << " votes" <<endl<<
					"Which are " << partyVotesInDistrict / tempDis.getVotingCitizensAmountInDistrict() * 100 <<
					"precentages of voting citizens in the district";



				partyLeaderReps = partyVotesInDistrict / tempDis.getNumberOfCitizens() * (tempDis.getNumOfReps());

				//todo: allow these lines after adding "printPartyRepsFromDistrictByAmount()" func:
				
				//roee answer:
				//TODO:roee check please
				_parties.getPartyByIndex(k).printPartyRepsFromDistrictByAmount(partyLeaderReps, tempDis.getSerialNum());

				 partyLeader = &(_parties.getPartyByIndex(k).getPartyLeader());
				cout << "\nThe Party leader " << partyLeader->getCitizenName() << " got " <<
					partyLeaderReps << "Reps";



				if (partyLeaderReps > maxRepsForPm) {
					maxRepsForPm = partyLeaderReps;
					strcpy(pmWithTheMostRepsName, partyLeader->getCitizenName());
				}
			}


			//todo: allow these lines after adding "getVotingCitizensAmountInDistrict()" func:
			//TODO:roee check please
		/*		cout << "The precentage of voting citizens in the District is: " <<
					tempDis.getVotingCitizensAmountInDistrict()/(tempDis.getEligibleCitizens() * 100);*/
					//todo idan need to ask roee what he means here? its an array not an int//tempDis.getEligibleCitizens()
		

						//district winner check:

					cout << "the Pm party with the most reps is: " << partyLeader->getCitizenName() << " who get all " <<
					tempDis.getNumOfReps() << " reps ";////TODO:roee check please if its fine my change

				//	countReps.setPmsRepsByPartyID(partyLeader->getParty()->getPartyID());
			maxRepsForPm = 0;
			//todo: allow this line after adding "setLeader(Citizen)" func:
			
		//tempDis.setLeaderInDist(partyLeader);
			
		}
		char* winnerName=nullptr;
		int winnerPartdId=0;
		// elections winner check:
		
		/* todo: allow these lines after =>
		  _parties.findPartyByID(i).PartyLeader() //to get in some other working way the citizen partyLeader
		  //todo : idan asks roee : what is i? findPartyByID(i).
		  */
			for (int i = 0; i < partiesAmount; i++)//idan added bracketsts.{} to the for
			{
				if (maxRepsForPm < countReps.getPmsRepsByPartyID(i)) {
					const Citizen& winner = _parties.getPartyByIndex(i).getPartyLeader();//changed to by index
					maxRepsForPm = countReps.getPmsRepsByPartyID(i);
					int winnerPartdId = winner.getParty()->getPartyID();
					strcpy(winnerName, winner.getCitizenName());
				}
			}
		cout << "the ELECTIONS WINNER is: " << winnerName << "with" <<
			countReps.getPmsRepsByPartyID(winnerPartdId) << "electors";


		
	}

	//TODO: roee choose if you want to delete the following functions or not 
	/*

		///ROEE MOVED FROM HEADER
		int checkWinningPMInDistrict(int districtID, resultsArr results) {
			int max = 0;
			int cur;
			int winnerPartyPmID = 0;
			for (int j = 0; j < _parties.getLogicSize(); j++) {
				cur = results.getPMNumberOfRepsInDistrict(j, districtID);
				if (max < cur) {
					max = cur;
					winnerPartyPmID = j;
				}
			}
			return winnerPartyPmID;
		}
		int checkWinnigPMRepsAmountInDistrict(resultsArr repsCountArr, int districtId) {// todelete
			int count = 0;
			for (int i = 0; i < _parties.getLogicSize(); i++) {
				count = count + repsCountArr.getPMNumberOfRepsInDistrict(i, districtId);
			}
			return count;
		}
		int checkTotalPartyVotesAmount(resultsArr results, int partyID) {
			int count = 0;
			for (int i = 0; i < _parties.getLogicSize(); i++) {
				count = count + results.getDistrictNumberOfVotesInParty(i + 100, partyID);
			}
			return count;



		}*/
}