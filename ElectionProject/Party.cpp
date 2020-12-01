#include "Party.h"
#include "List.h"
namespace elec {

	int Party::pdGenerator;

	Party::Party(const char* partyName, int PMCandidateID) :
		_partyID(++pdGenerator), _partyName(new char[MAX_SIZE]), _PMCandidateID(PMCandidateID) 
		//_partyMembers() //roee: matala says u add a party using the pmCandidate. should we initiate it with citizens in it? does it auto initiates?
	{
		Citizen* PMCandidate = findCitizenByID(PMCandidateID); //roee: need to implement the func. where does the func belongs to?
		addPartyMembers(PMCandidate); //roee: And whats the best way to find in the eligibleCitizens List the pmCandidate BY his ID?
		set_partyName(partyName);
	}

	///idan commented - do we want to duplicate a party?
	 //roee: CANCELED IT
	
	/*Party::Party(const Party& other) : _partyID(other._partyID), _PMCandidateID(other._PMCandidateID)
	{
		set_partyName(other._partyName);
		set_party(other._partyMembers, other.logicSizePartyMembers);
	}*/


	Party::~Party()
	{
		delete[] _partyName;
		_partyMembers.deleteList(); //roee: updated from del[] partymembers
	}


	bool Party::set_partyName(const char* partyName)
	{
		long namelen = strlen(partyName);
		this->_partyName = new char[namelen + 1];
		strncpy(this->_partyName, partyName, namelen);
		return true;
	}

	bool Party::setPMCandidateID(int idnum) {
		_PMCandidateID = idnum;
		return true;
	}

/*	bool Party::set_party(Citizen** partyMembers, int size) //roee: changed it - it does the same as list constructor
	{
		delete[] this->_partyMembers;
		phySizePartyMembers = size * 2;
		logicSizePartyMembers = size;
		this->_partyMembers = new Citizen * [phySizePartyMembers];
		for (int i = 0; i < size; ++i)
		{
			this->_partyMembers[i] = partyMembers[i];
		}
		return true;


	}*/

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

	List Party::getPartyMembers() const //roee: Im not sure if I should implement getter in List class or keep it that way
	{
		return _partyMembers;
	}

	///todo:need to be removed after roee divide builds the vectors...
	//Citizen** reallocCitizenArray(Citizen** citizen, int old_size, int new_size);
	
	bool Party::addPartyMembers(Citizen* citizen) //roee: the name just covers the list func
	{
		/*if (logicSizePartyMembers == phySizePartyMembers)
		{
			List::reallocCitizenArray(partyMembers, phySizePartyMembers, phySizePartyMembers * 2);
			phySizePartyMembers *= 2;
		}
		if (logicSizePartyMembers < phySizePartyMembers)
		{
			_partyMembers[logicSizePartyMembers++] = citizen;
		}
		else
		{
			//error
			return false;
		}
		return true;*/

		return _partyMembers.addListMember(citizen); //roee: was added instead of in each class
	}


}