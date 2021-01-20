//code verison 3.2
#pragma once
#include "Utils.h"
#include <algorithm>
#include <string>
using namespace std;
namespace elec
{
	class LoadElectionSystem;
	class District;
	class Party;

	class Citizen
	{
	private:
		string _name;
		int _idNum;
		int _birthYear;
		bool _hasVoted;
		const Party* _party;
		int _partyId;
		const District& _district;
		
		Citizen(const Citizen& other);
		const Citizen& operator=(const Citizen&);

	public:
		Citizen() = delete;
	
		 Citizen(LoadElectionSystem& loader, const District& district);
		Citizen(const string& cs, int id, int birth_year, const Party* party, const District& district);


		~Citizen();
		friend District;
		friend ostream& operator<<(ostream& os, const Citizen& citizen);

		/// <summary>
		/// set the party for citizen who is also a repsentive.
		/// </summary>
		/// <param name="party">pointer to the party</param>
		/// <returns>true for check</returns>
		void setParty(const Party* party) noexcept(false);
		/// <summary>
		/// sets if the citizen has voted.
		/// </summary>
		/// <param name="voted">true if he voted else false</param>
		/// <returns></returns>
		bool setHasVoted(bool voted);


		const string getCitizenName() const;
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