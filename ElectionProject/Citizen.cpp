//code verison 1.0
#include "Citizen.h"
#include "District.h"
#include "Party.h"

namespace elec
{


	Citizen::Citizen(const char* citizen_name, int id_num, int birthYear, int districtNum, const Party* party,
	                 const District& district) : _citizen_name(new char[strlen(citizen_name + 1)]), _id_num(id_num),
	                                             _birthYear(0), _districtNum(districtNum), _party(nullptr),
	                                             _district(district), _hasVoted(false)
	{
		strcpy(this->_citizen_name, citizen_name);
	}

	Citizen::~Citizen()
	{
		delete[] _citizen_name;
	}


		/* citizen can or can not change a district
		bool Citizen::setDistrictNum(int DistrictNum)
		{
			//	_district = new District(district);
			_districtNum = DistrictNum;
		//todo idan	District* district = findDistrictByNum(DistrictNum); //roee: The idea is to add the citizen to his district's eligible list after the user entered the number
		//todo idan	district.addEligibleCitizens(DistrictNum); //roee: we should implement. not sure in which class to implement both funcs.
			return true;                                     //for now I added  one func at district.h bottom
		}
		*/

	bool Citizen::setParty(const Party* party)
	{
		_party = party;
		return true;
	}

	bool Citizen::setHasVoted(bool voted)
	{
		_hasVoted = voted;
		return true;
	}

	const char* Citizen::getCitizenName() const
	{
		return _citizen_name;

	}

	const int Citizen::getCitizenID() const
	{
		return _id_num;

	}


	int Citizen::getCitizenBirthYear() const
	{
		return _birthYear;

	}

	const int Citizen::getCitizenDistrictNum() const
	{
		return _districtNum;

	}

	bool Citizen::hasVoted() const
	{
		return _hasVoted;
	}

	ostream& operator<<(ostream& os, const Citizen& citizen)
	{
		os << citizen._citizen_name << ", his id :" << (int)citizen._id_num << " and his year birth : " << (int)citizen._birthYear;
		if(citizen._hasVoted)
		{
			os << " and he voted this election round." << endl;
		}
		else
		{
			os << " and he didn't vote this election round." << endl;
		}
		return os;
	}
}


