//code verison 3.0
#include "Party.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include "Citizen.h"
#include "CitizenList.h"


namespace elec {

	int Party::pdGenerator = PARTY_ID_INIT;


	Party::Party(const string& partyName, int PMCandidateID, int numOfDist, Citizen& partyLeader) : _partyID(pdGenerator++),
		_name(partyName),
		_PMCandidateID(PMCandidateID), _partyMembers(new CitizenList()), _representativesByDist(new CitizenList[numOfDist]),
		_partyLeader(partyLeader), _numOfDist(numOfDist),_VotingPercentagesDistrict(new double[MAX_SIZE]),_logicSize(0),_phySize(MAX_SIZE)
	{
		_partyMembers->addToList(partyLeader);
		for (int i = 0; i < numOfDist; i++)
		{
			_VotingPercentagesDistrict[i] = 0;
		}

	}

	Party::Party(LoadElectionSystem& loader, Citizen& partyLeader, int numOfDist): _partyMembers(new CitizenList()),
		_representativesByDist(new CitizenList[numOfDist]), _partyLeader(partyLeader)
	{
		ifstream& reader = loader.getReader();
		//Reading serial num of party _partyID:
		reader.read(rcastc(&_partyID), sizeof(int));
		pdGenerator = _partyID;
		//Reading name:
		reader.read(rcastc(&_name), sizeof(string));
		//Reading _PMCandidateID//
		reader.read(rcastc(&_PMCandidateID), sizeof(int));
		//Reading _numOfDist
		reader.read(rcastc(&_numOfDist), sizeof(int));
		//Reading _phySize
		reader.read(rcastc(&_phySize), sizeof(int));
		_VotingPercentagesDistrict = new double[_phySize];
		//Reading _logicSize
		reader.read(rcastc(&_logicSize), sizeof(int));
		//Reading double arr:
		for (int i = 0; i < _logicSize; ++i)
		{
			reader.read(rcastc(&_VotingPercentagesDistrict[i]), sizeof(double));
		}
	}
	Party::~Party()
	{
		delete[] _VotingPercentagesDistrict;
	}


	bool Party::setPMCandidateID(int idNum) {
		_PMCandidateID = idNum;
		return true;
	}

	const int Party::getPartyID() const
	{
		return _partyID;
	}

	bool Party::addToRepByDists(CitizenList& reps, int district)
	{
		_representativesByDist[district] = reps;
		return true;
	}

	const string Party::getPartyName() const
	{
		return _name;
	}

	int Party::getPartyPMCandidateID() const
	{
		return _PMCandidateID;
	}

	const CitizenList& Party::getPartyMembers() const
	{

		return *_partyMembers;
	}

	bool Party::addToMembers(Citizen& citizen) 
	{
		return _partyMembers->addToList(citizen);
	}

	bool Party::AddAnotherColumn()
	{
		CitizenList* new_memory = new CitizenList[_numOfDist ];
		for (int i = 0; i < min(_numOfDist , _numOfDist); ++i)
		{
			new_memory[i] = (_representativesByDist[i]);
		}
		_representativesByDist = new_memory;

		return true;
	}

	bool Party::addDistToArr()
	{
		if (_logicSize == _phySize)
		{
			realloc(_phySize * 2);

		}
		_VotingPercentagesDistrict[_numOfDist] = 0;
		_logicSize++;
		return true;
	}

	bool Party::updateDistricts()
	{
		_numOfDist++;
		return AddAnotherColumn() && addDistToArr();
	}


	string Party::printPartyRepsFromDistrictByAmount(int num, int districtID) const
	{
		string output;
		CitizenList& represnts = _representativesByDist[abs(districtID - DISTRICT_ID_INIT)];
		int amountToPrint = min(num, represnts.getLogicSize());
		if(amountToPrint==0)
		{
			output.append("\n The are no any representatives.(user didn't add any representatives). \n");
		}
		else
		{
			cout << "And they are:" << endl;
			for (int i = 0; i < amountToPrint; ++i)
			{
				cout << (represnts.getCitizenByIndex(i)).getCitizenName() << endl;
			}
		}
		output += "**********************************\n";
		return output;
	}


	bool Party::addToRepresentativesByDis(Citizen& citizen, int distIndex) 
	{
		return  _representativesByDist[distIndex].addToList(citizen);
	}

	Citizen& Party::getPartyLeader() const
	{
		return _partyLeader;
	}

	double Party::getVotingPercentagesByDistcritIdx(int index) const
	{
		return _VotingPercentagesDistrict[index];
	}



	void Party::save(ofstream& outFile) const
	{

		//save serialNumOfParty:
		outFile.write(rcastcc(&_partyID), sizeof(int));
		//saving name
		outFile.write(rcastcc(&_name), sizeof(string));
		//saving _PMCandidateID
		outFile.write(rcastcc(&_PMCandidateID), sizeof(int));
		//saving _numOfDist
		outFile.write(rcastcc(&_numOfDist), sizeof(int));
		//saving _phySize
		outFile.write(rcastcc(&_phySize), sizeof(int));
		//saving _logicSize
		outFile.write(rcastcc(&_numOfDist), sizeof(int));
		//saving double arr:
		for (int i = 0; i < _numOfDist; ++i)
		{
			outFile.write(rcastcc(&_VotingPercentagesDistrict[i]), sizeof(double));
		}

		
		
	}

	CitizenList* Party::getRepresentativesByDis() const
	{
		return _representativesByDist;
	}

	/// <summary>
	/// adding a citizen as a party member, adds to the party member list and to the
	/// Representatives list By the district they represnt.
	/// </summary>
	/// <param name="citizen">the citizen we want to add to the lists</param>
	/// <param name="distIndex">the district he represnt</param>
	/// <returns>true if everything is ok else false </returns>
	bool Party::addPartyMember( Citizen& citizen, int distIndex)
	{
		bool addtodis = false, addtomembers = false;
		addtodis = addToRepresentativesByDis(citizen, distIndex);
		addtomembers = addToMembers(citizen);
		return addtomembers && addtodis;
	}

	void Party::realloc(int new_size)
	{
		double* new_memory = new double[new_size];

		for (int i = 0; i < min(new_size, _phySize); ++i)
		{
			new_memory[i] = _VotingPercentagesDistrict[i];
		}
		if (_logicSize >= 1)
		{
			delete[] _VotingPercentagesDistrict;
		}

		_phySize = new_size;
		_VotingPercentagesDistrict = new_memory;
	}

	bool  Party::setVotingPercentagesDistrict(double num, int districtID)
	{
		_VotingPercentagesDistrict[districtID - DISTRICT_ID_INIT] = num;
		return true;
	}



	ostream& operator<<(ostream& os, const Party& party)
	{
		os << "**********************************" << endl;
		os << party._name << ","<< static_cast<int>(party._partyID) << endl<<"The party leader candidate name and ID is " << party.getPartyLeader().getCitizenName() << ", " <<
			static_cast<int>(party.getPartyPMCandidateID()) << "." << endl << "Party members are:" << endl;
		int sizeOfPartyMemberList = party.getPartyMembers().getLogicSize();
		if (sizeOfPartyMemberList > 1)
		{
			for (int i = 1; i < sizeOfPartyMemberList; ++i)
			{
				os << party.getPartyMembers().getCitizenByIndex(i).getCitizenName() << endl;
			}
		}
		else
		{
			os << "There are no any party member in this party." << endl;
		}
		os << "**********************************" << endl;
		return os;
	}
}
