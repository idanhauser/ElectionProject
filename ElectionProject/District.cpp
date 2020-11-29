#include "District.h"
namespace elec
{
	int District::snGenerator = 100;

	/**
	 * \brief constructor for a district
	 * \param name the name of the district
	 * \param eligibleCitizens list of citizens that allowed to vote
	 * \param eligcitSize
	 */

	District::District(const char* name, const Citizen* eligibleCitizens) :
		name(new char[MAX_SIZE]), eligibleCitizens(new Citizen[MAX_SIZE]), logicSizeEligciti(0), phySizeEligciti(MAX_SIZE), serialNum(snGenerator++)
	{
		long namelen = strlen(name);
		this->name = new char[namelen + 2];
		strncpy(this->name, name, namelen);
		votersPercentage = 0;
	}

	District::District(const District& other)
	{




		setName(other.name);
		this->serialNum = other.serialNum;
		setEligibleCitizens(other.eligibleCitizens, other.logicSizeEligciti);
		votersPercentage = other.votersPercentage;
	}

	District::~District()
	{
		delete[] name;
		delete[] eligibleCitizens;
	}

	bool District::setName(const char* name)
	{
		long namelen = strlen(name);
		this->name = new char[namelen + 1];
		strncpy(this->name, name, namelen);
		return true;
	}

	bool District::setEligibleCitizens(Citizen* eligibleCitizens, int size)
	{
		delete[] this->eligibleCitizens;
		phySizeEligciti = size * 2;
		logicSizeEligciti = size;
		this->eligibleCitizens = new Citizen[phySizeEligciti];
		for (int i = 0; i < size; ++i)
		{
			this->eligibleCitizens[i] = Citizen(eligibleCitizens[i]);
		}
		return true;
	}


	const char* District::getName() const
	{
		return name;
	}

	Citizen* District::getEligibleCitizens() const
	{
		return eligibleCitizens;
	}

	double District::getVotersPercentage() const
	{
		return votersPercentage;
	}

	bool District::addEligibleCitizen(const Citizen& cit)
	{
		if (logicSizeEligciti < phySizeEligciti)
		{
			eligibleCitizens[logicSizeEligciti++] = cit;
		}
		//else realloc
	}
}
