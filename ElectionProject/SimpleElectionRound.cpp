//code verison 3.0
#include "SimpleElectionRound.h"

#include <fstream>

#include "DividedDistrict.h"

namespace elec
{
	SimpleElectionRound::SimpleElectionRound(LoadElectionSystem& loader):ElectionRound(loader)
	{
	}

	SimpleElectionRound::SimpleElectionRound(int date_d, int date_m, int date_y, int numOfReps) noexcept(false) :ElectionRound(date_d, date_m, date_y),_numOfReps(numOfReps)
	{
		string name("simple_Election_Round");
		DividedDistrict* dist = new DividedDistrict(name ,_numOfReps,0);
		if(numOfReps<0)
		{
			throw numOfReps;
		}
		_districts.addToList(*dist);
		_results.addDistrict();
		_results.setDistrictsAmount();
	}

	int SimpleElectionRound::getNumOfReps() const
	{
		return _numOfReps;
	}

	bool SimpleElectionRound::addNewDistrict(string& name, int numberRepresentatives, int& districtId,DistcritType districtType)
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
