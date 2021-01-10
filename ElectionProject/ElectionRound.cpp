//code verison 3.1
#include "ElectionRound.h"
#include <iostream>
#include <algorithm>
#include <fstream>

#include "Party.h"
#include "Exceptions.h"
#include "DistrictList.h"
#include "CitizenList.h"
#include "LoadElectionSystem.h"
#include "PartyList.h"
#include "UnifiedDistrict.h"
#include "DividedDistrict.h"
#include "DynamicArray.h"
using namespace std;

namespace elec {

	ElectionRound::ElectionRound(int date_d, int date_m, int date_y) noexcept(false) :
		_districts(), _parties(), _results(_parties.getLogicSize(), _districts.size()), NoChangeSinceLastCalc(0)
	{
		setDate(date_d, date_m, date_y);
	}

	ElectionRound::ElectionRound(LoadElectionSystem& loader) : _districts(), _parties(), _results(0, 0)
	{
		bool represntAdded;
		int numberOfparties;
		int numberOfdist;
		DistcritType type;
		ifstream& reader = loader.getReader();
		//Reading Date:
		//read date:
		reader.read(rcastc(&_dateDay), sizeof(int));
		//read month:
		reader.read(rcastc(&_dateMonth), sizeof(int));
		//read year:
		reader.read(rcastc(&_dateYear), sizeof(int));

		//Read Dists:
			//reading number of dists:
		reader.read(rcastc(&numberOfdist), sizeof(int));

		for (int i = 0; i < numberOfdist; ++i)
		{
			District* dist;
			reader.read(rcastc(&type), sizeof(DistcritType));
			if (type == DistcritType::DividedDistrictType)
			{
				dist = new DividedDistrict(loader);
			}
			else
			{
				dist = new UnifiedDistrict(loader);
			}


			_districts.push_back(dist);

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
			if (isCitizenExist(partyLeaderId, indexOfDist)) {
				Party* party = new Party(loader, _districts.at(indexOfDist)->getCitizenById(partyLeaderId), numberOfdist);
				_parties.addToList(*party);

			}
		}
		//	cout << "read parties done" << endl;

			//cout << "resultarr" << endl;
			//Reading _votesByIDs:
		_results = resultsArr(loader, numberOfparties, numberOfdist);

		string output;
		//-------------------------------------------------------------------------
		// match between represent to a party. and party to a dist and citizen:
		//i - dist index; j - party index; t - citizen index.
		for (auto i = _districts.begin(); i != _districts.end(); ++i)
		{
			int numOfCitizens = (*i)->getNumberOfCitizens();
			for (int t = 0; t < numOfCitizens; ++t)
			{
				Citizen& citizTemp = (*i)->getCitizenByIndex(t);
				try {
					if (citizTemp.GetPartyId() != -1)
					{

						Party& currParty = _parties.getPartyByIndex(citizTemp.GetPartyId() - PARTY_ID_INIT);
						currParty.addPartyMember(citizTemp, (*i)->getSerialNum() - DISTRICT_ID_INIT);
						citizTemp.setParty(&currParty);
					}
				}
				catch (const char& ex)
				{
					cout << ex << "for citizen id: " << (*i)->getSerialNum() << endl;
				}
			}
		}
	}

	void ElectionRound::addNewDistrict(string& name, int numbeRepresentatives, int& districtId,
		DistcritType districtType)
	{
		if ((name.find_first_not_of(' ') == std::string::npos) || name.find_first_of("0123456789") != std::string::npos)
		{
			throw invalid_argument("Invalid name: empty name or name contains digits.");
		}
		if (numbeRepresentatives < 0)
		{
			throw invalid_argument("Number of representatives cant be zero or negative.");
		}

	}


