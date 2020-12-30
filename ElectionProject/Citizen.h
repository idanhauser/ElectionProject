//code verison 2.5
#pragma once
#include "Utils.h"
using namespace std;
namespace elec
{
	class LoadElectionSystem;
	class District;
	class Party;

	class Citizen
	{
	private:
		char* _name;
		int _idNum;
		int _birthYear;
		int _districtNum;
		bool _hasVoted;
		//if citizen is also represnt
		const Party* _party;
		int _partyId;
		//reference to an existing district 
		const District& _district;
		
		Citizen(const Citizen& other);
		const Citizen& operator=(const Citizen&);

	public:
		Citizen() = delete;
		Citizen(const char* citizen_name, int id_num, int birthYear, int districtNum, const Party* party,const District& district);
		 Citizen(LoadElectionSystem& loader, const District& district);


		~Citizen();

		friend ostream& operator<<(ostream& os, const Citizen& citizen);

		
		bool setParty(const Party* party);
		bool setHasVoted(bool voted);
		
		const char* getCitizenName() const;
		int getCitizenID() const;
		int getCitizenBirthYear() const;
		int getDistrictNum() const;
		int GetPartyId() const;
		bool hasVoted()const;
		const Party* getParty() const;
		const District& getDistrict() const;
		/// <summary>
		/// Save citizen into file
		/// </summary>
		/// <param name="outFile">the file we write to</param>
		void save(ofstream& outFile) const;
	};


}