//code verison 2.0
#pragma once
#include "Utils.h"
using namespace std;
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
		bool _hasVoted;
		const Party* _party;
		//reference to an existing district 
		const District& _district; //idan:copied from moshe, what de we want
		bool setDistrict(District& dist);
		
		Citizen(const Citizen& other);
		const Citizen& operator=(const Citizen&);

	public:
		Citizen() = delete;
		Citizen(const char* citizen_name, int id_num, int birthYear, int districtNum, const Party* party,const District& district);
		~Citizen();

		friend ostream& operator<<(ostream& os, const Citizen& citizen);
		//friend class CitizenList;
		
		bool setParty(const Party* party);
		bool setHasVoted(bool voted);
		
		const char* getCitizenName() const;
		const int getCitizenID() const;
		int getCitizenBirthYear() const;
		const int getDistrictNum() const;
	//	const char* getDistrictName() const;//Idan: why i dont succeed?
		bool hasVoted()const;
		const Party* getParty() const;
		const District& getDistrict() const;

	};


}