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
		int _birthYear;//TODO:not that i read again the matala 1 we need only birth year.. not the day and month lets change it like keren(basketball) need to change to _yearOfBirth yes? //roee: done
		int _districtNum;
		const Party* _party;
		//const District& _district; - //roee: We can have only the number, but check the only problem it makes at setDistrictNum func

	//	Citizen(const Citizen/***/& other);///idan cahnged ->//TODO:we don't want the ability to duplicate a citizen
		
	public:
		Citizen() = delete;
//		Citizen(const char* citizen_name, int id_num, int birthDate[8], int districtNum);
		Citizen(const char* citizen_name, int id_num, int birthYear, int _districtNum
			/*,const District &district*/ ,const Party* party);//TODO:Added after watching at keren vids, i think we should do it like this.
		
		~Citizen();

	
		bool setCitizenName(const char* citizen_name);
		bool setCitizenID(int idnum);
		bool setBirthYear(const int birthYear);
		bool setDistrictNum(int DistrictNum);
		bool setParty(const Party* party);
		
		const char* getCitizenName() const;
		const int getCitizenID() const;
		int getCitizenBY() const;
		const int getCitizenDistrictNum() const;
		
		








	};


}