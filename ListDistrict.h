#pragma once
#include <fstream>
#include "ListTemplate.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;

namespace election {
	class District;
	class Civilien;
	class ListDistrict
	{
	private:
		ListT<District> lst;
	public:
		ListDistrict() = default;//ctor
		~ListDistrict();//dtor
		District* findDistrict(int numOfDistrict);//find district by his num  serial
		bool findDistrictByName(string name);//find district by his name
		Civilien* findCivilien(int id);//finding civilien by his id
		void printList(int typeElection);//print the list
		void printListCivilienInAllDistricts(int typeElection);
		ListT<District>& getList() { return lst; }

		void save(std::ostream& o);//save all the fileds of the list of districts to a file.
		void load(std::istream& i);//load all the fileds of the list of districts from a file.
	};
}