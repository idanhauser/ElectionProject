#pragma once
#include <string>
using namespace std;
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
		string output;
	public:
		virtual ~InputException() = default;

		virtual void show()
		{
			output.append("Some input exception: ");
		}
	};


	class numOfRepException :InputException
	{

	public:
		explicit numOfRepException(int num_of_reps)
			: _numOfReps(num_of_reps)
		{
		}

		virtual ~numOfRepException() = default;

		virtual void show() override
		{
			InputException::show();
			output.append("Number of representative can't be negative or zero, please insert netrual number");
		}
	private:
		int _numOfReps;
	};
}