	void ElectionRound::printElectionDate(ostream& os) const
	{

		os << _dateDay << "." << _dateMonth << "." << _dateYear;
		os << endl;

	}
	void ElectionRound::setDate(int date_d, int date_m, int date_y) noexcept(false)
	{
		if (date_y <= 0)
		{
			throw YearException(date_y);
		}
		if (date_d < 1 || date_d>31)
		{
			throw DayException(date_d);
		}

		if (date_m < 1 || date_m>12)
		{
			throw MonthException(date_m);
		}
		const Months month = static_cast<Months>(date_m);
		if (month == Months::February)
		{
			if (date_d < 1 || date_d>28)
			{
				throw DayMonthException(date_d, date_m);
			}
		}
		else if ((month == Months::January) || (month == Months::March) || (month == Months::May) || (month ==
			Months::July) || (month == Months::August) || (month == Months::October) || (month == Months::December))
		{
			if (date_d < 1 || date_d>31)
			{
				throw DayMonthException(date_d, date_m);
			}
		}
		else
		{
			if (date_d < 1 || date_d>30)
			{
				throw DayMonthException(date_d, date_m);
			}
		}
		_dateDay = date_d;
		_dateYear = date_y;
		_dateMonth = date_m;
	}


	void ElectionRound::addNewCitizen(string& name, int id, int birthYear, int districtId) noexcept(false)
	{
		bool validData = true;
		int saveDis;
		bool citizenExist = true;



		if (!isCitizenExist(id, saveDis))
		{
			if (isDistcritExist(districtId))
			{
				Citizen* citiz = new Citizen(name, id, birthYear, districtId, nullptr, *_districts.at(districtId-DISTRICT_ID_INIT));
				_districts.at(districtId-DISTRICT_ID_INIT)->addCitizen(*citiz);//need to check if added susccessfuly.
			}
			else
			{
				throw DistcritsNotExistException(districtId);
			}
		}
		else
		{
			//citizen already exist.
			throw CitizenExistException(id, districtId);
		}

	}



	void ElectionRound::addNewParty(string& name, int pdId, int& partyId) noexcept(false)
	{
		int distIndex;

		Citizen* leader = nullptr;
		bool partyAdded = false;
		if (isCitizenExist(pdId, distIndex))
		{
			leader = &(_districts.at(distIndex)->getCitizenById(pdId));
			Party* par = new Party(name, pdId, _districts.size(), *leader);
			partyId = par->getPartyID();
			leader->setParty(par);
			partyAdded = _parties.addToList(*par);
			_results.addParty();
			for (auto j = _districts.begin(); j != _districts.end(); ++j)
			{
				(*j)->updateRepsArr();
			}
		}
		else
		{
			throw CitizenNotExistException(pdId);
		}
	}

	bool ElectionRound::addNewPartyRepresentative(int representId, int partyId, int districtId)
	{
		int distIndex;
		bool represntAdded = false;
		if (isCitizenExist(representId, distIndex))
		{
			Citizen& citizenReprenst = _districts.at(distIndex)->getCitizenById(representId);
			if (isDistcritExist(districtId) && _parties.IsPartyExist(partyId))
			{
				Party& currParty = _parties.getPartyByIndex(partyId);
				represntAdded = currParty.addPartyMember(citizenReprenst, abs(DISTRICT_ID_INIT - districtId));
				citizenReprenst.setParty(&currParty);
			}
		}
		return represntAdded;

	}


	bool ElectionRound::isDistcritExist(int id) const
	{
		bool found = false;
		for (auto i = _districts.begin(); i != _districts.end() && !found; ++i)
		{

			if ((*i)->getSerialNum() == id)
			{
				found = true;
			}
		}
		return found;
	}


	void ElectionRound::viewAllDistricts()  noexcept(false)
	{
		string output;
		int len = _districts.size();

		if (!_districts.empty())
		{
			calcReps();
			this->NoChangeSinceLastCalc = 1;
			for (auto i = _districts.begin(); i != _districts.end(); ++i)
			{
				cout << *(*i)<<endl;
			}

		}
		else
		{
			output.append("There are no districts to show.");
			throw output;
		}
	}



