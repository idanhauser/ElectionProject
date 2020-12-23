//code verison 2.0
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
		int _numOfDist;
		double* _VotingPercentagesDistrict;
		int _logicSize;
		int _phySize;

		void realloc(int new_size);
		Party(const Party& other);
		const Party& operator=(const Party&);

		bool AddAnotherColumn();
		bool addDistToArr();
		
		
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
		const CitizenList& getPartyMembers() const;
		CitizenList* getRepresentativesByDis() const;
		bool addPartyMember( Citizen& citizen,int distIndex);
		bool addToMembers( Citizen& citizen) ;

		bool updateParties();
		void printPartyRepsFromDistrictByAmount(int num, int districtID) const;
		bool addToRepresentativesByDis(Citizen& citizen, int distIndex) ;
		Citizen& getPartyLeader() const;
		double getVotingPercentagesByDistcritIdx(int index) const;
		void addVotingToPartyFromDistIdx(int index);

		
	};
}