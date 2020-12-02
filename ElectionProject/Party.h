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
		
	public:
		Party() = delete;
		Party(const char* partyName, int _PMCandidateID);
		//Party(const Party& other);//=delete;//TODO:idan changed we dont want the ability to duplicate a praty?
		//roee: canceled it
		~Party();


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