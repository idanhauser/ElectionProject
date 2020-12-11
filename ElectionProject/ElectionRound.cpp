
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
		Citizen* partyLeader;
		int totalDistrictVotes = 0, partyLeaderReps, maxRepsForPm = 0, totalPartyVotesPrecentage, partyVotesInDistrict, totalPartyVotes = 0;
		int districtAmount = countReps.getdistrictsAmount(), partiesAmount = countReps.getpartiesAmount();

		for (int j = 0; j <= districtAmount; j++) {
			tempDis = _districts.findDistrictByID(j + 100);
			cout << "\n----------------------------------------------------";
			//לכל מחוז יש לההציג את שם המחוז
			cout << "\nDistrict Name: " << tempDis->getName();
			//מספר הנציגים שהמחוז מעניק
			cout << "\nAmount Of Reps: " << tempDis->getNumOfReps();
			for (int k = 0; k < partiesAmount; k++) {
				partyVotesInDistrict = votesResults.getDistrictNumberOfVotesInParty(j + 100, k);
				totalPartyVotesPrecentage = partyVotesInDistrict / tempDis->getNumberOfCitizens() * 100;//from all citizens - not only voting ones
				cout << "\nThe party " << _parties.findPartyByID(k) << " got " << partyVotesInDistrict << " votes" << //delete after fix of the next comment
					"\nwhich are " << totalPartyVotesPrecentage << "precentage of votes from all citizens";

				/*todo: allow these lines after adding "getVotingCitizensAmountInDistrict()" func:
				//מספר ואחוז הקולות שקיבלה כל מפלגה
				totalPartyVotesPrecentage = partyVotesInDistrict / tempDis->getVotingCitizensAmountInDistrict() * 100;
				cout << "\nThe party " << _parties.findPartyByID(k) << " got " << partyVotesInDistrict << " votes"<<
					"\nwhich are " << partyVotesInDistrict/getVotingCitizensAmountInDistrict()*100 <<
					"precentages of voting citizens in the district";

				*/

				partyLeaderReps = partyVotesInDistrict / tempDis->getNumberOfCitizens() * (tempDis->getNumOfReps());
				//update: explanation: setElectionResult member in party k district j.
				//  implementation:                    
				//_parties.findPartyByID(k).findDistrictByID(j).setElectionResult(partyLeaderReps)
				
				/*todo: allow these lines after adding "printPartyRepsFromDistrictByAmount()" func:
				//להציג לכל מחוז את רשימת הנציגים שנבחרה מכל מפלגה
				findPartyByID(k).printPartyRepsFromDistrictByAmount(partyLeaderReps, districtID)

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
			//אחוז ההצבעה במחוז
			cout << "The precentage of voting citizens in the District is: " <<
				tempDis.getVotingCitizensAmountInDistrict()/tempDis->getEligibleCitizens() * 100;

				*/


				//district winner check:
				//מועמד המפלגה אליה המחוז משויך

			cout << "the Pm party with the most reps is: " << partyLeader->getCitizenName() << " who get all " <<
				tempDis->getNumOfReps() << " reps ";

			countReps.setPmsRepsByPartyID(partyLeader->getParty()->getPartyID());
			maxRepsForPm = 0;
			/*todo: allow this line after adding "setLeader(Citizen)" func:

			tempDis.setLeader(partyLeader);

			*/
		}
		
		/***************************************************************************************/
		//pmCandidatesRepsArrSorted[] sort:
		struct pair {
			int index;
			int repsAmount;
		};
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
		
		for (int i = 0; i < partiesAmount; i++) {
	//להציג עבור כל מפלגה את המועמד שלה לראשות המדינה, סכום הנציגים שזכה בהם וסכום הקולות שקיבלה המפלגה בכל המחוזות
			for (int l = 0; l < partiesAmount; l++)
				totalPartyVotes = totalPartyVotes + votesResults.getDistrictNumberOfVotesInParty(l + 100, i);
			cout << _citizens.findCitizenByID(_parties.findPartyByID(pmCandidatesRepsArrSorted[i].index)->getPartyPMCandidateID())->getCitizenName() << //todo: fix finding partyLeader ID
				" got total amount of " << countReps.getPmsRepsByPartyID(pmCandidatesRepsArrSorted[i].index) << " reps " <<
				"\nhis party got total amount of" << totalPartyVotes << " votes";
		}
		cout << "the ELECTIONS WINNER is: " << _citizens.findCitizenByID(_parties.findPartyByID(pmCandidatesRepsArrSorted[0].index)->getPartyPMCandidateID())->getCitizenName()
			<< "with" << countReps.getPmsRepsByPartyID(pmCandidatesRepsArrSorted[0].repsAmount) << "electors";

		delete[] pmCandidatesRepsArrSorted;

		
	}

	






}
