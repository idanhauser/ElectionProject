#pragma once
#include "ElectionMain.h"
namespace elec
{
	class District;
	class Party;

	class Citizen
	{
	private:
		char* _citizen_name;
		int _id_num;
		int _birthDate[8];//TODO:not that i read again the matala 1 we need only birth year.. not the day and month lets change it like keren(basketball) need to change to _yearOfBirth yes?
		int _districtNum;
		District* _district;
		const Party* _party;

		Citizen(const Citizen/***/& other);///idan cahnged ->//TODO:we don't want the ability to duplicate a citizen
		const Citizen& operator=(const Citizen&);
	public:
		Citizen() = delete;
		Citizen(const char* citizen_name, int id_num, int birthDate[8], int districtNum);
		Citizen(const char* citizen_name, int id_num, int birthDate[8], int districtNum, const District& district, const Party* party);//TODO:Added after watching at keren vids, i think we should do it like this.

		~Citizen();
		friend ostream& operator<<(ostream& os, const Citizen& citizen);

		bool setCitizenName(const char* citizen_name);
		bool setBirthDate(const int* birthDate);
		bool setDistrict(const District& district);
		bool setParty(const Party* party);

		const char* getCitizenName() const;
		const int getCitizenID() const;
		const int* getCitizenBD() const;
		const int getCitizenDistrictNum() const;










	};


}