#include "Citizen.h"
#include "District.h"
#include "Party.h"

namespace elec
{
	//roee original cto'r
	Citizen::Citizen(const char* citizen_name, int id_num, int birthDate[8], int districtNum) :
		_citizen_name(new char[MAX_SIZE])
	{
		setCitizenName(citizen_name);
		this->_id_num = id_num;
		for (int i = 0; i < 8; i++) {
			this->_birthDate[i] = birthDate[i];
		}
		this->_districtNum = districtNum;
		_district = nullptr;
		_party = nullptr;
	}

	//idan TODO -> do we want to duplicate a citizen?

	Citizen::Citizen(const Citizen& other)
	{
		setCitizenName(other._citizen_name);
		this->_id_num = other._id_num;
		setBirthDate(other._birthDate);
		this->_districtNum = other._districtNum;
	}
	//idan added ctor TODO: need to talk with roee
	Citizen::Citizen(const char* citizen_name, int id_num, int birthDate[8], int districtNum, const District& district,
		const Party* party) : _citizen_name(new char[strlen(citizen_name + 1)]), _id_num(id_num), _districtNum(districtNum),
		_party(party)
	{
		setCitizenName(citizen_name);
		this->_id_num = id_num;
		for (int i = 0; i < 8; i++) {
			this->_birthDate[i] = birthDate[i];
		}
		this->_districtNum = districtNum;
		_district = new District(district);

	}

	Citizen::~Citizen()
	{
		delete[] _birthDate;
		delete[] _citizen_name;
	}


	bool Citizen::setCitizenName(const char* citizen_name) {
		int namelen = strlen(citizen_name);
		this->_citizen_name = new char[namelen + 1];
		strncpy(this->_citizen_name, citizen_name, namelen);
		return true;
	}

	bool Citizen::setBirthDate(const int* birthDate)
	{
		for (int i = 0; i < 8; i++)
		{
			this->_birthDate[i] = birthDate[i];
		}
		return true;
	}

	bool Citizen::setDistrict(const District& district)
	{
		_district = new District(district);
		return true;
	}

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


	const int* Citizen::getCitizenBD() const
	{
		return _birthDate;

	}

	const int Citizen::getCitizenDistrictNum() const
	{
		return _districtNum;

	}

	ostream& operator<<(ostream& os, const Citizen& citizen)
	{
		os << citizen._citizen_name << ", his id :" << (int)citizen._id_num << " and his year birth : " << (int)citizen._birthDate << endl;
		return os;
	}
}


