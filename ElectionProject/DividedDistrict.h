//code verison 3.0
#pragma once
#include "District.h"
#include <string>
using namespace std;

namespace elec
{
	class DividedDistrict : public District
	{
	public:
		DividedDistrict(string& name, int numOfReps, int numOfParties);
		DividedDistrict(LoadElectionSystem& loader);
		virtual ~DividedDistrict();
		/// <summary>
		/// printing function of this class
		/// </summary>
		/// <param name="os">the file we print to.</param>
		virtual void toOs(ostream& os) const override;




	};

}