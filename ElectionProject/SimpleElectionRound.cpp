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
		int dist8;
		string name("simple_Election_Round");
		ElectionRound::addNewDistrict(name, _numOfReps, dist8, DistcritType::DividedDistrictType);
		DividedDistrict* dist = new DividedDistrict(name ,_numOfReps,0);
		if(numOfReps<0)
		{
			throw invalid_argument("Number of representatives cant be zero or negative.");
		}

		_districts.addToList(*dist);
		_results.addDistrict();
		_results.setDistrictsAmount();
	}

	int SimpleElectionRound::getNumOfReps() const
	{
		return _numOfReps;
	}

	void SimpleElectionRound::addNewDistrict(string& name, int numberRepresentatives, int& districtId,DistcritType districtType)
	{
		
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
