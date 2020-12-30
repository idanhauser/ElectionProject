//code verison 2.5
using namespace std;
#include "Party.h"
#include "PartyList.h"
namespace elec {


	PartyList::PartyList() : _logicSize(0), _phySize(MAX_SIZE), _parties(new Party* [MAX_SIZE]) {}

	PartyList::~PartyList()
	{
		for (int i = 0; i < _logicSize; i++)
		{
			delete _parties[i];
		}
		delete[] _parties;
	}

	void PartyList::realloc(int new_size)
	{
		Party** new_memory = new Party * [new_size];

		for (int i = 0; i < min(new_size, _phySize); ++i)
		{
			new_memory[i] = this->_parties[i];
		}
		if (_logicSize >= 1)
		{
			delete[] _parties;
		}

		_phySize = new_size;
		_parties = new_memory;
	}


	bool PartyList::addToList(Party& party)
	{
		if (_logicSize == _phySize)
		{
			realloc(_phySize * 2);

		}
		_parties[_logicSize++] = &party;
		return true;
	}



	int PartyList::getLogicSize() const
	{
		return _logicSize;
	}

	const Party& PartyList::getPartyByIndex(int index) const
	{
		if (index < _logicSize)
			return *_parties[index];
	}

	 Party& PartyList::getPartyByIndex(int index) 
	{
		if (index < _logicSize)
			return *_parties[index];
	}

	bool PartyList::IsPartyExist(int partyId) const
	{
		bool found = false;
		for (int i = 0; i < _logicSize && !found; ++i)
		{
			if (i == abs(partyId - PARTY_ID_INIT))
			{
				found = true;
			}
		}
		return found;
	}
}
