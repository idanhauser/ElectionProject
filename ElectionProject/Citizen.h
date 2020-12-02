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
		int _birthYear;
		int _districtNum;
		const Party* _party;
		const District& _district;  //roee: We can have only the number, but check the only problem it makes at setDistrictNum func//TODO:so what? the this memeber is for us, the id of district is for the user

		Citizen(const Citizen& other);///idan cahnged ->//TODO:we don't want the ability to duplicate a citizen
		const Citizen& operator=(const Citizen&);
	public:
		Citizen() = delete;

		
		Citizen(const char* citizen_name, int id_num, int birthYear, int districtNum, const Party* party,
		        const District& district);

		~Citizen();

	
		bool setCitizenName(const char* citizenName);
		bool setCitizenID(int idNum);
		bool setBirthYear(const int birthYear);
		//bool setDistrictNum(int districtNum);Idan citizen can't change a district
		bool setParty(const Party* party);

		const char* getCitizenName() const;
		const int getCitizenID() const;
		int getCitizenBirthYear() const;
		const int getCitizenDistrictNum() const;










	};


}