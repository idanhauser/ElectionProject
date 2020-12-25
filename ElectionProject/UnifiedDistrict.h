//code verison 2.0
#pragma once

#include "District.h"

namespace elec
{


	class UnifiedDistrict :public District
	{
		const Citizen* _partyLeader;
	public:
		UnifiedDistrict(char* name, int numOfReps);

		Citizen* getPartyLeader() const;
		bool setLeader(const Citizen* leader);

		~UnifiedDistrict() override;
	};

}
