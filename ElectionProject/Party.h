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
		CitizenList *_partyMembers;
		CitizenList* _representativesByDist;
		Citizen& _partyLeader;
		Party(const Party& other);
		const Party& operator=(const Party&);
		int _numOfDist;
	public:
		Party() = delete;
		Party(const char* partyName, int PMCandidateID, int numOfDist,Citizen& partyLeader);

		~Party();
		friend ostream& operator<<(ostream& os, const Party& party);
		friend class PartyList;
	
		bool setPMCandidateID(int idnum);

		bool addPartyMembers(Citizen* citizen);



		const char* getPartyName() const;
		const int getPartyID() const;
		int getPartyPMCandidateID() const;
		CitizenList getPartyMembers() const;
		CitizenList* getRepresentativesByDis();
		bool addPartyMember(Citizen& citizen,int distIndex);
		bool addToMembers( Citizen& citizen) ;
		bool AddAnotherColumn();
		void printPartyRepsFromDistrictByAmount(int num, int districtID) const;
		bool addToRepresentativesByDis(Citizen& citizen, int distIndex);
		Citizen& getPartyLeader() const;


		///ROEEE TODO = what are those functions?
	
	//CitizenList getPartyMembers()const; todo roee
		
		
	};
}