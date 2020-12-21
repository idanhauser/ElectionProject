﻿//code verison 2.0
#include "Citizen.h"

#include "Party.h"

namespace elec
{
	Citizen::Citizen(const char* citizen_name, int id_num, int birthYear, int districtNum, const Party* party,
		const District& district) : _citizen_name(new char[strlen(citizen_name)+1]), _id_num(id_num),
		_birthYear(birthYear), _districtNum(districtNum), _hasVoted(false),
		_party(nullptr), _district(district)
	{
		strcpy(this->_citizen_name, citizen_name);
	}

	Citizen::~Citizen()
	{
		delete[] _citizen_name;
	}


	

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

	const int Citizen::getDistrictNum() const
	{
		return _districtNum;

	}
	bool Citizen::hasVoted() const
	{
		return _hasVoted;
	}

	const Party* Citizen::getParty() const
	{
		return _party;
	}

	const District& Citizen::getDistrict() const
	{
		return _district;
	}
	ostream& operator<<(ostream& os, const Citizen& citizen)
	{
		os << citizen._citizen_name << ", his id :" << (int)citizen._id_num << " and his year birth : " << (int)citizen._birthYear << endl;
		if (citizen._hasVoted)
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


