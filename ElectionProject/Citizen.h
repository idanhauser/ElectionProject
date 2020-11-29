#pragma once
#include "ElectionMain.h"
namespace elec
{
	class Citizen
	{
	private:
		char* _citizen_name;
		int _id_num;
		int _birthDate[8];//TODO:not that i read again the matala 1 we need only birthyear.. not the day and month lets change it like keren(basketball)
		int _districtNum;

	public:
		Citizen() = delete;
		Citizen(const char* citizen_name, int id_num, int birthDate[8], int districtNum);
		Citizen(const Citizen/***/& other)=delete;///idan cahnged ->//we don't want the ability to duplicate a citizen
		~Citizen();


		bool setCitizenName(const char* citizen_name);
		bool setBirthDate(const int* birthDate);


		const char* getCitizenName() const;
		const int getCitizenID() const;
		const int* getCitizenBD() const;
		const int getCitizenDistrictNum() const;
		
		









	};


}