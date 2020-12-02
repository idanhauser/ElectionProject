#pragma once
#include "ElectionMain.h"
#include "List.h"

namespace elec
{
	class List;
	class Citizen;
	class Party
	{
	private:
		static int pdGenerator;
		
		int _partyID; 
		char* _partyName;
		int _PMCandidateID;
		List _partyMembers;
		
		Party(const Party& other);
		const Party& operator=(const Party&);
	public:
		Party() = delete;
		Party(const char* partyName, int _PMCandidateID);

		~Party();
		friend ostream& operator<<(ostream& os, const Party& party);

		bool set_partyName(const char* partyName);
		bool setPMCandidateID(int idnum);

		bool addPartyMembers(Citizen* citizen); //roee: Should it get few partyMembers?

		// bool set_party(/*Citizen** partyMembers, int size*/); //roee: no need - does the same as constructor


		const char* getPartyName() const;
		const int getPartyID() const; 
		int getPartyPMCandidateID() const;
		List getPartyMembers() const;





	};

}