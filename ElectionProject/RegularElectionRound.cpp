#include "RegularElectionRound.h"
#include "LoadElectionSystem.h"
#include <fstream>


#include "DividedDistrict.h"
#include "UnifiedDistrict.h"

namespace elec
{

	RegularElectionRound::RegularElectionRound(LoadElectionSystem& loader) :ElectionRound(loader)
	{

	}

	RegularElectionRound::RegularElectionRound(int date_d, int date_m, int date_y) : ElectionRound(date_d, date_m, date_y)
	{
	}




	void RegularElectionRound::addNewDistrict(string& name, int numberRepresentatives, int& districtId, DistcritType districtType)
	{
		ElectionRound::addNewDistrict(name, numberRepresentatives, districtId, districtType);
		bool districtAdded;
		if (districtType == DistcritType::UnifiedDistrict)
		{
			UnifiedDistrict* dist = new UnifiedDistrict(name, numberRepresentatives, _parties.getLogicSize());
			districtId = static_cast<UnifiedDistrict*>(dist)->getSerialNum();
			 _districts.push_back(dist);
		}

		else
		{
			DividedDistrict* dist = new DividedDistrict(name, numberRepresentatives, _parties.getLogicSize());

			districtId = static_cast<DividedDistrict*>(dist)->getSerialNum();
			_districts.push_back(dist);
		}
		for (int i = 0; i < _parties.getLogicSize(); ++i)
		{
			_parties.getPartyByIndex(i).updateDistricts();
		}
		_results.addDistrict(_districts.getLogicSize());

		//return districtAdded;



	}

	RegularElectionRound::~RegularElectionRound()
	{
	}

	void RegularElectionRound::save(ofstream& outFile) const
	{
		int type = static_cast<int>(ElectionType::RegularElectionRound);
		outFile.write(rcastcc(&type), sizeof(int));
		ElectionRound::save(outFile);
	}
}
