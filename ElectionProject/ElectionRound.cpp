//code verison 2.5
#include "ElectionRound.h"
#include <iostream>
#include <algorithm>
#include <fstream>

#include "Party.h"

#include "DistrictList.h"
#include "CitizenList.h"
#include "LoadElectionSystem.h"
#include "PartyList.h"
#include "UnifiedDistrict.h"
#include "DividedDistrict.h"
using namespace std;

namespace elec {
	ElectionRound::ElectionRound(int date[DATE_SIZE]) :_districts(), _parties(),
		_results(_parties.getLogicSize(), _districts.getLogicSize()), NoChangeSinceLastCalc(0)
	{


		for (int i = 0; i < DATE_SIZE; ++i)
		{
			this->_date[i] = date[i];
		}
	}

	ElectionRound::ElectionRound(LoadElectionSystem& loader) : _districts(), _parties(), _results(0, 0)
	{
		bool represntAdded;
		int numberOfparties;
		int numberOfdist;
		DistcritType type;
		ifstream& reader = loader.getReader();
		//Reading Date:
		reader.read(rcastc(_date), sizeof(int) * DATE_SIZE);
		//Read Dists:
			//reading number of dists:
		reader.read(rcastc(&numberOfdist), sizeof(int));

		for (int i = 0; i < numberOfdist; ++i)
		{
			District* dist;
			reader.read(rcastc(&type), sizeof(DistcritType));
			if(type==DistcritType::DividedDistrictType)
			{
				dist = new DividedDistrict(loader);
			}
			else
			{
				dist= new UnifiedDistrict(loader);
			}
			

			_districts.addToList(*dist);

		}

		//cout << "read dists" << endl;
		//Reading parties:
		//Read Dists:
			//reading number of parties:
		reader.read(rcastc(&numberOfparties), sizeof(int));
		for (int i = 0; i < numberOfparties; ++i)
		{
			int indexOfDist;
			int partyLeaderId;
			//reading partyLeaderId:
			reader.read(rcastc(&partyLeaderId), sizeof(int));
			if (_districts.isCitizenExist(partyLeaderId, indexOfDist)) {
				Party* party = new Party(loader, _districts.getDistcritByIndex(indexOfDist).getCitizenById(partyLeaderId), numberOfdist);
				_parties.addToList(*party);

			}
		}
	//	cout << "read parties done" << endl;

		//cout << "resultarr" << endl;
		//Reading _votesByIDs:
		_results= resultsArr(loader, numberOfparties, numberOfdist);


		//-------------------------------------------------------------------------
		// match between represent to a party. and party to a dist and citizen:
		//i - dist index; j - party index; t - citizen index.
		for (int i = 0; i < numberOfdist; ++i)
		{
			District& distTemp = _districts.getDistcritByIndex(i);
			int numOfCitizens = distTemp.getNumberOfCitizens();
			for (int t = 0; t < numOfCitizens; ++t)
			{
				Citizen& citizTemp = distTemp.getCitizenByIndex(t);
				if (citizTemp.GetPartyId() != -1)
				{
					Party& currParty = _parties.getPartyByIndex(citizTemp.GetPartyId() - PARTY_ID_INIT);
					represntAdded = currParty.addPartyMember(citizTemp, i);
					citizTemp.setParty(&currParty);
					if (!represntAdded)
					{
						cout << "Error:Couldn't finish the loading." << endl;
						return;
					}
				}
			}
		}
	}




