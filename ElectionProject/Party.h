#pragma once
#include "ElectionMain.h"
namespace elec
{
	class Citizen;

	class Party
	{
	private:
		static int pdGenerator;
		
		int _partyID; //should be made automatic using contsructor
		char* _partyName;
		int _PMCandidateID;
		Citizen** _partyMembers;
		
		int phySizePartyMembers;
		int logicSizePartyMembers;

	public:
		Party() = delete;
		Party(const char* partyName, int _PMCandidateID);
		Party(const Party& other)=delete;//idan changed we dont want the ability to duplicate a praty?
		~Party();


		bool set_partyName(const char* partyName);
		bool set_partyMembers(Citizen** partyMembers, int size);

		const char* getPartyName() const;
		const int getPartyID() const; 
		int getPartyPMCandidateID() const;
		Citizen** getPartypartyMembers() const;

		bool addPartyMembers(Citizen* citizen);




	};

}