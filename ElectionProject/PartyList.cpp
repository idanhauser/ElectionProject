//code verison 3.1
using namespace std;
#include "Party.h"
#include "PartyList.h"
namespace elec {


	PartyList::PartyList() :  _parties(0) {}

	PartyList::~PartyList()
	{
	}



	bool PartyList::addToList(Party *Party)
	{
		_parties.push_back(Party);
		return true;
	}


	int PartyList::getLogicSize() const
	{
		return _parties.size();
	}

	const Party& PartyList::getPartyByIndex(int index) const
	{
		if (index < _parties.size())
			return *_parties[index];
	}

	 Party& PartyList::getPartyByIndex(int index) 
	{
		if (index < _parties.size())
			return *_parties[index];
	}

}
