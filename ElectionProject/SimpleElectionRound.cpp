//code verison 2.0
#include "SimpleElectionRound.h"
#include "DividedDistrict.h"

namespace elec
{

	SimpleElctionRound::SimpleElctionRound(int date[8],int numOfReps):ElectionRound(date)
	{
		DividedDistrict* dist = new DividedDistrict ("Single", numOfReps, _parties.getLogicSize());
		_districts.addToList(*dist);
	}
}