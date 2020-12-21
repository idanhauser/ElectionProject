//code verison 2.0
#include "Party.h"

#include "Citizen.h"
#include "CitizenList.h"
#include "Citizen.h"

namespace elec {

	int Party::pdGenerator = PARTY_ID_INIT;


	Party::Party(const char* partyName, int PMCandidateID, int numOfDist, Citizen& partyLeader) : _partyID(pdGenerator++),
		_partyName(new char[strlen(partyName) + 1]),
		_PMCandidateID(PMCandidateID), _partyMembers(new CitizenList()), _representativesByDist(new CitizenList[numOfDist]),
		_partyLeader(partyLeader), _numOfDist(numOfDist)
	{

		strcpy(this->_partyName, partyName);

	}

	Party::~Party()
	{
		delete[] _partyName;

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

	bool Party::addToMembers(Citizen& citizen)
	{
		return _partyMembers->addToList(citizen);
	}

	bool Party::AddAnotherColumn()
	{
		CitizenList* new_memory = new CitizenList[_numOfDist + 1];
		for (int i = 0; i < min(_numOfDist + 1, _numOfDist); ++i)
		{
			new_memory[i] = (_representativesByDist[i]);
		}
		_representativesByDist = new_memory;
		_numOfDist++;
		return true;
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

	CitizenList* Party::getRepresentativesByDis()
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
	bool Party::addPartyMember(Citizen& citizen, int distIndex)
	{
		bool addtodis = false, addtomembers = false;
		addtodis = addToRepresentativesByDis(citizen, distIndex);
		addtomembers = addToMembers(citizen);
		return addtomembers && addtodis;
	}
	
	//roee
	/*CitizenList Party::getPartyMembers()const
	{
		return _partyMembers;
	}*/


	ostream& operator<<(ostream& os, const Party& party)
	{
		os << party._partyName << ", it's is id :" << (int)party._partyID << "  the PM Candidate ID is " << (int)party.
			_PMCandidateID << endl;
		return os;
	}
}
