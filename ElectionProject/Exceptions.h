//code verison 3.2
#pragma once
#include <string>
using namespace std;
#include <algorithm>
#include "Utils.h"

namespace elec
{


	class DateException : std::exception
	{
	protected:
		string _output;
	public:
		virtual ~DateException() = default;

		virtual void Error()
		{
			_output.append("Some date exception: ");
		}

		virtual const string& getMessage() const
		{
			return _output;
		}
	};

	class DayException : public DateException
	{
	public:
		explicit DayException(int day)
			: _day(day)
		{
		}
		virtual void Error() override
		{
			DateException::Error();
			_output.append("day can not be ");
			_output.append(to_string(_day));
			_output.append(".\n");
		}

	private:
		int _day;
	};

	class YearException : public DateException
	{
	public:
		explicit YearException(int year)
			: _year(year)
		{
		}
		virtual void Error() override
		{
			DateException::Error();
			_output.append("year can't be negative: ");
			_output.append(to_string(_year));
			_output.append(".\n");
		}

	private:
		int _year;
	};

	
	class DayMonthException : public DateException
	{
	public:

		DayMonthException(int day, int month)
			: _day(day),
			_month(month)
		{
		}
		virtual void Error() override
		{
			Months m = static_cast<Months>(_month);
			DateException::Error();
			_output = "In month " + MONTHS_NAME.at(static_cast<int>(_month));
			if (m == Months::February)
			{
				if (_day>28)
				{
					_output.append(" we have only 28 days.");
				}
			}
			else if ((m == Months::January) || (m == Months::March) || (m == Months::May) || (m ==
				Months::July) || (m == Months::August) || (m == Months::October) || (m == Months::December))
			{
				if ( _day>31)
				{
					_output.append(" we have only 31 days.");
				}
			}
			else
			{
				if ( _day>30)
				{
					_output.append(" we have only 30 days.");
				}
			}
		}

	private:
		int _day;
		int _month;
	};

	
	class MonthException : public DateException
	{
	public:
		explicit MonthException(int month)
			: _month(month)
		{
		}
		virtual void Error() override
		{
			DateException::Error();
			_output.append(" Month can not be ");
			_output.append(to_string(_month));
			_output.append(".\n");
		}
	private:
		int _month;
	};



	class InputException
	{
	protected:
		string _output;
	public:
		virtual ~InputException() = default;

		virtual void Error()
		{
			_output.append("Some input exception: ");
		}

		virtual const string& getMessage() const
		{
			return _output;
		}
	};




	class IdException :InputException
	{

	public:
		explicit IdException(int id)
			: _id(id)
		{
		}

		virtual ~IdException() = default;

		virtual void Error() override
		{
			InputException::Error();
			_output.append(" The len of the id is :" + to_string(_id) + ", when it must be 9 digits.\n");
		}
	private:
		int _id;
	};






	class ElectionSystemException
	{
	protected:
		string _output;
	public:
		virtual ~ElectionSystemException() = default;

		virtual void Error()
		{
			_output.append("Some error with election system: ");
		}

		virtual const string& getMessage() const
		{
			return _output;
		}
	};


	class CitizenNotExistException :public ElectionSystemException
	{

	public:
		explicit CitizenNotExistException(int id)
			: _id(id)
		{
		}

		virtual ~CitizenNotExistException() = default;

		virtual void Error() override
		{
			ElectionSystemException::Error();
			_output.append(" The citizen with id :" + to_string(_id) + " wasn't found.\n");
		}
	private:
		int _id;
	};

	class DistcritsNotExistException :public ElectionSystemException
	{

	public:
		explicit DistcritsNotExistException(int id)
			: _id(id)
		{
		}

		virtual ~DistcritsNotExistException() = default;

		virtual void Error() override
		{
			ElectionSystemException::Error();
			_output.append(" The distcrit with id :" + to_string(_id) + " wasn't found.\n");
		}
	private:
		int _id;
	};



	class CitizenExistException :public ElectionSystemException
	{

	public:
		explicit CitizenExistException(int id,int distId)
			: _id(id),_distId(distId)
		{
		}

		virtual ~CitizenExistException() = default;

		virtual void Error() override
		{
			ElectionSystemException::Error();
			_output.append(
				" The citizen with id :" + to_string(_id) + " already exist and live in distcrit id: " +
				to_string(_distId) + ".\n");
		}
	private:
		int _id;
		int _distId;
	};

	class DistcritsExistException :public ElectionSystemException
	{

	public:
		explicit DistcritsExistException(int id)
			: _id(id)
		{
		}

		virtual ~DistcritsExistException() = default;

		virtual void Error() override
		{
			ElectionSystemException::Error();
			_output.append(" The distcrit with id :" + to_string(_id) + " already exist.\n");
		}
	private:
		int _id;
	};

	class PartyNotExistException :public ElectionSystemException
	{

	public:
		explicit PartyNotExistException(int id)
			: _id(id)
		{
		}

		virtual ~PartyNotExistException() = default;

		virtual void Error() override
		{
			ElectionSystemException::Error();
			_output.append(" The party with id :" + to_string(_id) + " wasn't found.\n");
		}
	private:
		int _id;
	};




	
	class NullObjectException :public ElectionSystemException
	{

	public:
		explicit NullObjectException(string& where)
			: _place(where)
		{
		}
		virtual ~NullObjectException() = default;

		virtual void Error() override
		{
			ElectionSystemException::Error();
			_output.append(" Couldn't proceed with you request with "+ _place+" unfortunatly, please try again.\n");
		}

	private:
	string _place;
	
	};



	class AgeException :public ElectionSystemException
	{

	public:
		explicit AgeException(int birth, int currYear)
			: age(currYear-birth)
		{
		}
		virtual ~AgeException() = default;

		virtual void Error() override
		{
			ElectionSystemException::Error();
			_output.append(
				" Can't add citizen because he is only " + to_string(age) +
				" years old, try again when he turns 18.\n");
		}

	private:
		int age;


	};


	class ResultsException
	{
	protected:
		string _output;

	public:
		ResultsException()
		{
			_output.append("Error Calculating Results: ");
		};
		~ResultsException() = default;

		virtual const string& getMessage() const
		{
			return _output;
		}





	};

	class PartiesException : public ResultsException
	{
	public:
		PartiesException()
		{
			Error();
		}
		virtual ~PartiesException() = default;

		virtual void Error()
		{
			_output.append("There aren't parties inserted. You must have at least 1.");


		}

	};
	class DistrictsException : public ResultsException
	{
	public:
		DistrictsException()
		{
			Error();
		}
		virtual ~DistrictsException() = default;
		virtual void Error()
		{
			_output.append("There aren't districts inserted. You must have at least 1.");

		}



	};

	
	

}