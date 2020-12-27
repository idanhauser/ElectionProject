//code verison 2.0
#pragma once
#include "CitizenList.h"
using namespace std;
#include <string>


namespace elec
{
	class CitizenList;
	class Citizen;

	class District
	{
	private:
		static int snGenerator;
		int _serialNum;
		char* _name;
		CitizenList _Citizens;
		double _votersPercentage;
		int* _repsByPartyID;//todo: check
		int _repsByPartyLogicSize;
		int _repsByPartyPhySize;
		int _numOfReps;

		int _numberOfVotesinDist;
		District(const District& other);
		const District& operator=(const District&);

	public:
	
		District() = delete;///we delete default constructor
		District(const char* name, int numOfReps);
		~District();
		friend ostream& operator<<(ostream& os, const District& district);
		//friend class CitizenList;


		const CitizenList& getEligibleCitizens() const;
		const char* getName() const;
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
		int getLogicSize() const;
		bool setRepsArrByPartyID(int partyID, int repsAmount);
	};
}