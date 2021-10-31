#define _CRT_SECURE_NO_WARNINGS
#include "Excpetion.h"
#include "Civilien.h"
#include <iostream>
#include "District.h"

namespace election
{
	Civilien::Civilien(const string name, int id, int birthYear, District* district)
		:_name(name), _id(id), _birthYear(birthYear), _district(district), _isVoted(false), _isDelegate(false), _isCandidate(false)
	{
	}

	Civilien::Civilien(const Civilien& civilien):_name(civilien._name),_id(civilien._id),_birthYear(civilien._birthYear),_district(civilien._district)
	{
	}
	void Civilien::printCivilien()
	{
		cout << "Name: " << _name << endl;
		cout << "Id: " << _id << endl;
		cout << "Birth year: " << _birthYear << endl;
		cout << endl;
	}
	
	void Civilien::save(std::ostream& o)
	{
		this->_district->getSerial();

		int len = _name.size();
		o.write(rcastcc(&len), sizeof(len));
		o.write(rcastcc(&_name[0]), len * sizeof(char));
		o.write(rcastcc(&_id), sizeof(_id));
		o.write(rcastcc(&_birthYear), sizeof(_birthYear));
		o.write(rcastcc(&_isVoted), sizeof(_isVoted));
		o.write(rcastcc(&_isDelegate), sizeof(_isDelegate));
		o.write(rcastcc(&_isCandidate), sizeof(_isCandidate));
		//int dis= this->_district->getSerial();
		//o.write(rcastcc(&dis), sizeof(dis));

	}
	void Civilien::load(istream& i,District* district)
	{
		if (!i.good())
			throw LoadException();
		int len;
		i.read(rcastc(&len), sizeof(len));
		_name.resize(len + 1);
		i.read(rcastc(&_name[0]), len * sizeof(char));
		i.read(rcastc(&_id), sizeof(_id));
		i.read(rcastc(&_birthYear), sizeof(_birthYear));
		i.read(rcastc(&_isVoted), sizeof(_isVoted));
		i.read(rcastc(&_isDelegate), sizeof(_isDelegate));
		i.read(rcastc(&_isCandidate), sizeof(_isCandidate));
		_district = district;
	}
}


