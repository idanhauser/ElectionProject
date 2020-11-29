#include "Party.h"

namespace elec {

	int Party::pdGenerator;

	Party::Party(const char* partyName, int PMCandidateID) :
		_partyID(++pdGenerator), _partyName(new char[MAX_SIZE]), _PMCandidateID(PMCandidateID), _partyMembers(new Citizen* [MAX_SIZE]), phySizePartyMembers(MAX_SIZE), logicSizePartyMembers(0)
	{
		set_partyName(partyName);
	}

	///idan commented - do we want to duplicate a party?
	/*
	Party::Party(const Party& other) : _partyID(other._partyID), _PMCandidateID(other._PMCandidateID)
	{
		set_partyName(other._partyName);
		set_partyMembers(other._partyMembers, other.logicSizePartyMembers);
	}*/


	Party::~Party()
	{
		delete[] _partyName;
		delete[] _partyMembers;
	}


	bool Party::set_partyName(const char* partyName)
	{
		long namelen = strlen(partyName);
		this->_partyName = new char[namelen + 1];
		strncpy(this->_partyName, partyName, namelen);
		return true;
	}





	bool Party::set_partyMembers(Citizen** partyMembers, int size)
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

	Citizen** Party::getPartypartyMembers() const
	{
		return _partyMembers;
	}


	bool Party::addPartyMembers(Citizen* citizen)
	{
		if (logicSizePartyMembers == phySizePartyMembers)
		{
			_partyMembers = reallocCitizenArray(_partyMembers, phySizePartyMembers, phySizePartyMembers * 2);
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
		return true;
	}


}