	void ElectionRound::printElectionDate(ostream& os) const
	{
		for (int i = 0; i < DATE_SIZE; ++i)
		{
			os << static_cast<char>(_date[i] + '0');
			if (i == 1 || i == 3)
			{
				os << '/';
			}
		}
		os << endl;

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

	bool ElectionRound::addNewParty(const char* name, int pdId, int& partyId)
	{
		int distIndex;

		Citizen* leader = nullptr;
		bool partyAdded = false;
		if (_districts.isCitizenExist(pdId, distIndex))
		{
			leader = &(_districts.getDistcritByIndex(distIndex).getCitizenById(pdId));
			Party* par = new Party(name, pdId, _districts.getLogicSize(), *leader);
			partyId = par->getPartyID();
			leader->setParty(par);
			partyAdded = _parties.addToList(*par);
			_results.addParty();
			for (int j = 0; j < _districts.getLogicSize(); ++j)
			{
				_districts.getDistcritByIndex(j).updateRepsArr();
			}
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
				Party& currParty = _parties.getPartyByIndex(partyId);
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
			this->NoChangeSinceLastCalc = 1;
			for (int i = 0; i < len; i++)
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

		if (NoChangeSinceLastCalc)
			return true;
		this->NoChangeSinceLastCalc = 1;
		if (!isResultsAllowed())
			return false;
		int districtAmount = _districts.getLogicSize();
		int partiesAmount = _parties.getLogicSize();
		for (int j = 0; j < districtAmount; j++)
		{
			//todo roee: fix adding by the number of reps saved in  district repsArr, the parties representives
			/*for (int k = 0; k < partiesAmount; k++)
			{
				for (int k = 0; k < _districts.getDistcritByIndex(j)->getRepsByPartyID(k); k++)
				{
					_parties.getPartyByIndex(k).addToRepByDists(_parties.getPartyByIndex(k).getPartyMembers())
				}
			}*/
			_results.VotesToRepsInDistrictByDistrictID(_districts.getDistcritByIndex(j).getSerialNum(),
				_districts.getDistcritByIndex(j).getNumOfReps(), &(_districts.getDistcritByIndex(j)));

			if (typeid(_districts.getDistcritByIndex(j)) == typeid(UnifiedDistrict))
			{
				setWinnerInUnifiedDistrictByDistrictID(_districts.getDistcritByIndex(j).getSerialNum(), _districts.getDistcritByIndex(j).getNumOfReps());

			}
			else
			{
				// update divided district results to results arr
				for (int i = 0; i < partiesAmount; i++)
					_results.addToPmsRepsTotalByPartyID(i, _results.getDistrictNumberOfVotesInParty(i, j + DISTRICT_ID_INIT));

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
				tempDistrict.settVotersPrecentage(static_cast<double>(tempDistrict.getVotingCitizensAmountInDistrict() / tempDistrict.getNumberOfCitizens()) * 100);

				const double votingForPartyFromVotersInDistrictPrecentage = static_cast<double>(_results.getDistrictNumberOfVotesInParty(partyId - PARTY_ID_INIT, distIndex + DISTRICT_ID_INIT)) /
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
		this->NoChangeSinceLastCalc = 0;
		return isVotedCheck;
	}


	bool ElectionRound::theResults()
	{ // todo:roee fix - not sure if needed. we can just call from outside the if and "calcReps"
		if (!isResultsAllowed())
			return false;
		calcReps();

		return true;
	}

	ostream& operator<<(ostream& os, ElectionRound& electionRound) {

		if (!electionRound.isResultsAllowed())
		{
			os << "Sorry...Not enough details to get results" << endl;
			return os;
		}
		else
		{
			cout << "Election Round" << endl;
			electionRound.printElectionDate(os);
			//for (int i = 0; i < 3; i+=2) //todo: fix printing address instead of date when written as "os << electionRound._date << endl;"
			//	os << electionRound._date[i] << electionRound._date[i + 1] << "/";
			//os << electionRound._date[6] << electionRound._date[7];
			//os << endl;

			int districtAmount = electionRound._districts.getLogicSize();
			int partiesAmount = electionRound._parties.getLogicSize();
			for (int j = 0; j < districtAmount; j++)
			{

				//if (typeid(electionRound._districts.getDistcritByIndex(j)) == typeid(UnifiedDistrict))
				//{
				os << electionRound._districts.getDistcritByIndex(j) << endl;
				//}
				//else
				//	os << electionRound._districts.getDistcritByIndex(j) << endl;

				os << "each party got:" << endl;

				//print results:
				if (typeid(electionRound._districts.getDistcritByIndex(j)) == typeid(UnifiedDistrict))
				{
					for (int m = 0; m < partiesAmount; m++)
					{
						os << electionRound._parties.getPartyByIndex(m);
						os << electionRound._results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, m) << " Reps" << endl;
						//todo:roee fix::not printing party members cause they were never added
						electionRound._parties.getPartyByIndex(m).printPartyRepsFromDistrictByAmount(electionRound._results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, m), j + DISTRICT_ID_INIT);
						os << "Amount of Votes For The Party from Voting Citizens In The District: " <<
							electionRound._results.getDistrictNumberOfVotesInParty(m, j + DISTRICT_ID_INIT) << endl;
						os << "Precentage of votes For The Party from Voting Citizens In The District is: " <<
							electionRound._parties.getPartyByIndex(m).getVotingPercentagesByDistcritIdx(j) <<
							"%" << endl;

					}


					//todo:roee check
					os << "The district belongs to: " << electionRound._districts.getDistcritByIndex(j).getPartyLeader()->getCitizenName() << endl;
				}
				else
				{
					// = its a divided district - Only needed to present reps in max to min order
					for (int m = 0; m < partiesAmount; m++)
					{
						int* partyIndexesSotedByReps = new int[partiesAmount];
						for (int w = 0; w < districtAmount; w++)
						{
							electionRound.sortDistrictWinners(w + DISTRICT_ID_INIT, partyIndexesSotedByReps);
						}
						os << electionRound._parties.getPartyByIndex(partyIndexesSotedByReps[m]) << endl;
						os << electionRound._results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, partyIndexesSotedByReps[m]) << " Reps" << endl;
						//todo:roee fix::not printing party members cause they were never added
						electionRound._parties.getPartyByIndex(partyIndexesSotedByReps[m]).
							printPartyRepsFromDistrictByAmount(electionRound._results.getPMNumberOfRepsInDistrict(j + DISTRICT_ID_INIT, partyIndexesSotedByReps[m]), j + DISTRICT_ID_INIT);
						os << "Amount of Votes For The Party from Voting Citizens In The District: " <<
							electionRound._results.getDistrictNumberOfVotesInParty(partyIndexesSotedByReps[m], j + DISTRICT_ID_INIT) << endl;
						os << "Precentage of votes For The Party from Voting Citizens In The District is: " <<
							electionRound._parties.getPartyByIndex(partyIndexesSotedByReps[m]).getVotingPercentagesByDistcritIdx(j) << "%" << endl;

					}//no need to check for winner, printing sorted is enough
				}

			}

			//elections winner
			int* partiesIndexs = new int[partiesAmount];
			electionRound.checkElectionsWinner(partiesIndexs);
			for (int p = 0; p < partiesAmount; p++)
			{

				os << electionRound._parties.getPartyByIndex(partiesIndexs[p]).getPartyLeader().getCitizenName()
					<< " got " << electionRound._results.getPmsRepsTotalByPartyID(partiesIndexs[p]) << " reps ";
				os << "his party got total amount of " << electionRound._results.getTotalPartyNumberOfVotes(partiesIndexs[p]) << " votes" << endl;

			}
			delete[] partiesIndexs;
			return os;


		}

	}

	void ElectionRound::save(ofstream& outFile) const
	{
		//cout << "saving ElectionRound" << endl;
		int numOfParties;
		int numOfDists;
		DistcritType type;
		//Saving Date:
		outFile.write(rcastcc(_date), sizeof(int) * DATE_SIZE);
		// the number of dists:		
		numOfDists = _districts.getLogicSize();
		//number of dists:
		outFile.write(rcastcc(&numOfDists), sizeof(int));
		//saving the districts:
		//cout << "saving districts" << endl;
		for (int i = 0; i < numOfDists; ++i)
		{
			const District& distTemp = _districts.getDistcritByIndex(i);
			if (typeid(distTemp) == typeid(UnifiedDistrict))
			{
				type = DistcritType::UnifiedDistrict;
			}
			else
			{
				type = DistcritType::DividedDistrictType;
			}
			outFile.write(rcastcc(&type), sizeof(DistcritType));
			distTemp.save(outFile);
		}
	//	cout << "saving parties" << endl;
		// the number of parties:
		numOfParties = _parties.getLogicSize();
		//Saving number of parties:
		outFile.write(rcastcc(&numOfParties), sizeof(int));
		//Saving the parties:
		for (int i = 0; i < numOfParties; ++i)
		{
			//saving the partyLeadr id of party[i].
			int partyLeaderId = _parties.getPartyByIndex(i).getPartyPMCandidateID();
			outFile.write(rcastcc(&partyLeaderId), sizeof(int));
			_parties.getPartyByIndex(i).save(outFile);
		}
		//Saving resultArr:
		_results.save(outFile);

//		cout << "done" << endl;
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
				if (arr[j].repsAmount < arr[j + 1].repsAmount)
					swap(&arr[j], &arr[j + 1]);
			}
		}
	}







	bool ElectionRound::setWinnerInUnifiedDistrictByDistrictID(int districtID, int repsAmount) {
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
		_districts.getDistcritById(districtID).setLeader(&(_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader()));
		for (int i = 0; i < _parties.getLogicSize(); i++)
		{
			_districts.getDistcritById(districtID).setRepsArrByPartyID(i, 0);
		}
		_districts.getDistcritById(districtID).setRepsArrByPartyID(leaderWithMostRepsPartyID, _districts.getDistcritById(districtID).getNumOfReps());
		_results.addToPmsRepsTotalByPartyID(leaderWithMostRepsPartyID, repsAmount);


		return true;
	}



	bool ElectionRound::checkElectionsWinner(int* partiesIndexes) {
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

		for (int n = 0; n < _parties.getLogicSize(); n++)
		{
			totalRepsForPmByID[n].index = n;
			totalRepsForPmByID[n].repsAmount = _results.getPMNumberOfRepsInDistrict(districtID, n);
		}
		bubbleSort(totalRepsForPmByID, _parties.getLogicSize());

		for (int p = 0; p < _parties.getLogicSize(); p++)
		{
			partiesIndexes[p] = totalRepsForPmByID[p].index;

		}
		delete[] totalRepsForPmByID;
		return true;
	}


	bool ElectionRound::isResultsAllowed()const
	{
		if ((_parties.getLogicSize() != 0) && (_districts.getLogicSize() != 0))
			return true;
		else
			return false;
	}

}