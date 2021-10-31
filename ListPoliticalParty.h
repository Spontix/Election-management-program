#pragma once
#include "District.h"
#include "PoliticalParty.h"
#include "ArrCandidate.h"
#include "ListTemplate.h"
#include <fstream>

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;

namespace election {
	class PoliticalParty;
	class ListPoliticalParty
	{
	private:
		friend class District;
		friend class DevidedDistrict;
		ListT<PoliticalParty> lst;
	public:
		ListPoliticalParty()=default;//ctor
		~ListPoliticalParty();//dtor

		ListT<PoliticalParty>& getList() { return lst; }
		void setDelegate(PoliticalParty* party, int numOfDistrict, Civilien* civilien);
		void setLengthToAllTheParties(int length);

		PoliticalParty* findPoliticalParty(int PoliticalNum);
		bool findPoliticalPartyByName(string name);//finding political party by the name
		void printListPoliticalParty(int typeElection);//print the list
		void save(std::ostream& o);//save all the fileds of the list of politicals party in file.
		void load(std::istream& i, ListDistrict& lstDist);//load all the fileds of the list of politicals party from a file.
	};
}

