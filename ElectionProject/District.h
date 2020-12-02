﻿#pragma once

#include <string>
#include <iostream>
#include "CitizenList.h"
#include "Utils.h"
namespace elec
{
	class CitizenList;


	class District
	{
	private:
		static int snGenerator;
		int _serialNum;
		char* _name;
		CitizenList _Citizens;// or CitizenList* _Citizens; or CitizenList** _Citizens;
		double _votersPercentage;
		int _electionResult;


		District(const District& other);
		const District& operator=(const District&);

	public:
		//friend class Citizen;//TODO:idan do we need it? 
		District() = delete;///we delete default constructor
		District(const char* name);

		~District();
		friend ostream& operator<<(ostream& os, const District& district);
		friend class CitizenList;
		

		const CitizenList& getEligibleCitizens() const;
		const char* getName() const;
		double getVotersPercentage() const;
		int getElectionResults()const;
		int getSerialNum() const;
		int getNumberOfCitizens() const;



		/* //roee:
			bool Party::addEligibleCitizens(Citizen* citizen)
			{
				return _eligibleCitizens.addListMember(citizen);
			}*/



			//bool setName(const char* name);
			//bool setEligibleCitizens(Citizen** eligible_Citizens, int size); //roee: need to change from citizen** to list.

	};
}