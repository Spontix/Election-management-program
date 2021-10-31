#define _CRT_SECURE_NO_WARNINGS
#include "Excpetion.h"
#include <iostream>
#include "ListCivilien.h"
#include "ListPoliticalParty.h"
#include "PoliticalParty.h"
#include "District.h"
namespace election
{

	
	void ListCiviliens::printListCiviliens()
	{
		ListT<Civilien>::Iterator itr = lst.begin();
		while (itr != lst.end())
		{
			(*itr)->printCivilien();
			++itr;
		}

	}

	void ListCiviliens::freeNodes(bool deleteCivilien)
	{
		ListT<Civilien>::Iterator itr = lst.begin();
		ListT<Civilien>::Iterator deleteNode = nullptr;
		while (itr != lst.end())
		{
			deleteNode = itr;
			if (deleteCivilien)
				delete (*itr);
			++itr;
			lst.erase(deleteNode);

		}
	}

	void ListCiviliens::saveListById(std::ostream& o)
	{
		o.write(rcastcc(&_amountOfVotersPerParty), sizeof(_amountOfVotersPerParty));
		int size=lst.GetSizeOfList();
		o.write(rcastcc(&size), sizeof(size));
		auto iter = lst.begin();
		for (; iter != lst.end(); iter++)
		{
			int id = (*iter)->getID();
			o.write(rcastcc(&id), sizeof(id));
		}
	}

	void ListCiviliens::loadListById(std::istream& i, ListDistrict& dist_lst)
	{
		i.read(rcastc(&_amountOfVotersPerParty), sizeof(_amountOfVotersPerParty));
		int size,id;
		i.read(rcastc(&size), sizeof(size));//the number of nodes in the list
		for (int j = 0; j < size; j++)
		{
			i.read(rcastc(&id), sizeof(id));//read the id of the civilian
			Civilien* c = dist_lst.findCivilien(id);//find the civilian fron the states
			lst.push_back(c);//add the civilian to the list
			lst.setSize();//update the len of the list after adding the node
		}
	}


	void ListCiviliens::save(ostream& o)
	{
		o.write(rcastcc(&_amountOfVotersPerParty), sizeof(_amountOfVotersPerParty));
		int size = lst.GetSizeOfList();
		o.write(rcastcc(&size), sizeof(size));//the number of nodes in the list
		ListT<Civilien>::Iterator iter = lst.begin();
		for (; iter != lst.end(); ++iter)
		{
			(*iter)->save(o);
		}
	}

	void ListCiviliens::load(std::istream& i, District* district)
	{
		i.read(rcastc(&_amountOfVotersPerParty), sizeof(_amountOfVotersPerParty));
		int size;
		i.read(rcastc(&size), sizeof(size));//the number of nodes in the list
		Civilien* civilien;
		for (int j = 0; j < size; j++)
		{
			civilien = new Civilien();//allocate new civilian
			civilien->load(i,district);//load the civilian
			lst.push_back(civilien);//add the civilian to the list
			lst.setSize();//update the len of the list after adding the node
		}
	}


}
