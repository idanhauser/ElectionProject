//code verison 2.0
#include "SimpleElectionRound.h"
#include "DividedDistrict.h"

namespace elec
{
	SimpleElectionRound::SimpleElectionRound(int date[DATE_SIZE], int num_of_rep) :ElectionRound(date),_numOfReps(num_of_rep)
	{
		DividedDistrict* dist = new DividedDistrict("singleDist", _numOfReps);
		_districts.addToList(*dist);
		_results.addDistrict();
		_results.setdistrictsAmount();
	}

	int SimpleElectionRound::getNumOfReps() const
	{
		return _numOfReps;
	}

	bool SimpleElectionRound::addNewDistrict(const char str[MAX_SIZE], int numbeRepresentatives, int& districtId)
	{
		return false;
	}

	SimpleElectionRound::~SimpleElectionRound()
	{
	}
}
