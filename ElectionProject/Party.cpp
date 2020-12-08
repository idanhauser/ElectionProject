//code verison 1.0
#include "Party.h"
#include "CitizenList.h"


namespace elec {

	int Party::pdGenerator = PARTY_ID_INIT;
	//_partyMembers() //roee: matala says u add a party using the pmCandidate. should we initiate it with citizens in it? does it auto initiates?
//todo:idan->	Citizen* PMCandidate = findCitizenByID(PMCandidateID); //roee: need to implement the func. where does the func belongs to?
//todo:idan->	addPartyMembers(PMCandidate); //roee: And whats the best way to find in the eligibleCitizens List the pmCandidate BY his ID?
		//TODO://_partyMembers.addToList() ->Idan: it should be something like that -> i will think about it
		//maybe Party will get a citizen in the paramters who's the prime minister?
	
	Party::Party(const char* partyName, int PMCandidateID, int numOfDist) : _partyID(pdGenerator++),
		_partyName(new char[strlen(partyName) + 1]),
		_PMCandidateID(PMCandidateID), _partyMembers(new CitizenList()), _representatives(new CitizenList[numOfDist])
	{
	/*	for (int i = 0; i < numOfDist; ++i)
		{
			*(_representatives[i].getCitizens()) = new CitizenList*();
		}
*/
		strcpy(this->_partyName, partyName);

	}

	///idan commented - do we want to duplicate a party?
	 //roee: CANCELED IT
	/*
	Party::Party(const Party& other) : _partyID(other._partyID), _PMCandidateID(other._PMCandidateID)
	{
		set_partyName(other._partyName);
		set_party(other._partyMembers, other.logicSizePartyMembers);
	}
	*/

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
	bool Party::addToRepresentativesBydis(Citizen& citizen, int distIndex)
	{
		 return  _representatives[distIndex].addToList(citizen);
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
		bool addtodis=false, addtomembers=false;
		addtodis = addToRepresentativesBydis(citizen, distIndex);
		addtomembers = addToMembers(citizen);
		return addtomembers && addtodis;
	}


	/*//todo:idan->
	List Party::getPartyMembers() const //roee: Im not sure if I should implement getter in List class or keep it that way
	{
		return _partyMembers;
	}*/



	//bool Party::addPartyMembers(Citizen* citizen) //roee: the name just covers the list func
	//{


	//	return _partyMembers.addToList(*citizen); //roee: was added instead of in each class
	//}


	ostream& operator<<(ostream& os, const Party& party)
	{
		os << party._partyName << ", it's is id :" << (int)party._partyID << "  the PM Candidate ID is " << (int)party.
			_PMCandidateID << endl;
		return os;
	}
}
