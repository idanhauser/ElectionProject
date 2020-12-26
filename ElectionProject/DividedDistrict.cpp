//code verison 2.0
#include "DividedDistrict.h"



elec::DividedDistrict::DividedDistrict(const char* name, int numOfReps):District(name,numOfReps),_numOfRepsForParty(nullptr )
{
}

elec::DividedDistrict::~DividedDistrict()
{
	delete[] _numOfRepsForParty;
}


