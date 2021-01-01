﻿//code verison 3.0
#include "LoadElectionSystem.h"

namespace elec
{

	LoadElectionSystem::LoadElectionSystem(char fileName[MAX_SIZE]) :_inFile(fileName, ios::binary), _isFileNotOk(false)
	{

		if (!_inFile) {
			_isFileNotOk = true;
		}
	}

	LoadElectionSystem::~LoadElectionSystem()
	{
		if (_inFile.is_open())
		{
			_inFile.close();
		}
	}

	ElectionType LoadElectionSystem::getElectionType()
	{
		int type;
		if (CheckFile())
		{
			_inFile.read(rcastc(&type), sizeof(int));
		}
		return static_cast<ElectionType>(type);
	}

	bool LoadElectionSystem::CheckFile() const
	{
		return _isFileNotOk ? false : true;
	}

	ifstream& LoadElectionSystem::getReader()
	{

		return _inFile;

	}
}
