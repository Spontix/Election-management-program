#define _CRT_SECURE_NO_WARNINGS
#include "ListDistrict.h"
#include <iostream>
#include "District.h"
#include "ListCivilien.h"
#include "Excpetion.h"
using namespace std;

namespace election {

	District* ListDistrict::findDistrict(int numOfDistrict)
	{
		ListT<District>::Iterator itr = lst.begin();
		while (itr != lst.end())
		{
			if ((*itr)->getSerial() == numOfDistrict)
			{
				return (*itr);
			}
			++itr;
		}
		return nullptr;
	}

	Civilien* ListDistrict::findCivilien(int id)
	{
		ListT<District>::Iterator itr = lst.begin();
		while (itr != lst.end())
		{
			ListT<Civilien>::Iterator itrCivilien = (*itr)->getListOfVotersPerDistrict()->getList().begin();
			while (itrCivilien != nullptr)
			{
				if ((*itrCivilien)->getID() == id)
					return (*itrCivilien);
				++itrCivilien;
			}
			++itr;
		}
		return nullptr;
	}
	void ListDistrict::printList(int typeElection)
	{
		ListT<District>::Iterator itr = lst.begin();
		while (itr != lst.end())
		{
			if (typeElection == 2)
			{
				(*itr)->printDistrict(typeElection);
			}
			else
			{
				cout << "The kind of the district is:";
				if (dynamic_cast<DevidedDistrict*>((*itr)))
					cout << "Devided District" << endl;
				else
					cout << "Unified District" << endl;
				(*itr)->printDistrict(typeElection);
			}
			++itr;
		}
	}

	void ListDistrict::printListCivilienInAllDistricts(int typeElection)
	{
		if (typeElection == 2)
			cout << "The details for all civiliens are: " << endl;
		else
			cout << "The details for all civiliens in all of the districts are: " << endl;
		cout << endl;
		ListT<District>::Iterator itr = lst.begin();
		while (itr != lst.end())
		{
			(*itr)->printListCiviliens(typeElection);
			++itr;
		}
	}

	bool ListDistrict::findDistrictByName(string name)
	{
		ListT<District>::Iterator itr = lst.begin();
		while (itr != lst.end())
		{
			if ((*itr)->getName() == name)
			{
				return true;
			}
			++itr;
		}
		return false;
	}

	ListDistrict::~ListDistrict()
	{
		ListT<District>::Iterator itr = lst.begin();
		ListT<District>::Iterator deleteNode = nullptr;
		while (itr != lst.end())
		{
			deleteNode = itr;
			delete (*itr);
			++itr;
			lst.erase(deleteNode);
		}
	}
	void ListDistrict::save(std::ostream& o)
	{
		int size = lst.GetSizeOfList();
		o.write(rcastcc(&size), sizeof(size));
		ListT<District>::Iterator iter = lst.begin();
		for (; iter != lst.end(); ++iter)
		{
			int type = (*iter)->getTypeOf();
			o.write(rcastcc(&type), sizeof(type));
			(*iter)->save(o);
		}
	}

	void ListDistrict::load(std::istream& i)
	{
		int size, type;
		i.read(rcastc(&size), sizeof(size));
		District* theDistrict;
		for (int j = 0; j < size; j++)
		{
			i.read(rcastc(&type), sizeof(type));
			if (!type)//type==0
				theDistrict = new District();
			else//type==1
				theDistrict = new DevidedDistrict();

			theDistrict->load(i);
			lst.push_back(theDistrict);
			lst.setSize();
		}
	}

}