	bool ElectionRound::calcReps() {

		if (NoChangeSinceLastCalc)
			return true;
		this->NoChangeSinceLastCalc = 1;
		if (!isResultsAllowed())
			return false;

		int partiesAmount = _parties.getLogicSize();
		for (auto j = _districts.begin(); j != _districts.end(); ++j)
		{
			_results.VotesToRepsInDistrictByDistrictID((*j)->getSerialNum(),
				(*j)->getNumOfReps(), (*j));

			if (typeid((*j)) == typeid(UnifiedDistrict))
			{
				setWinnerInUnifiedDistrictByDistrictID((*j)->getSerialNum(), (*j)->getNumOfReps());

			}
			else
			{
				// update divided district results to results arr
				for (int i = 0; i < partiesAmount; i++)
					_results.addToPmsRepsTotalByPartyID(i, _results.getDistrictNumberOfVotesInParty(i, (*j)->getSerialNum()));

			}
		}
		return true;

	}

	void ElectionRound::viewAllCitizens() const noexcept(false)
	{
		if (!_districts.empty())
		{
			for (auto i = _districts.begin(); i !=_districts.end(); ++i)
			{
			
				if (!(*i)->getCitizens().empty())
					cout << "The citizens who live in " << (*i)->getName() << " are: " << endl;

				for (auto j = (*i)->getCitizens().begin(); j != (*i)->getCitizens().end(); ++j)
				{
					cout << *(*j) << endl;
				}

			}
		}
		else
		{
			const string msg = "There are no citizens to show.";
			throw msg;
		}
	}

