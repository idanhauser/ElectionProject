#include "RegularElectionRound.h"
#include "LoadElectionSystem.h"
#include <fstream>

namespace elec
{

	RegularElectionRound::RegularElectionRound(LoadElectionSystem& loader):ElectionRound(loader)
	{

	}

	RegularElectionRound::RegularElectionRound(int date[MAX_SIZE]) : ElectionRound(date)
	{
	}




	bool RegularElectionRound::addNewDistrict(const char name[MAX_SIZE], int numberRepresentatives, int& districtId)
	{
		bool districtAdded = false;
		District* dist = new District(name, numberRepresentatives);
		districtId = dist->getSerialNum();
		districtAdded = _districts.addToList(*dist);
		int numberOfparties = _parties.getLogicSize();
		for (int i = 0; i < numberOfparties; ++i)
		{
			_parties.getPartyByIndex(i).updateParties();
		}
		_results.addDistrict();
		_results.setdistrictsAmount();
		return districtAdded;
	}

	RegularElectionRound::~RegularElectionRound()
	{
	}

	void RegularElectionRound::save(ofstream& outFile) const
	{

		cout << "saving RegularElectionRound" << endl;
		int type= static_cast<int>(ElectionType::RegularElectionRound);
		outFile.write(rcastcc(&type), sizeof(int));
		ElectionRound::save(outFile);
	}
}
