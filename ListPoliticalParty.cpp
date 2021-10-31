#define _CRT_SECURE_NO_WARNINGS
#include "ListPoliticalParty.h"
#include "ListCivilien.h"
#include "PoliticalParty.h"
#include <iostream>
#include "Excpetion.h"
namespace election {

	ListPoliticalParty::~ListPoliticalParty()//deleting all the nodes and the political party
	{
		ListT<PoliticalParty>::Iterator itr = lst.begin();
		ListT<PoliticalParty>::Iterator deleteNode = nullptr;
		while (itr != lst.end())
		{
			deleteNode = itr;
			delete (*itr);
			++itr;
			lst.erase(deleteNode);
		}
	}

	void ListPoliticalParty::setLengthToAllTheParties(int length)//set the length of the arr of the list civiliens
	{
		ListT<PoliticalParty>::Iterator itr = lst.begin();
		while (itr!=lst.end())
		{
			(*itr)->setLength(length);
			++itr;
		}
	}

	PoliticalParty* ListPoliticalParty::findPoliticalParty(int politicalNum)//searching the political party if it exciste
	{
		ListT<PoliticalParty>::Iterator itr = lst.begin();
		for (;itr != lst.end(); itr++)
		{
			if ((*itr)->getNumOfTheParty() == politicalNum)
				return (*itr);
		}
		return nullptr;
	}

	void ListPoliticalParty::setDelegate(PoliticalParty* party, int numOfDistrict, Civilien* civilien)//adding to the district num in index numOfDistict a delagte to the list
	{
		party->getTheArrOfTheDelegates()[numOfDistrict].getList().push_back(civilien);
		party->getTheArrOfTheDelegates()[numOfDistrict].getList().setSize();
	}

	void ListPoliticalParty::printListPoliticalParty(int typeElection) //Prints the list
	{
		cout << "The details for all the politicals Party are: ";
		cout << endl;
		ListT<PoliticalParty>::Iterator itr = lst.begin();
		while (itr != lst.end())
		{
			(*itr)->printPoliticalParty(typeElection);//Prints The political party
			++itr;
		}
	}

	bool ListPoliticalParty::findPoliticalPartyByName(string name)//searching a political party by the name
	{
		ListT<PoliticalParty>::Iterator itr = lst.begin();
		while (itr != lst.end())
		{
			if ((*itr)->getNameOfTheParty()== name)
				return true;
			++itr;
		}
		return false;//if there is not a political party by the name,return false
	}

	void ListPoliticalParty::save(std::ostream& o) //Saving the detailse of the current election round
	{
		int size = lst.GetSizeOfList();
		o.write(rcastcc(&size), sizeof(size));
		ListT<PoliticalParty>::Iterator iter = lst.begin();
		for (; iter != lst.end(); ++iter)
		{
			(*iter)->save(o);
		}
	}

	void ListPoliticalParty::load(std::istream& i, ListDistrict& lstDist)
	{
		int size;
		i.read(rcastc(&size), sizeof(size));
		PoliticalParty* party;
		for (int j = 0; j < size; j++)
		{
			party = new PoliticalParty();
			party->load(i,lstDist);
			lst.push_back(party);
			lst.setSize();
		}
	}


}