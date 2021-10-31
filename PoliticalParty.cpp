#define _CRT_SECURE_NO_WARNINGS
#include "ListCivilien.h"
#include "PoliticalParty.h"
#include <iostream>
#include "Excpetion.h"
namespace election {
	int PoliticalParty::_num = 0;

	PoliticalParty::PoliticalParty(string nameOfTheParty, Civilien* candidate)
		:_nameOfTheParty(nameOfTheParty),_size(0),_len(0), _candidate(candidate), arrOfDelagatesPerDis(nullptr), _numOfTheParty(_num)

	{
		++_num;
	}

	void PoliticalParty::setArr(int size)
	{
		arrOfDelagatesPerDis = new ListCiviliens[size * 2];
		_size = size * 2 + 1;
		_len = size;
	}

	void PoliticalParty::setLength(int newlen)
	{
		if (newlen == _size)
		{
			resize(newlen * 2 + 1);
		}
		this->_len = newlen;
	}

	void PoliticalParty::resize(int size)
	{
		ListCiviliens* temp = new ListCiviliens[size];
		//memcpy(temp, arrOfDelagatesPerDis, _len);
		for (int i = 0; i < _len; i++)
		{
			temp[i] = arrOfDelagatesPerDis[i];
		}
		delete[] arrOfDelagatesPerDis;
		arrOfDelagatesPerDis = temp;
		this->_size = size;
	}


	void PoliticalParty::printPoliticalParty(int typeElection)
	{
		cout << "Name of political party: " << _nameOfTheParty << endl;
		cout << "Number of political party : " << _numOfTheParty << endl;
		cout << "The candidate of this political party is : " << endl;
		_candidate->printCivilien();
		if (typeElection == 1)
			cout << "The Delagates Per District of this political party are : " << endl;
		else
			cout << "The Delagates of this political party are : " << endl;
		for (int i = 0; i < _len; i++)
		{
			arrOfDelagatesPerDis[i].printListCiviliens();
		}
		cout << endl;
	}
	PoliticalParty::~PoliticalParty()
	{
		for (int i = 0; i < _len; i++)
			arrOfDelagatesPerDis[i].freeNodes(false);
		delete[] arrOfDelagatesPerDis;
	}


	void PoliticalParty::save(std::ostream& o)
	{
		int len = _nameOfTheParty.size();

		o.write(rcastcc(&len), sizeof(len));
		o.write(rcastcc(&_nameOfTheParty[0]), len);
		int id = _candidate->getID();
		o.write(rcastcc(&id),sizeof(int));
		o.write(rcastcc(&_num), sizeof(_num));
		o.write(rcastcc(&_numOfTheParty), sizeof(_numOfTheParty));
		o.write(rcastcc(&_size), sizeof(_size));
		o.write(rcastcc(&_len), sizeof(_len));
		for (int j = 0; j < _len; j++)
			arrOfDelagatesPerDis[j].saveListById(o);
	}

	void PoliticalParty::load(std::istream& i, ListDistrict& lstDist)
	{
		if (!i.good())
			throw LoadException();
		int len, id;
		i.read(rcastc(&len), sizeof(len ));
		_nameOfTheParty.resize(len + 1);
		i.read(rcastc(&_nameOfTheParty[0]), len);
		i.read(rcastc(&id), sizeof(id));
		_candidate=lstDist.findCivilien(id);
		i.read(rcastc(&_num), sizeof(_num));
		i.read(rcastc(&_numOfTheParty), sizeof(_numOfTheParty));
		i.read(rcastc(&_size), sizeof(_size));
		i.read(rcastc(&_len), sizeof(_len));
		arrOfDelagatesPerDis = new ListCiviliens[_len];
		for (int j = 0; j < _len; j++)
			arrOfDelagatesPerDis[j].loadListById(i, lstDist);
	}




}