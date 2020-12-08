
#include "ElectionRound.h"

//code verison 1.0
#include <iostream>


#include "DistrictList.h"
#include "CitizenList.h"
#include "PartyList.h"

using namespace std;

namespace elec
{
	ElectionRound::ElectionRound(int date[8]) :
		_citizens(CitizenList()), _districts(DistrictList()), _parties(PartyList()), results(resultsArr()) //todo: was initiated thi way: _citizens(CITIZENSlIST()). Check if the fix is fine)
	{
		//_citizens should be deleted
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



	//todo:roee
	void ElectionRound::votingAction(CitizenList& _citizens, resultsArr& results)//need to change to _districts
	{
		int id, party_id;
		cout << "\nType your ID: ";
		cin >> id;
		cout << "\nEnter your vote party ID: ";
		cin >> party_id;
		//should  isCitizenExist() if returned distIndex => getCitizenByIndex(getDIstrictByIndex( distIndex))
		//if true: use 
		Citizen* tempCitizen = _citizens.findCitizenByID(id);//need to change to _districts.findCitizenByID(id) or upper comment
		if (tempCitizen->hasVoted() == false) {
			tempCitizen->setHasVoted(true);
			results.AddSingleVoteToArr(party_id, tempCitizen->getCitizenDistrictNum());
		}
		else
			cout << "\nYou've voted already !! ";
	}

	void ElectionRound::theResults(resultsArr& votesResults) {
		resultsArr repsCounter;
		int partyVotesInDistrict;
		int tempWinnerReps;
		int totalWinningPMPartyVotes = 0, totalPartyVotes = 0, totalPartyMembersForPM = 0;
		int AmountOfPartyMembersFromSingleDistrict;
		int partiesAmount = _parties.getLogicSize();
		int districtsAmount = _districts.getLogicSize();
		int WinningPMPartyID, districtReps;
		const char* WinningPMName;
		double PartyvotesPrecentageInDistrict, totalPartyVotesPrecentage = 0;
		Party* tempParty;
		District* tempDistrict;
		int repsOfWinnerInDistrict;

		/*calc results*/
		for (int j = 0; j <= partiesAmount; j++) {
			tempParty = _parties.findPartyByID(j);
			for (int i = 0; i < districtsAmount; i++) {
				tempDistrict = _districts.findDistrictByID(j + 100);
				cout << "\n----------------------------------------------------";
				cout << "\nDistrict Name: " << tempDistrict->getName();
				cout << "\nAmount Of Reps: " << tempDistrict->getNumOfReps();
				partyVotesInDistrict = votesResults.getDistrictNumberOfVotesInParty(i + 100, j);
				cout << "\nThe District gave " << tempParty->getPartyName() << "  " << partyVotesInDistrict << " votes";
				PartyvotesPrecentageInDistrict = (partyVotesInDistrict / tempDistrict->getNumberOfCitizens()); //change to getNumberOfCitizensWhichVoted() to get precentage from votes and notfro m district
				cout << "\nwhich are: " << PartyvotesPrecentageInDistrict * 100 << "% precntages from the district citizens";
				totalPartyVotes = totalPartyVotes + partyVotesInDistrict;
				totalPartyVotesPrecentage = totalPartyVotesPrecentage + PartyvotesPrecentageInDistrict;
				AmountOfPartyMembersFromSingleDistrict = PartyvotesPrecentageInDistrict * (tempParty->getPartySize());
				totalPartyMembersForPM = totalPartyMembersForPM + AmountOfPartyMembersFromSingleDistrict;
				repsCounter.AddToPMRepsCount(i, j + 100, AmountOfPartyMembersFromSingleDistrict);
				votesResults.setPMsArrByIndex(j, AmountOfPartyMembersFromSingleDistrict);//toDelete
			}
			//todo: need to add function of printing partyMembers, and figure out the right order using repsCounter
			
			cout << "\nThe party got " << totalPartyVotes << "number of votes";
			cout << "\nwhich are " << totalPartyVotesPrecentage << "precentage of votes from all citizens";//watch commment before
			totalPartyVotesPrecentage = 0;
			totalPartyMembersForPM = 0;
			totalPartyVotes = 0;
		}


		cout << "\nThese are the stats of the PM candidates: ";

		for (int j = 0; j <= districtsAmount; j++) {
			WinningPMPartyID = checkWinningPMInDistrict(j, votesResults);
			repsOfWinnerInDistrict = checkWinnigPMRepsAmountInDistrict(repsCounter, j + 100);
			cout << "\nThe Party PM: " << _parties.findPartyByID(WinningPMPartyID)->getPartyLeader()); // idan new party Leader getter
			cout << " earned" << repsOfWinnerInDistrict << " members";
			cout << " His party got " << checkTotalPartyVotesAmount(votesResults, j) << " votes totally";
		}
	}
		
																							 

	int ElectionRound::checkWinningPMInDistrict(int districtID, resultsArr results) {
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

	int ElectionRound::checkWinnigPMRepsAmountInDistrict(resultsArr repsCountArr, int districtId) {// todelete
		int count = 0;
		for (int i = 0; i < _parties.getLogicSize(); i++) {
			count = count + repsCountArr.getPMNumberOfRepsInDistrict(i, districtId);
		}
		return count;
	}

	int ElectionRound::checkTotalPartyVotesAmount(resultsArr results, int partyID) {
		int count = 0;
		for (int i = 0; i < _parties.getLogicSize(); i++) {
			count = count + results.getDistrictNumberOfVotesInParty(i + 100, partyID);
		}
		return count;
	}


}
