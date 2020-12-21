//code verison 2.0
#pragma once
#include "District.h"
using namespace std;

namespace elec
{
	class DividedDistrict : public District
	{
		int* _numOfRepsForParty;
	public:
		DividedDistrict(const char* name, int numOfReps);
		~DividedDistrict();

	};

}