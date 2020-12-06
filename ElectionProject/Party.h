//code verison 1.0
#pragma once
#include "Utils.h"
#include "CitizenList.h"

namespace elec
{
	class CitizenList;
	class Party
	{
	private:
		static int pdGenerator;
		
		int _partyID; 
		char* _partyName;
		int _PMCandidateID;
		CitizenList _partyMembers;
		
		Party(const Party& other);
		const Party& operator=(const Party&);
	public:
		Party() = delete;
		Party(const char* partyName, int PMCandidateID);

		~Party();
		friend ostream& operator<<(ostream& os, const Party& party);
		//friend class PartyList;
	
		bool setPMCandidateID(int idnum);

		bool addPartyMembers(Citizen* citizen);

		

		const char* getPartyName() const;
		const int getPartyID() const; 
		int getPartyPMCandidateID() const;
		CitizenList getPartyMembers() const;



	};

}