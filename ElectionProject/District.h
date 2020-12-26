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
		int _electionResult;//roee what is that?
		int _numOfReps;

		int _numberOfVotesinDist;
		District(const District& other);
		const District& operator=(const District&);

	public:

		District() = delete;///we delete default constructor
		District(const char* name, int numOfReps);
		virtual ~District();
		friend ostream& operator<<(ostream& os, const District& district);
		//friend class CitizenList;


		const CitizenList& getEligibleCitizens() const;
		const char* getName() const;
		double getVotersPercentage() const;
		CitizenList getElectionResults()const;
		int getSerialNum() const;
		int getNumberOfCitizens() const;
		bool addCitizen(Citizen* citz);
		const Citizen& getCitizenById(int id) const;
		Citizen& getCitizenById(int id);
		virtual int getNumOfReps() const;
		bool isCitizenExist(int id) const;
		int getVotingCitizensAmountInDistrict() const;
		void operator++(int);
		/// <summary>
		/// saving the citizens in the list
		/// </summary>
		/// <param name="outFile">the file we want to write to</param>
		void save(ofstream& outFile) const;
	};
}