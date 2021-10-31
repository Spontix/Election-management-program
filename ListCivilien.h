#pragma once
#include "Civilien.h"
#include "ListDistrict.h"
#include "ListTemplate.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;

namespace election {
	class District;
	class ListDistrict;
	class ListPoliticalParty;
	class PoliticalParty;
	class ListCiviliens {
	private:
		ListT<Civilien> lst;
		int _amountOfVotersPerParty;//index that counting the votes per party
	public:
		ListCiviliens() :_amountOfVotersPerParty(0) {}//ctor
		int& getAmountOfVotersPerParty() { return _amountOfVotersPerParty; }
		//printers
		void printListCiviliens();
		void freeNodes(bool deleteCivilien = false);
		void setAmountOfVotersPerParty() { _amountOfVotersPerParty++; }
		ListT<Civilien>& getList() { return lst; }
		//serialization
		void saveListById(std::ostream& o);	
		void loadListById(std::istream& i,ListDistrict& dist_lst);

		void save(std::ostream& o);//save all the fileds of the list civiliens in a file
		void load(std::istream& i, District* district);
	};
}