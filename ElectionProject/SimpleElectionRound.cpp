//code verison 2.0
#include "SimpleElectionRound.h"
#include "DividedDistrict.h"

namespace elec
{

	SimpleElctionRound::SimpleElctionRound(int date[8],int numOfReps):ElectionRound(date)
	{
		DividedDistrict dist("Single", numOfReps);
		_districts.addToList(dist);
	}
}