//code verison 2.0
#include "Party.h"
#include <algorithm>
#include "Citizen.h"
#include "CitizenList.h"


namespace elec {

	int Party::pdGenerator = PARTY_ID_INIT;


	Party::Party(const char* partyName, int PMCandidateID, int numOfDist, Citizen& partyLeader) : _partyID(pdGenerator++),
		_partyName(new char[strlen(partyName) + 1]),
		_PMCandidateID(PMCandidateID), _partyMembers(new CitizenList()), _representativesByDist(new CitizenList[numOfDist]),
		_partyLeader(partyLeader), _numOfDist(numOfDist),_VotingPercentagesDistrict(new double[MAX_SIZE]),_logicSize(0),_phySize(MAX_SIZE)
	{

		strcpy(this->_partyName, partyName);

	}

	Party::~Party()
	{
		delete[] _partyName;
		delete[] _VotingPercentagesDistrict;
	}


	bool Party::setPMCandidateID(int idnum) {
		_PMCandidateID = idnum;
		return true;
	}

	const int Party::getPartyID() const
	{
		return _partyID;
	}

	const char* Party::getPartyName() const
	{
		return _partyName;
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
		return true;
	}

	bool Party::updateParties()
	{
		_numOfDist++;
		return AddAnotherColumn() && addDistToArr();
	}


	void Party::printPartyRepsFromDistrictByAmount(int num, int districtID) const
	{
		CitizenList& represnts = _representativesByDist[abs(districtID - DISTRICT_ID_INIT)];
		int amountToPrint = min(num, represnts.getLogicSize());
		for (int i = 0; i < amountToPrint; ++i)
		{
			cout << (represnts.getCitizenByIndex(i)).getCitizenName() << endl;

		}
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

	void Party::addVotingToPartyFromDistIdx(int index)
	{
		_VotingPercentagesDistrict[index]++;
	}

	CitizenList* Party::getRepresentativesByDis() const
	{
		return _representativesByDist;
	}

	/// <summary>
	/// adding a citizen as a party memebr, adds to the party memeber list and to the
	/// Representatives list By the distcrit they represnt.
	/// </summary>
	/// <param name="citizen">the citizen we want to add to the lists</param>
	/// <param name="distIndex">the distcrit he represnt</param>
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

	bool  Party::getVotingPercentagesDistrict(int districtID)
	{
		return _VotingPercentagesDistrict[districtID - DISTRICT_ID_INIT];
	}


	ostream& operator<<(ostream& os, const Party& party)
	{
		os << party._partyName << ","<< (int)party._partyID << endl<<"The party leader candidate name and ID is " << party.getPartyLeader().getCitizenName() << ", " <<
			(int)party.getPartyPMCandidateID() << "." << endl << "Party members are:" << endl;
		for (int i = 0; i < party.getPartyMembers().getLogicSize(); ++i)
		{
			os << party.getPartyMembers().getCitizenByIndex(i).getCitizenName() << endl;
		}
		return os;
	}
}
