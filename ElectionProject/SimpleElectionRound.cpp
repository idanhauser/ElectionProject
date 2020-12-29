//code verison 2.0
#include "SimpleElectionRound.h"

#include <fstream>

#include "DividedDistrict.h"

namespace elec
{
	SimpleElectionRound::SimpleElectionRound(LoadElectionSystem& loader):ElectionRound(loader)
	{
	}

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


	void SimpleElectionRound::save(ofstream& outFile) const
	{
	/*	ofstream outFile(fileName, ios::binary | ios::trunc);

		if (!outFile) {
			cout << "error outfile" << endl;
			exit(-1);
		}*/
		//first saving type of election.
		int type = static_cast<int>(ElectionType::SimpleElectionRound);
		outFile.write(rcastcc(&type), sizeof(int));
		ElectionRound::save( outFile);
		outFile.close();
	}

	
}
