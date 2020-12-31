//code verison 2.5
#pragma once

#include "District.h"

namespace elec
{


	class UnifiedDistrict :public District
	{
		const Citizen* _partyLeader;
	public:
		UnifiedDistrict(const char* name, int numOfReps, int numOfParties);
		UnifiedDistrict( LoadElectionSystem& loader);
		virtual ~UnifiedDistrict() override;

		virtual const Citizen* getPartyLeader() const override ;
		virtual bool setLeader(const Citizen* leader) override;

		virtual void toOs(ostream& os) const override;

	
	
	};

}
