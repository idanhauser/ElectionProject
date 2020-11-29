#include "Citizen.h"
using namespace elec;


Citizen::Citizen(const char* citizen_name, int id_num, int birthDate[8], int districtNum):
	citizen_name(new char[MAX_SIZE])
{
	setCitizenName(citizen_name);
	this->id_num = id_num;
	for (int i = 0; i < 8; i++) {
		this->birthDate[i] = birthDate[i];
	}
	this->districtNum = districtNum;
}


Citizen::Citizen(const Citizen& other)
{
	setCitizenName(other.citizen_name);
	this->id_num = other.id_num;
	setBirthDate(other.birthDate);
	this->districtNum = other.districtNum;
}

Citizen::~Citizen() 
{

}


bool Citizen::setCitizenName(const char* citizen_name) {
	long namelen = strlen(citizen_name);
	this->citizen_name = new char[namelen + 1];
	strncpy(this->citizen_name, citizen_name, namelen);
	return true;
}

bool Citizen::setBirthDate(const int* birthDate) {
	for (int i = 0; i < 8; i++) {
		this->birthDate[i] = birthDate[i];
	}
}

const char* Citizen::getCitizenName() const
{
	return citizen_name;

}

const int Citizen::getCitizenID() const
{
	return id_num;

}


const int* Citizen::getCitizenBD() const
{
	return birthDate;

}

const int Citizen::getCitizenDistrictNum() const
{
	return districtNum;

}




