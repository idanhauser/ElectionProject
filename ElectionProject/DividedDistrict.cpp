//code verison 2.0
#include "DividedDistrict.h"
#include <iostream>


using namespace std;

namespace elec {

	DividedDistrict::DividedDistrict(const char* name, int numOfReps) :District(name, numOfReps), _numOfRepsForParty(nullptr)
	{
	}

	DividedDistrict::~DividedDistrict()
	{
		delete[] _numOfRepsForParty;
	}

	ostream& operator<<(ostream& os, const DividedDistrict& district)
	{
		os << "District " << district.getName() << ", its ID is: " << (int)district.getSerialNum() << " has " << district.getNumberOfCitizens() << " citizens." << endl;
		os << "Number of representatives is : " << (double)district.getNumOfReps() << endl;
		os << "Precentage of voters: " << district.getVotersPrecentage() << "%" << endl;
		//TODO to check if the next commented line is needed
		/*<< "and the election's result is " <<(int)district._electionResult << "." << endl;*/
		for (int i = 0; i < district.getRepsByPartyLogicSizeLogicSize(); i++)
		{
			os << "The District Gives Party ID: " << i << " , " <<
				district.getRepsByPartyID(i) << "Reps." << endl;
		}
		return os;
	}

}