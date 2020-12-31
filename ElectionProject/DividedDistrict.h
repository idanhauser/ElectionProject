//code verison 2.5
#pragma once
#include "District.h"
using namespace std;

namespace elec
{
	class DividedDistrict : public District
	{
	public:
		DividedDistrict(const char* name, int numOfReps, int numOfParties);
		DividedDistrict( LoadElectionSystem& loader);
		virtual ~DividedDistrict();
		virtual void toOs(ostream& os) const override;




	};

}