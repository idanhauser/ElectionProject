#include "RegularElectionRound.h"
#include "LoadElectionSystem.h"
#include <fstream>


#include "DividedDistrict.h"
#include "UnifiedDistrict.h"

namespace elec
{

	RegularElectionRound::RegularElectionRound(LoadElectionSystem& loader):ElectionRound(loader)
	{

	}

	RegularElectionRound::RegularElectionRound(int date[MAX_SIZE]) : ElectionRound(date)
	{
	}




	bool RegularElectionRound::addNewDistrict(const char name[MAX_SIZE], int numberRepresentatives, int& districtId, DistcritType districtType)
	{
		bool districtAdded;
		if (districtType == DistcritType::UnifiedDistrict)
		{
			UnifiedDistrict* dist = new UnifiedDistrict(name, numberRepresentatives, _parties.getLogicSize());
			districtId = static_cast<UnifiedDistrict*>(dist)->getSerialNum();
			districtAdded = _districts.addToList(*dist);
		}

		else
		{
			DividedDistrict* dist = new DividedDistrict(name,  numberRepresentatives, _parties.getLogicSize());

			districtId = static_cast<DividedDistrict*>(dist)->getSerialNum();
			districtAdded = _districts.addToList(*dist);
		}
		for (int i = 0; i < _parties.getLogicSize(); ++i)
		{
			_parties.getPartyByIndex(i).updateDistricts();
		}
		_results.addDistrict(_districts.getLogicSize());

		return districtAdded;


		
	}

	RegularElectionRound::~RegularElectionRound()
	{
	}

	void RegularElectionRound::save(ofstream& outFile) const
	{
		int type= static_cast<int>(ElectionType::RegularElectionRound);
		outFile.write(rcastcc(&type), sizeof(int));
		ElectionRound::save(outFile);
	}
}
