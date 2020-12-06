
#include "ElectionRound.h"

//code verison 1.0
#include <iostream>


#include "DistrictList.h"
#include "CitizenList.h"
#include "PartyList.h"
#include "resultsArr.h"

using namespace std;

namespace elec
{
	/*ElectionRound::ElectionRound(int date[8]):
	_citizens(CitizenList()),_districts(DistrictList()),_parties(PartyList())
	{

		for (int i = 0; i < 8; ++i)
		{
			this->_date[i] = date[i];
		}
	}
	*/




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
	void ElectionRound::votingAction(CitizenList _citizens)
	{

		int id, party_id;
		cout << "\nType your ID: ";
		cin >> id;
		cout << "\nEnter your voted party ID: ";
		cin >> party_id;
		Citizen* tempCitizen = _citizens.findCitizenByID(id);
		if (tempCitizen->hasVoted() == false) {
			tempCitizen->setHasVoted(true);
			resultsArr resultsArr;
			resultsArr.AddVoteToResultsArr(party_id, tempCitizen->getCitizenDistrictNum());
		}
		else
			cout << "\nYou've voted already !! ";
	}

	void ElectionRound::theResults() {
		resultsArr results;
		int votes;
		int totalWinningPMPartyVotes = 0;
		int AmountOfPartyMembersFromSingleDistrict;
		int partiesAmount = _parties.getLogicSize();
		int districtsAmount = _districts.getLogicSize();
		int WinningPartyID, districtReps;
		const char* WinningPMName;
		double PartyvotesPrecentage, totalVotesPrecentage;
		Party* tempParty;
		District* tempDistrict;
		for (int j = 0; j <= districtsAmount; j++) {
			tempDistrict = _districts.findDistrictByID(j+100);
			cout << "\nDistrict Name: " << tempDistrict->getName();
			cout <<"\nAmount Of Reps: "<< tempDistrict->getNumOfReps();
			tempDistrict = _districts.findDistrictByID(j + 100);
			totalVotesPrecentage = 0;
			for (int i = 0; i < partiesAmount; i++) {
				votes = results.getPartyNumberOfVotesFromDistrict(j + 100, i);
				tempParty = _parties.findPartyByID(i);
				cout << " the party " << tempParty->getPartyName() << " got " << votes;
				PartyvotesPrecentage = (votes / tempDistrict->getNumberOfCitizens());
				totalVotesPrecentage = totalVotesPrecentage + PartyvotesPrecentage;
				AmountOfPartyMembersFromSingleDistrict = PartyvotesPrecentage * (tempParty->getPartySize());
				cout << " which are " << PartyvotesPrecentage << "of all votes. \nHence, "
					<< AmountOfPartyMembersFromSingleDistrict << " party members are elected from the party ";
				for (int k = 0; k < AmountOfPartyMembersFromSingleDistrict; k++)
					tempDistrict->addToElectedMembersArr(tempParty->getPartyMembers().getCitizenByIndex(k));
				results.setPMsArrByIndex(i, AmountOfPartyMembersFromSingleDistrict);
			}
			WinningPartyID = checkWinnerInDistrict(j + 100, results);
			WinningPMName = _citizens.findCitizenByID(WinningPartyID)->getCitizenName();
			cout << "\nThe total votes precentage in the District is: " << totalVotesPrecentage;
			districtReps =tempDistrict->getNumOfReps();
			cout << "\nThe winning PM in this District is " << WinningPMName << "who's getting all " <<
				districtReps << " district reps";
			cout << "\nThe Reps Are: ";
			for (int l = 0; l < tempDistrict->getElectionResults().getLogicSize(); l++) {
				tempDistrict->getElectionResults().printList();
			}
			results.addToTotalPMsReps(WinningPartyID, districtReps);
		}
		int PMPartyID = checkWinnigPM(results.getTotalPMsRepsArr());
		cout <<"\nthe winner of the elections is: " << _citizens.findCitizenByID(PMPartyID) 
			<< "with total amount of " << totalWinningPMPartyVotes <<"votes for his party"; //todo
	}

	int ElectionRound::checkWinnigPM(int* TotalPMsRepsArr) {
		int winner=0;
		for (int i = 0; i < _parties.getLogicSize(); i++) {
			if (winner > TotalPMsRepsArr[i])
				winner = i;
		}
		return winner;
	}

	int ElectionRound::checkWinnerInDistrict(int districtID, resultsArr results) {
		int max = 0;
		int cur;
		int winnerID = 0;
		for (int j = 0; j < _parties.getLogicSize(); j++) {
			cur = results.getPartyNumberOfVotesFromDistrict(districtID + 100, j);
			if (max < cur) {
				max = cur;
				winnerID = j;
			}
		}
		return winnerID;
	}
}
