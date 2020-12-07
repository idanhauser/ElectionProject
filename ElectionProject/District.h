//code verison 1.0
#pragma once
#include "CitizenList.h"
using namespace std;
#include <string>


namespace elec
{
	class CitizenList;


	class District
	{
	private:
		static int snGenerator;
		int _serialNum;
		char* _name;
		CitizenList _Citizens;
		double _votersPercentage;
		int _electionResult;
		int _numOfReps;


		District(const District& other);
		const District& operator=(const District&);

	public:
		//friend class Citizen;//TODO:idan do we need it? 
		District() = delete;///we delete default constructor
		District(const char* name, int numOfReps);
		~District();
		friend ostream& operator<<(ostream& os, const District& district);
		//friend class CitizenList;


		const CitizenList& getEligibleCitizens() const;
		const char* getName() const;
		double getVotersPercentage() const;
		int getElectionResults()const;
		int getSerialNum() const;
		int getNumberOfCitizens() const;
		bool addCitizen(Citizen* citz);
		const Citizen& getCitizenById(int id) const;
		Citizen& getCitizenById(int id);

		bool isCitizenExist(int id) const;
	};
}