//code verison 2.5
#include "DividedDistrict.h"
#include <iostream>

#include "Utils.h"


using namespace std;

namespace elec {

	DividedDistrict::DividedDistrict(const char* name, int numOfReps, int numOfParties) :District(name, numOfReps, numOfParties)
	{
	}

	DividedDistrict::DividedDistrict( LoadElectionSystem& loader):District(loader)
	{
		
	}

	DividedDistrict::~DividedDistrict()
	{

	}
	void DividedDistrict::toOs(ostream& os) const
	{
		int repSize = getRepsByPartyLogicSize();
		int reps;
		for (int i = 0; i < repSize; i++)
		{
			reps = getRepsByPartyID(i+ PARTY_ID_INIT);
			os << "The District Gives Party ID: " << i << endl;
			os << reps << " Reps." << endl;
		}
	}



	ostream& operator<<(ostream& os, const DividedDistrict& district)
	{
		os << "**********************************" << endl;
		os << "Divided Type District " << district.getName() << ", its ID is: " << static_cast<int>(district.
			getSerialNum()) << " has " << district.getNumberOfCitizens() << " citizens." << endl;
		os << "Number of representatives is : " << static_cast<double>(district.getNumOfReps()) << endl;
		os << "Precentage of voters: " << district.getVotersPrecentage() << "%" << endl;
		os << "**********************************" << endl;
		return os;
	}

}