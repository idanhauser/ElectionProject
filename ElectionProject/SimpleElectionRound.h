//code verison 2.0
#pragma once
#include "ElectionRound.h"

namespace elec
{


	class SimpleElctionRound :public ElectionRound
	{
		int _numOfRep;
	public:

		explicit SimpleElctionRound(int date[8],int numOfReps);
	};
}