//code verison 3.1
#pragma once
#include "Utils.h"
#include "CitizenList.h"
#include "LoadElectionSystem.h"
#include <string>
namespace elec
{
	class CitizenList;
	class Party
	{
	private:
		static int pdGenerator;

		int _partyID;
		string _name;
		int _PMCandidateID;
		vector<Citizen*>_partyMembers;
		vector<vector<Citizen*>> _representativesByDist;
		Citizen& _partyLeader;
		vector<double> _VotingPercentagesDistrict;

		Party(const Party& other);
		const Party& operator=(const Party&);

		
		
	public:
		Party() = delete;
		Party(const string& partyName, int PMCandidateID, int numOfDist,Citizen& partyLeader);
		Party( LoadElectionSystem& loader, Citizen& partyLeader,int numOfDist);

		~Party();
		friend ostream& operator<<(ostream& os, const Party& party);

		friend class PartyList;
	
		bool setPMCandidateID(int idNums);
		bool setVotingPercentagesDistrict(double num, int districtID);

		bool addToRepByDists(Citizen* reps, int district);

		const string getPartyName() const;
		const int getPartyID() const;
		int getPartyPMCandidateID() const;
		const vector<Citizen*> getPartyMembers() const;
		vector<vector<Citizen*>> getRepresentativesByDis() const;
		bool addPartyMember( Citizen& citizen,int distIndex);
		bool addToMembers(Citizen* citizen);

		bool updateDistricts();
		string printPartyRepsFromDistrictByAmount(int num, int districtID) const;
		bool addToRepresentativesByDis(Citizen& citizen, int distIndex) ;
		Citizen& getPartyLeader() const;
		double getVotingPercentagesByDistcritIdx(int index) const;
		/// <summary>
		/// this function saves file the class.
		/// </summary>
		/// <param name="outFile">the file we write to,</param>
		void save(ofstream& outFile) const;
		
	};
}
