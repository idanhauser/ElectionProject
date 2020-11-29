#include "Citizen.h"
using namespace elec;


Citizen::Citizen(const char* citizen_name, int id_num, int birthDate[8], int districtNum) :
	_citizen_name(new char[MAX_SIZE])
{
	setCitizenName(citizen_name);
	this->_id_num = id_num;
	for (int i = 0; i < 8; i++) {
		this->_birthDate[i] = birthDate[i];
	}
	this->_districtNum = districtNum;
}

//idan commented -> do we want to duplicate a citizen?
/*Citizen::Citizen(const Citizen& other)
{
	setCitizenName(other._citizen_name);
	this->_id_num = other._id_num;
	setBirthDate(other._birthDate);
	this->_districtNum = other._districtNum;
}*/

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




