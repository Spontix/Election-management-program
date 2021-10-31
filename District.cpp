#define _CRT_SECURE_NO_WARNINGS
#include "ListCivilien.h"
#include "ListPoliticalParty.h"
#include "ListTemplate.h"
#include "District.h"
#include "Excpetion.h"
#include <iostream>

using namespace std;


namespace election
{
	void bubbleSort(ArrCandidate* arr)
	{
		for (int i = 0; i < PoliticalParty::getNum() - 1; i++)
			for (int j = 0; j < PoliticalParty::getNum() - i - 1; j++)
				if (arr[j].getSumOfDelegateThatEarned() > arr[j + 1].getSumOfDelegateThatEarned())
				{
					ArrCandidate temp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = temp;
				}
	}

	void setTheArrOfCandidates(ArrCandidate* arr, ListT<PoliticalParty>::Iterator& itrParty)
	{
		for (int i = 0; i < PoliticalParty::getNum(); i++)
		{
			arr[i].setCandidate((*itrParty)->getCandidate());//set all the arr to the candidates
			++itrParty;
		}
	}

	int District::_serial = 0;

	District::District(string name, int delegates)
		:_pVotersList(new ListCiviliens), _name(name), _delegates(delegates), _serialPerDistrict(_serial), _sizeOfCivilien(0),
		_amountOfVoters(0), _typeOf(0)
	{
		_serial++;
	}
	District::District(const District& district)
		: _name(district._name), _delegates(district._delegates), _serialPerDistrict(district._serialPerDistrict)
		, _amountOfVoters(district._amountOfVoters), _pVotersList(district._pVotersList), _sizeOfCivilien(district._sizeOfCivilien), _typeOf(district._typeOf)
	{
	}

	void District::add(Civilien* civilien)//adding civilien to a district
	{
		_pVotersList->getList().push_back(civilien);
		++_sizeOfCivilien;
		_pVotersList->getList().setSize();
	}
	void District::printDistrict(int typeElection)
	{
		if (typeElection == 2)
			cout << "There is no districts in this type of election" << endl;
		else
		{
			cout << "Num of district: " << _serialPerDistrict << endl;
			cout << "Name: " << _name << endl;
			cout << "The amount of delegates: " << _delegates << endl;
			cout << endl;
		}



	}

	void District::printListCiviliens(int typeElection)
	{
		ListT<Civilien>::Iterator itr = _pVotersList->getList().begin();
		while (itr != _pVotersList->getList().end())
		{
			District* ForPrint = (*itr)->getDistrict();
			if (typeElection == 1)
			{
				cout << "The serial number of the district is: ";
				cout << ForPrint->getSerial() << endl;
			}
			(*itr)->printCivilien();
			++itr;
		}
	}

	District::~District()
	{
		_pVotersList->freeNodes(true);
		delete _pVotersList;
	}

	DevidedDistrict::~DevidedDistrict()
	{
		getListOfVotersPerDistrict()->freeNodes(true);
		delete getListOfVotersPerDistrict();
	}

	/**/
	PoliticalParty* District::findMaxPerDistrict(ListPoliticalParty& lstPolParty, ArrCandidate* arr, ArrCandidate* tempArr)
	{//return the politicalParty that got the max num of votes in the district
		int i = 0;//goes over the parties
		ListT<PoliticalParty>::Iterator itrParty = lstPolParty.getList().begin();
		PoliticalParty* MaxParty = (*itrParty);
		int max = (*itrParty)->getTheArrOfTheDelegates()[_serialPerDistrict].getAmountOfVotersPerParty();
		arr[i].getSumOfVotesThatEarned() += (*itrParty)->getTheArrOfTheDelegates()[_serialPerDistrict].getAmountOfVotersPerParty();
		tempArr[i].getSumOfVotesThatEarned() = (*itrParty)->getTheArrOfTheDelegates()[_serialPerDistrict].getAmountOfVotersPerParty();
		++itrParty;
		while (itrParty != nullptr)
		{
			i++;

			arr[i].getSumOfVotesThatEarned() += (*itrParty)->getTheArrOfTheDelegates()[_serialPerDistrict].getAmountOfVotersPerParty();
			tempArr[i].getSumOfVotesThatEarned() = (*itrParty)->getTheArrOfTheDelegates()[_serialPerDistrict].getAmountOfVotersPerParty();
			if (max < (*itrParty)->getTheArrOfTheDelegates()[_serialPerDistrict].getAmountOfVotersPerParty())
			{
				MaxParty = (*itrParty);
				max = (*itrParty)->getTheArrOfTheDelegates()[_serialPerDistrict].getAmountOfVotersPerParty();
			}
			++itrParty;
		}
		return MaxParty;
	}
	/**/

