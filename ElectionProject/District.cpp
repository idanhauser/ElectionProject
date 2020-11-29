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

	District::District(const char* name, const Citizen* eligibleCitizens, int eligcit_size_) :name(new char[MAX_SIZE]), eligibleCitizens(new Citizen[eligcit_size_ * 2]), logicSizeEligciti(eligcit_size_), phySizeEligciti(eligcit_size_ * 2), serialNum(snGenerator++)
	{
		long namelen = strlen(name);
		this->name = new char[namelen + 2];
		strncpy(this->name, name, namelen);

		for (int i = 0; i < eligcit_size_; ++i)
		{
			this->eligibleCitizens[i] = Citizen(eligibleCitizens[i]);
		}
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
}
