#pragma once
#include <fstream>

#include "Utils.h"

namespace elec
{
	class LoadElectionSystem
	{
	private:
		 ifstream _inFile;
		 bool _isFileNotOk;
	public:
		LoadElectionSystem() = delete;
		LoadElectionSystem(char fileName[MAX_SIZE]);



		 ~LoadElectionSystem();
		ElectionType getElectionType();
		bool CheckFile() const;
		 ifstream& getReader();
	};
}