#include "Citizen.h"
#include "District.h"
#include "Party.h"

namespace elec
{
	//roee original cto'r
/*	Citizen::Citizen(const char* citizen_name, int id_num, int birthDate[4], int districtNum) :
		_citizen_name(new char[MAX_SIZE])
	{
		setCitizenName(citizen_name);
		this->_id_num = id_num;
		for (int i = 0; i < 4; i++) {
			this->_birthDate[i] = birthDate[i];
		}
		this->_districtNum = districtNum;
		_district = nullptr;
		_party = nullptr;
	}
	*/


	Citizen::Citizen(const char* citizen_name, int id_num, int birthYear, int districtNum, const Party* party, const District& district) : _citizen_name(new char[strlen(citizen_name + 1)]), _id_num(id_num), _birthYear(0), _party(nullptr), _districtNum(districtNum), _district(district)
	{
		setCitizenName(citizen_name);

		//	this->_id_num = id_num;               //roee: I moved them all to the func name line
		//  this->_districtNum = districtNum;
		//	_district = new District(district);

	}


	//idan TODO -> do we want to duplicate a citizen? //roee: Canceled it
/*	Citizen::Citizen(const Citizen& other): _district(other._district)
	{
		setCitizenName(other._citizen_name);
		this->_id_num = other._id_num;
		setBirthDate(other._birthDate);
		//this->_districtNum = other._districtNum;
	}
	//idan added ctor TODO: need to talk with roee
	*/




	Citizen::~Citizen()
	{
		delete[] _citizen_name;
	}


	bool Citizen::setCitizenName(const char* citizen_name) {
		int namelen = strlen(citizen_name);
		this->_citizen_name = new char[namelen + 1];
		strncpy(this->_citizen_name, citizen_name, namelen);
		return true;
	}


	bool Citizen::setCitizenID(int idnum) {
		_id_num = idnum;
		return true;
	}

	bool Citizen::setBirthYear(const int birthYear)
	{
		if (birthYear >= 2002 && birthYear <= 1900)
			return false;
		else
		{
			_birthYear = birthYear;
			return true;
		}
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

	const char* Citizen::getCitizenName() const
	{
		return _citizen_name;

	}

	const int Citizen::getCitizenID() const
	{
		return _id_num;

	}


	int Citizen::getCitizenBY() const
	{
		return _birthYear;

	}

	const int Citizen::getCitizenDistrictNum() const
	{
		return _districtNum;

	}

}


