//code verison 1.0
using namespace std;
#include "Party.h"
#include "PartyList.h"
namespace elec {


	PartyList::PartyList() : _logicSize(0), _phySize(MAX_SIZE), _parties(new Party* [MAX_SIZE]) {}

	PartyList::~PartyList()
	{
		for (int i = 0; i < _phySize; i++)
		{
			delete _parties[i];
		}
		delete[] _parties;
	}

	PartyList::PartyList(const PartyList& other) :_logicSize(other._logicSize), _phySize(other._phySize), _parties(new Party*[other._phySize])
	{
		int len = other.getLogicSize();
		for (int i = 0; i < len; ++i)
		{
			_parties[i] = other._parties[i];
		}
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


	bool PartyList::addToList(Party* Party)
	{
		if (_logicSize == _phySize)
		{
			realloc(_phySize * 2);

		}
		_parties[_logicSize++] = Party;
		return true;
	}



	int PartyList::getLogicSize() const
	{
		return _logicSize;
	}

	ostream& operator<<(ostream& os, const PartyList& party)
	{
		int len = party.getLogicSize();
		for (int i = 0; i < len; i++)
		{
			os << party._parties[i] << endl;
		}
		return os;
	}
}
