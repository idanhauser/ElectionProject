//code verison 2.0
#pragma once

#include "District.h"

namespace elec
{


	class UnifiedDistrict :public District
	{
		const Citizen* _partyLeader;
	public:
		UnifiedDistrict(const char* name, int numOfReps, int numOfParties);
		~UnifiedDistrict();

		const Citizen* getPartyLeader() const override;
		bool setLeader(const Citizen* leader)  override;
		
		friend ostream& operator<<(ostream& os, const UnifiedDistrict& district);

		virtual const char* getName() const override 
		{
			return _name;
		};



		/*base funcs*/
		const CitizenList& getEligibleCitizens() const {return  District::getEligibleCitizens(); };
		const double getVotersPrecentage() const { return District::getVotersPrecentage(); };
		CitizenList getElectionResults()const { return District::getElectionResults(); };
		int getSerialNum() const { return District::getSerialNum(); };
		int getNumberOfCitizens() const { return District::getNumberOfCitizens(); };
		bool addCitizen(Citizen* citz) { return District::addCitizen(citz); };
		bool addrepToArr() { return District::addrepToArr(); };
		const Citizen& getCitizenById(int id) const { return District::getCitizenById(id); };
		Citizen& getCitizenById(int id) { return District::getCitizenById(id); };
		int getNumOfReps() const { return District::getNumOfReps(); };
		bool settVotersPrecentage(const int num) { return District::settVotersPrecentage(num); };
		bool isCitizenExist(int id) const { return District::isCitizenExist(id); };
		int getVotingCitizensAmountInDistrict() const { return District::getVotingCitizensAmountInDistrict(); };
		void operator++(int x) { District::operator++(x); }; //todo: check
		void realloc(int new_size) { District::realloc(new_size); };
		int getRepsByPartyLogicSize() const { return District::getRepsByPartyLogicSize(); };
		bool setRepsArrByPartyID(int partyID, int repsAmount) { return District::setRepsArrByPartyID( partyID, repsAmount); };
		int getRepsByPartyID(int partyID) const { return District::getRepsByPartyID(partyID); };



	};

}