	void ElectionRound::viewAllParties() const noexcept(false)
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
		if (isCitizenExist(citizenId, distIndex) && (_parties.IsPartyExist(partyId)))
		{
			District& tempDistrict = *_districts.at(distIndex);
			Citizen& tempCitizen = tempDistrict.getCitizenById(citizenId);
			if (tempCitizen.hasVoted() == false) {
				tempCitizen.setHasVoted(true);

				_results.AddSingleVoteToArr(partyId, tempCitizen.getDistrictNum());
				tempDistrict.setVotersPrecentage(static_cast<double>(tempDistrict.getVotingCitizensAmountInDistrict() / tempDistrict.getNumberOfCitizens()) * 100);

				const double votingForPartyFromVotersInDistrictPrecentage = static_cast<double>(_results.getDistrictNumberOfVotesInParty(partyId - PARTY_ID_INIT, distIndex + DISTRICT_ID_INIT)) /
					double(_districts.at(distIndex + DISTRICT_ID_INIT)->getVotingCitizensAmountInDistrict()) * 100;
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
	{
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
			int partiesAmount = electionRound._parties.getLogicSize();
			for (auto j = electionRound._districts.begin(); j !=electionRound._districts.end(); ++j)
			{

				os << (*j) << endl;
				os << "each party got:" << endl;

				//print results:
				if (typeid((*j)) == typeid(UnifiedDistrict))
				{
					for (int m = 0; m < partiesAmount; m++)
					{
						os << electionRound._parties.getPartyByIndex(m);
						os << "And the have ";
						os << electionRound._results.getPMNumberOfRepsInDistrict((*j)->getSerialNum(), m) << " representatives." << endl;
						os << electionRound._parties.getPartyByIndex(m).printPartyRepsFromDistrictByAmount(electionRound._results.getPMNumberOfRepsInDistrict((*j)->getSerialNum(), m), (*j)->getSerialNum());
						os << "Amount of Votes For The Party from Voting Citizens In The District: " <<
							electionRound._results.getDistrictNumberOfVotesInParty(m, (*j)->getSerialNum()) << endl;
						os << "Percentages of votes For The Party from Voting Citizens In The District is: " <<
							electionRound._parties.getPartyByIndex(m).getVotingPercentagesByDistcritIdx((*j)->getSerialNum()-DISTRICT_ID_INIT) <<
							"%" << endl;

					}
					os << endl;
					os << "The district belongs to: " << (*j)->getPartyLeader()->getCitizenName() << endl;
					os << endl;
				}
				else
				{
					// = its a divided district - Only needed to present reps in max to min order
					for (int m = 0; m < partiesAmount; m++)
					{
						int* partyIndexesSotedByReps = new int[partiesAmount];
						for (int w = 0; w < electionRound._districts.size(); w++)
						{
							electionRound.sortDistrictWinners(w + DISTRICT_ID_INIT, partyIndexesSotedByReps);
						}
						os << electionRound._parties.getPartyByIndex(partyIndexesSotedByReps[m]) << endl;
						os << electionRound._results.getPMNumberOfRepsInDistrict((*j)->getSerialNum(), partyIndexesSotedByReps[m]) << " Reps" << endl;
						electionRound._parties.getPartyByIndex(partyIndexesSotedByReps[m]).
							printPartyRepsFromDistrictByAmount(electionRound._results.getPMNumberOfRepsInDistrict((*j)->getSerialNum(), partyIndexesSotedByReps[m]), (*j)->getSerialNum());
						os << "Amount of Votes For The Party from Voting Citizens In The District: " <<
							electionRound._results.getDistrictNumberOfVotesInParty(partyIndexesSotedByReps[m], (*j)->getSerialNum()) << endl;
						os << "Precentage of votes For The Party from Voting Citizens In The District is: " <<
							electionRound._parties.getPartyByIndex(partyIndexesSotedByReps[m]).getVotingPercentagesByDistcritIdx((*j)->getSerialNum()-DISTRICT_ID_INIT) << "%" << endl;

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


	bool ElectionRound::isCitizenExist(int id, int& distIndex) const
	{
		distIndex = -1;

		bool found = false;
		for (auto i = _districts.begin(); i != _districts.end() && !found; ++i)
		{
			if ((*i)->isCitizenExist(id))
			{
				distIndex = (*i)->getSerialNum() - DISTRICT_ID_INIT;
				found = true;
			}
		}
		return found;
	}



	void ElectionRound::save(ofstream& outFile) const
	{
		//cout << "saving ElectionRound" << endl;
		int numOfParties;
		int numOfDists;
		DistcritType type;
		//Saving Date:
			//saving date:
		outFile.write(rcastcc(&_dateDay), sizeof(int));
		//saving month:
		outFile.write(rcastcc(&_dateMonth), sizeof(int));
		//saving year:
		outFile.write(rcastcc(&_dateYear), sizeof(int));
		// the number of dists:		
		numOfDists = _districts.size();
		//number of dists:
		outFile.write(rcastcc(&numOfDists), sizeof(int));
		//saving the districts:
		//cout << "saving districts" << endl;
		for (auto i = _districts.begin(); i != _districts.end(); ++i)
		{
			if (typeid((*i)) == typeid(UnifiedDistrict))
			{
				type = DistcritType::UnifiedDistrict;
			}
			else
			{
				type = DistcritType::DividedDistrictType;
			}
			outFile.write(rcastcc(&type), sizeof(DistcritType));
			(*i)->save(outFile);
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
		_districts.at(districtID-DISTRICT_ID_INIT)->setLeader(&(_parties.getPartyByIndex(leaderWithMostRepsPartyID).getPartyLeader()));
		for (int i = 0; i < _parties.getLogicSize(); i++)
		{
			_districts.at(districtID-DISTRICT_ID_INIT)->setRepsArrByPartyID(i, 0);
		}
		_districts.at(districtID - DISTRICT_ID_INIT)->setRepsArrByPartyID(
			leaderWithMostRepsPartyID, _districts.at(districtID - DISTRICT_ID_INIT)->getNumOfReps());
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
		if ((_parties.getLogicSize() != 0) && (!_districts.empty()))
			return true;
		else
			return false;
	}

}