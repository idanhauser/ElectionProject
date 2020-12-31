//code verison 2.5
#pragma once
#include "CitizenList.h"
using namespace std;
#include <string>


namespace elec
{
	class LoadElectionSystem;
	class CitizenList;
	class Citizen;

	class District
	{
	protected:
		static int snGenerator;
		int _serialNum;
		char* _name;
		CitizenList _Citizens;
		double _votersPercentage;
		int* _repsByPartyID;//todo: check
		int _numOfParties;
		int _repsByPartyLogicSize;
		int _repsByPartyPhySize;
		int _numOfReps;
		int _electionResult;//todo:idan- can be deleted
		int _numberOfVotesinDist;
		District(const District& other);


	public:
		District(LoadElectionSystem& loader);
		District() = delete;///we delete default constructor
		District(const char* name, int numOfReps, int numOfParties);
		virtual ~District();
		virtual void toOs(ostream& os) const = 0;
		friend ostream& operator<<(ostream& os, const District& district);

		virtual const Citizen* getPartyLeader() const { return nullptr; }
		virtual bool setLeader(const Citizen* leader) { return false; }

		//Idan:
		Citizen& getCitizenByIndex(int idx);

		virtual const CitizenList& getEligibleCitizens() const;
		virtual const char* getName() const;
		const double getVotersPrecentage() const;


		CitizenList getElectionResults()const;
		int getSerialNum() const;
		int getNumberOfCitizens() const;
		bool addCitizen(Citizen* citz);
		bool addrepToArr();
		const Citizen& getCitizenById(int id) const;
		Citizen& getCitizenById(int id);
		int getNumOfReps() const;
		bool settVotersPrecentage(const int num);
		bool isCitizenExist(int id) const;
		int getVotingCitizensAmountInDistrict() const;
		void operator++(int);
		void realloc(int new_size);
		int getRepsByPartyLogicSize() const;
		bool setRepsArrByPartyID(int partyID, int repsAmount);
		int getRepsByPartyID(int partyID) const;
		bool updateRepsArr();
		bool AddAnotherColumn();
		bool addDistToArr();
		/// <summary>
		/// saving the citizens in the list
		/// </summary>
		/// <param name="outFile">the file we want to write to</param>
		void save(ofstream& outFile) const;

	};
}