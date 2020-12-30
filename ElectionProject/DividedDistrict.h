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
		virtual ~DividedDistrict();
		virtual void toOs(ostream& os) const override;
		//friend ostream& operator<<(ostream& os, const DividedDistrict& district);

		virtual const char* getName() const override;



	};

}