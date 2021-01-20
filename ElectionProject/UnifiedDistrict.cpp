//code verison 3.2              
#include "UnifiedDistrict.h"
#include <iostream>
#include <algorithm>
#include "Utils.h"

namespace elec
{
	UnifiedDistrict::UnifiedDistrict(string& name, int numOfReps, int numOfParties) : District(name, numOfReps, numOfParties),
		_partyLeader(nullptr)
	{
	}

	UnifiedDistrict::UnifiedDistrict(LoadElectionSystem& loader):District(loader),_partyLeader(nullptr)
	{
	}

	UnifiedDistrict::~UnifiedDistrict()
	{

	}



	const Citizen* UnifiedDistrict::getPartyLeader() const
	{
		return _partyLeader;
	}

	bool UnifiedDistrict::setLeader(const Citizen* leader)
	{
		if (leader != nullptr)
		{
			_partyLeader = leader;
			return true;
		}
		return false;
	}


	void UnifiedDistrict::toOs(ostream& os) const
	{
		int repSize = _repsByPartyID.size();
		for (int i = 0; i < repSize; i++)
		{
			int repByParty = District::getRepsByPartyID(i + PARTY_ID_INIT);
			if (repByParty != 0)
			{
				os << "Only Party Id " << i << " Leader" << endl;
				os << "Gets all " << repByParty << " reps from the district." << endl;
				os << "The other party leaders get None" << endl;
			}
		}
	}



















}
