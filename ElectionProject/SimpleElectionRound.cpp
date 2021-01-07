//code verison 3.0
#include "SimpleElectionRound.h"

#include <fstream>

#include "DividedDistrict.h"

namespace elec
{
	SimpleElectionRound::SimpleElectionRound(LoadElectionSystem& loader):ElectionRound(loader)
	{
	}

	SimpleElectionRound::SimpleElectionRound(int date[DATE_SIZE], int numOfReps) :ElectionRound(date),_numOfReps(numOfReps)
	{
		DividedDistrict* dist = new DividedDistrict("Simple_Election_Round", _numOfReps,0);
		_districts.addToList(*dist);
	}

	int SimpleElectionRound::getNumOfReps() const
	{
		return _numOfReps;
	}

	bool SimpleElectionRound::addNewDistrict(const char str[MAX_SIZE], int numberRepresentatives, int& districtId,DistcritType districtType)
	{
		return false;
	}

	SimpleElectionRound::~SimpleElectionRound()
	{
		
	}


	void SimpleElectionRound::save(ofstream& outFile) const
	{
		int type = static_cast<int>(ElectionType::SimpleElectionRound);
		outFile.write(rcastcc(&type), sizeof(int));
		ElectionRound::save( outFile);
		outFile.close();
	}

	
}
