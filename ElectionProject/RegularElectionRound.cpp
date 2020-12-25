#include "RegularElectionRound.h"

namespace elec
{
	RegularElectionRound::RegularElectionRound(int date[MAX_SIZE]) : ElectionRound(date)
	{
	}

	bool RegularElectionRound::addNewDistrict(const char name[MAX_SIZE], int numberRepresentatives, int& districtId)
	{
		bool districtAdded = false;
		District* dist = new District(name, numberRepresentatives);
		districtId = dist->getSerialNum();
		districtAdded = _districts.addToList(*dist);
		for (int i = 0; i < _parties.getLogicSize(); ++i)
		{
			_parties.getPartyByIndex(i).updateParties();
		}
		_results.addDistrict();
		_results.setdistrictsAmount();
		return districtAdded;
	}

	RegularElectionRound::~RegularElectionRound()
	{
	}
}