	/**/
	void District::CalculateTheAmountOfDelegatesPerParty(ListPoliticalParty& lstPolParty, ArrCandidate* arr, PoliticalParty* party, ArrCandidate* tempArr)
	{
		int countHowManyDelegatesThatEntered = 0;//the number of delegats for the party
		ListT<PoliticalParty>::Iterator itrParty = lstPolParty.getList().begin();
		while (itrParty != nullptr)
		{
			int i = 0;
			double thePresentageOfTheCivilienWhoVote = (((*itrParty)->getTheArrOfTheDelegates()[_serialPerDistrict].getAmountOfVotersPerParty() * 100) / _amountOfVoters);
			int numOfTheDelegateToParty = static_cast<int>(((_delegates * thePresentageOfTheCivilienWhoVote) / 100) + 0.5);
			ListT<Civilien>::Iterator itrCivilien = (*itrParty)->getTheArrOfTheDelegates()[_serialPerDistrict].getList().begin();
			if (numOfTheDelegateToParty > _delegates)
				throw ToFewDelegates();
			
			cout << "The delegates of the political party " << (*itrParty)->getNameOfTheParty() << " in district " << _name << " are:" << endl;
			while (itrCivilien != nullptr && i < numOfTheDelegateToParty)
			{
				cout << (*itrCivilien)->getName() << endl;
				i++;
				countHowManyDelegatesThatEntered++;
				++itrCivilien;
			}
			cout << "The presentage of votes are:" << thePresentageOfTheCivilienWhoVote << "%" << endl;
			cout << "The amount of votes are:" << (*itrParty)->getTheArrOfTheDelegates()[_serialPerDistrict].getAmountOfVotersPerParty() << endl;
			++itrParty;
		}
		if (countHowManyDelegatesThatEntered != _delegates)
		{
			cout << "The capacity of the delegates are not full" << endl;
			exit(1);
		}
		arr[party->getNumOfTheParty()].getSumOfDelegateThatEarned() += countHowManyDelegatesThatEntered;
		int presentageOfVotesToDistrict = (_amountOfVoters * 100) / _sizeOfCivilien;
		
		cout << "The presentage of votes to district " << _name << " are: " << presentageOfVotesToDistrict << "%" << endl;
	}


	void DevidedDistrict::CalculateTheAmountOfDelegatesPerParty(ListPoliticalParty& lstPolParty, ArrCandidate* arr, PoliticalParty* party, ArrCandidate* tempArr)
	{
		ListT<PoliticalParty>::Iterator itrParty = lstPolParty.getList().begin();
		int j = 0;
		int countHowManyDelegatesThatEntered = 0;
		while (itrParty != nullptr)
		{
			int i = 0;
			double thePresentageOfTheCivilienWhoVote = (((*itrParty)->getTheArrOfTheDelegates()[getSerial()].getAmountOfVotersPerParty() * 100) / getAmountOfVoters());
			tempArr[j].getPresantageOfVotes() = thePresentageOfTheCivilienWhoVote;
			int numOfTheDelegateToParty = static_cast<int>(((getDelegates() * thePresentageOfTheCivilienWhoVote) / 100) + 0.5);
			ListT<Civilien>::Iterator itrCivilien = (*itrParty)->getTheArrOfTheDelegates()[getSerial()].getList().begin();
			if (numOfTheDelegateToParty > getDelegates())
			{
				cout << "There Are to few delegates to the party:" << (*itrParty)->getNameOfTheParty() << " in this district" << endl;
				return;
			}
			while (itrParty != nullptr && i < numOfTheDelegateToParty)
			{
				arr[j].getSumOfDelegateThatEarned()++;
				tempArr[j].getSumOfDelegateThatEarned()++;
				i++;
				countHowManyDelegatesThatEntered++;
				++itrCivilien;
			}
			j++;
			++itrParty;
		}
		if (countHowManyDelegatesThatEntered != getDelegates())
		{
			cout << "The capacity of the delegates are not full" << endl;
			exit(1);
		}
		bubbleSort(tempArr);
		ListT<PoliticalParty>::Iterator itrParty1 = lstPolParty.getList().begin();
		j = PoliticalParty::getNum() - 1;
		while (itrParty1 != nullptr)
		{
			if (tempArr[j].getSumOfDelegateThatEarned() != 0) {
				cout << "The delegates to Candiate " << tempArr[j].getCandidate()->getName() << " are:";
				cout << tempArr[j].getSumOfDelegateThatEarned() << endl;
				cout << "The presentage of votes are:" << tempArr[j].getPresantageOfVotes() << "%" << endl;
				cout << "The amount of votes are:" << tempArr[j].getSumOfVotesThatEarned() << endl;
			}
			j--;
			++itrParty1;
		}
		int presentageOfVotesToDistrict = (getAmountOfVoters() * 100) / getSizeOfCivilien();
		cout << "The presentage of votes are:" << presentageOfVotesToDistrict << "%" << endl;
	}

	void District::save(std::ostream& o) const
	{
		int len = _name.length();
		o.write(rcastcc(&len), sizeof(len));
		o.write(rcastcc(&_name[0]), len);
		o.write(rcastcc(&_serial), sizeof(_serial));
		o.write(rcastcc(&_serialPerDistrict), sizeof(_serialPerDistrict));
		o.write(rcastcc(&_delegates), sizeof(_delegates));
		o.write(rcastcc(&_sizeOfCivilien), sizeof(_sizeOfCivilien));
		_pVotersList->save(o);
		o.write(rcastcc(&_amountOfVoters), sizeof(_amountOfVoters));
	}

	void District::load(std::istream& i)
	{
		int len;
		i.read(rcastc(&len), sizeof(len));
		_name.resize(len + 1);
		i.read(rcastc(&_name[0]), len);
		i.read(rcastc(&_serial), sizeof(_serial));
		i.read(rcastc(&_serialPerDistrict), sizeof(_serialPerDistrict));
		i.read(rcastc(&_delegates), sizeof(_delegates));
		i.read(rcastc(&_sizeOfCivilien), sizeof(_sizeOfCivilien));
		_pVotersList = new ListCiviliens();
		_pVotersList->load(i,this);
		i.read(rcastc(&_amountOfVoters), sizeof(_amountOfVoters));
	}


	void DevidedDistrict::save(std::ostream& o) const
	{
		District::save(o);
	}

	void DevidedDistrict::load(std::istream& i)
	{
		if (!i.good())
			throw LoadException();
		District::load(i);
	}
}


