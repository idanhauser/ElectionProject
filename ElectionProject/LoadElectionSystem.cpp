//code verison 3.1
#include "LoadElectionSystem.h"

#include <iostream>
using namespace std;
namespace elec
{

	LoadElectionSystem::LoadElectionSystem(string fileName) noexcept(false) : _isFileNotOk(false)
	{

		try {
			_inFile.open(fileName, ios::binary);
			if (!_inFile.good())
			{
				throw "Error while opening the file";
			}
		}
		catch (...)
		{
			_isFileNotOk = false;
			_inFile.close();
			throw;
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
