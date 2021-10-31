#pragma once
#include <fstream>
#include <array>
#include "Excpetion.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
namespace election {
	constexpr static array<int, 12> Mounths = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	class Date {
	private:
		int _d;// day
		int _m;// mounth
		int _y;// year
	public:
		Date() = default;//ctor
		Date(const Date& other) :_d(other._d), _m(other._m), _y(other._y) {}
		Date(int d, int m, int y) :_d(d), _m(m), _y(y)
		{
			if (y <= 0)
			{
				throw YearException();
			}
			if (m > 12 || m < 1)
			{
				throw MounthException();
			}
			if (Mounths[m - 1] - d < 0)
			{
				throw DayFloatException();
			}
			if (d < 0)
			{
				throw DayNegativException();
			}
		}
		//ctor
		/**********************Geters*************************/
		int getDay()const { return _d; }
		int getMounth()const { return _m; }
		int getYear()const { return _y; }
		/**********************Seters*************************/
		void setAll(int d, int m, int y)
		{
			_d = d;
			_m = m;
			_y = y;
		}



		void load(std::istream& i)//load from a file the detailse of date
		{
			if (!i.good())
				throw LoadException();
			i.read(rcastc(&_d), sizeof(_d));
			i.read(rcastc(&_m), sizeof(_m));
			i.read(rcastc(&_y), sizeof(_y));
		}
		void save(std::ostream& o) const//save to file the details of date
		{

			o.write(rcastcc(&_d), sizeof(_d));
			o.write(rcastcc(&_m), sizeof(_m));
			o.write(rcastcc(&_y), sizeof(_y));

		}

	};
}