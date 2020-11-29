#pragma once
#include "ElectionMain.h"
namespace elec
{
	class Citizen
	{
	private:
		char* citizen_name;
		int id_num;
		int birthDate[8];
		int districtNum;

	public:
		Citizen() = delete;
		Citizen(const char* citizen_name, int id_num, int birthDate[8], int districtNum);
		Citizen(const Citizen& other);
		~Citizen();


		bool setCitizenName(const char* citizen_name);
		bool setBirthDate(const int* birthDate);


		const char* getCitizenName() const;
		const int getCitizenID() const;
		const int* getCitizenBD() const;
		const int getCitizenDistrictNum() const;









	};


}