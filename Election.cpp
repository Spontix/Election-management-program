#define _CRT_SECURE_NO_WARNINGS
#include "Election.h"
#include "Excpetion.h"
#include <iostream>

namespace election {

	void Election::save(std::ostream& o)
	{
		_date.save(o);
		_lstDist.save(o);
		_lstParty.save(o);
	}

	void Election::load(std::istream& i, int kind)
	{
		if (!i.good())
			throw LoadException();
		_kind = kind;
		_date.load(i);
		_lstDist.load(i);
		_lstParty.load(i, _lstDist);
	}

	void RegularElection::load(std::istream& i, int kind)
	{
		if (!i.good())
			throw LoadException();
		Election::load(i, kind);
	}

	void RegularElection::save(std::ostream& o)
	{
		Election::save(o);
	}

	void SimpleElection::save(std::ostream& o)
	{
		Election::save(o);
	}

	void SimpleElection::load(std::istream& i, int kind)
	{
		if (!i.good())
			throw LoadException();
		Election::load(i, kind);
	}

}