//code verison 3.1
#include "LoadElectionSystem.h"

#include <iostream>
using namespace std;
namespace elec
{

	LoadElectionSystem::LoadElectionSystem(string fileName) noexcept(false): _isFileNotOk(false)
	{
		
		try {
			_inFile.close();
			_inFile.exceptions(ifstream::badbit);
			_inFile.open(fileName, ios::binary);
		}
		catch(const ifstream::failure&ex)
		{
			cout << "Error while opening the file" << endl;
			throw;
		}
		_isFileNotOk = false;
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
