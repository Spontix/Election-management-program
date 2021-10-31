#pragma once
#include <fstream>
#include "ListCivilien.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;

namespace election {
	class Civilien;
	class ListDistrict;
	class PoliticalParty
	{
	private:
		string _nameOfTheParty;
		Civilien* _candidate;
		ListCiviliens* arrOfDelagatesPerDis;
		static int _num;
		int _numOfTheParty;
		int _size;//logical size
		int _len;//phis size
		void resize(int size);//resize the size of the arr

	public:
		PoliticalParty() = default;
		PoliticalParty(string nameOfTheParty, Civilien* candidate);//ctor
		~PoliticalParty();//dtro


		/**********************Geters*************************/
		int getNumOfTheParty()const { return _numOfTheParty; }
		Civilien* getCandidate()const { return _candidate; }
		string getNameOfTheParty()const { return _nameOfTheParty; }
		int getLen() { return _len; }
		static int getNum() { return _num; }
		ListCiviliens* getTheArrOfTheDelegates() { return arrOfDelagatesPerDis; }
		/**********************Seters*************************/
		void setArr(int size);//arr of list of civilien that are delegate per dist
		void setLength(int newlen);
		void setTheArrOfTheDelegates(int index) { arrOfDelagatesPerDis[index].setAmountOfVotersPerParty(); }

		void printPoliticalParty(int typeElection);//print the political party
		void save(std::ostream& o);//save all the fileds of politicals party in file.
		void load(std::istream& i, ListDistrict& lstDist);//load all the fileds of politicals party from a file.
	};
}

