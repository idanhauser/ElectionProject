//code verison 3.1
#include "SimpleElectionRound.h"

#include <fstream>

#include "DividedDistrict.h"

namespace elec
{
	SimpleElectionRound::SimpleElectionRound(LoadElectionSystem& loader) :ElectionRound(loader)
	{
	}

	SimpleElectionRound::SimpleElectionRound(int date_d, int date_m, int date_y, int numOfReps) noexcept(false) :ElectionRound(date_d, date_m, date_y), _numOfReps(numOfReps)
	{
		int dist8;
		string name("simple_Election_Round");
		ElectionRound::addNewDistrict(name, _numOfReps, dist8, DistcritType::DividedDistrictType);
		DividedDistrict* dist = new DividedDistrict(name, _numOfReps, 0);
		if (numOfReps < 0)
		{
			throw invalid_argument("Number of representatives cant be zero or negative.");
		}
		_districts.push_back(dist);
	}

	int SimpleElectionRound::getNumOfReps() const
	{
		return _numOfReps;
	}

	void SimpleElectionRound::addNewDistrict(string& name, int numberRepresentatives, int& districtId, DistcritType districtType)
	{

	}

	SimpleElectionRound::~SimpleElectionRound()
	{

	}


	void SimpleElectionRound::save(ofstream& outFile) const
	{
		int type = static_cast<int>(ElectionType::SimpleElectionRound);
		outFile.write(rcastcc(&type), sizeof(int));
		ElectionRound::save(outFile);
		outFile.close();
	}


}
