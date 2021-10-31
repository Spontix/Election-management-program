#define _CRT_SECURE_NO_WARNINGS

#include <fstream>
#include <iostream>
#include "Election.h"
#include "District.h"
#include "ListDistrict.h"
#include "ListPoliticalParty.h"
#include "PoliticalParty.h"
#include "ArrCandidate.h"
#include "Civilien.h"
#include "ListCivilien.h"
#include "ListTemplate.h"
#include "Excpetion.h"
#include "Date.h"

#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

enum class Choice
{
	District = 1, Civilien, PoiliticalParty, Delegates, ShowDistricts, ShowCiviliens, ShowPoliticalParty, Vote, Resultes, Exit, SaveElection, LoadElection
};
enum class ChoiceOfStartedManue
{
	Create = 1, Load, Exit
};
using namespace std;
using namespace election;
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

void checkIdNumber(int id)
{
	int count = 0;
	while (id != 0)
	{
		id = id / 10;
		count++;
	}
	if (count != 9)
		throw IdException();

}

void setTheArrOfCandidates(ArrCandidate* arr, ListT<PoliticalParty>::Iterator& itrParty)
{
	for (int i = 0; i < PoliticalParty::getNum(); i++)
	{
		arr[i].setCandidate((*itrParty)->getCandidate());//set all the arr to the candidates
		++itrParty;
	}
}
void ElectionType()
{
	cout << "Please choose the election type that you want:" << endl;;
	cout << "1. Normal election round" << endl;;
	cout << "2. Simple election round" << endl;;

}
void ManueChoice()
{
	cout << "choose an option:\n";
	cout << "1. Add district\n";
	cout << "2. Add civilien\n";
	cout << "3. Add civilien to political party\n";
	cout << "4. Add civilien as delegate of political party\n";
	cout << "5. exhibit all the districts:\n";
	cout << "6. exhibit all the civiliens\n";
	cout << "7. exhibit all the political partys\n";
	cout << "8. Vote\n";
	cout << "9. exhibit the resulte of the election\n";
	cout << "10. Exit\n";
	cout << "11.save the round election in file\n";
	cout << "12.Load excisted round election from file.\n";
}
void AddDistrict(ListPoliticalParty& lstPolParty, ListDistrict& lstDist, Election* Election)//Add District to the list
{
	if (Election->getKindElection() == 2)
		throw FailedSimpleElection();
	District* theDistrict;
	cout << "Please insert num of delegates and name of the district" << endl;
	int delegates; string name;
	cin >> name >> delegates;
	cout << "Please insert the kind of the district" << endl;
	int kindOf;
	cin >> kindOf;

	if (!kindOf)
		theDistrict = new District(name, delegates);
	else
		theDistrict = new DevidedDistrict(name, delegates);

	if (lstDist.getList().begin() == nullptr)//if the list is empty,adding without any check
	{
		lstDist.getList().push_back(theDistrict);
		lstDist.getList().setSize();
	}
	else if (!(lstDist.findDistrictByName(name)))
	{
		lstDist.getList().push_back(theDistrict);
		lstDist.getList().setSize();

		if (lstPolParty.getList().begin() != nullptr)
			lstPolParty.setLengthToAllTheParties(District::getNumOfDistrict());//while in the methode that setLength per arr in political party;
	}
	else
	{
		delete theDistrict;
		throw DistrictException();
	}
}
void AddCivilien(ListDistrict& lstDist, Election* Election)
{
	cout << "Please give me the details of the civilien: " << endl;
	int id; string name; int districtNum; int birthYear;
	cin >> name >> id >> birthYear;
	//checkIdNumber(id);
	if (Election->getDate().getYear() - birthYear < 18)
		throw Under18Exception();
	if (Election->getKindElection() == 2)
		districtNum = 0;
	else
		cin >> districtNum;

	District* dist = lstDist.findDistrict(districtNum);//check that the distrtict number is valid
	Civilien* c = new Civilien(name, id, birthYear, dist);
	if (dist != nullptr)
	{
		if (dist->getListOfVotersPerDistrict()->getList().begin() == nullptr)
		{//checking if the List is empty
			dist->add(c);
		}
		else
		{
			Civilien* civilien = lstDist.findCivilien(id);// check that the Civilien is valid
			if (civilien)
			{
				delete c;
				throw CivilienException();
			}
			else
				dist->add(c);
		}
	}
	else
		throw SerialException();
}
void AddPoliticalParty(ListPoliticalParty& lstPolParty, ListDistrict& lstDist)//Adding a poitical party
{
	int Mood = 1;
	cout << "Please insert a political party: " << endl;
	int id; string name;

	cin >> name >> id;
	Civilien* civilien = lstDist.findCivilien(id); //check that the Civilien is valid
	PoliticalParty* party = new PoliticalParty(name, civilien);
	if (civilien != nullptr)
	{
		if (civilien->getIsCandidate())
			throw CandidateException();
		else if (lstPolParty.getList().begin() == nullptr)
		{
			party->setArr(District::getNumOfDistrict() + 1);//set the arr of ListCivilien to the number of the sistricts
			lstPolParty.getList().push_back(party);
			lstPolParty.getList().setSize();
			civilien->getIsCandidate() = true;//turning the status of this specific civilien to a candidate
		}
		else if (!(lstPolParty.findPoliticalPartyByName(name)))
		{
			party->setArr(District::getNumOfDistrict() + 1);
			lstPolParty.getList().push_back(party);//Add the political party to the list
			lstPolParty.getList().setSize();
			civilien->getIsCandidate() = true;//turning the status of this specific civilien to a candidate
		}
		else
		{
			cout << "Political party:" << name << " is already exciste" << endl;
			delete party;
		}
	}
	else
	{
		delete party;
		throw CivilienException();
	}
}

void AddDelegate(ListPoliticalParty& lstPolParty, ListDistrict& lstDist, Election* Election)
{
	cout << "Please insert a delegate to party: " << endl;
	int id; int partyNum; int districtNum;
	cin >> id >> partyNum;
	if (partyNum < 0)
		throw NegativPartyException();

	if (Election->getKindElection() == 2)
		districtNum = 0;
	else
		cin >> districtNum;
	Civilien* civilien = lstDist.findCivilien(id);//check that the Civilien is valid
	District* dist = lstDist.findDistrict(districtNum);//check that the distrtict number is valid
	PoliticalParty* party = lstPolParty.findPoliticalParty(partyNum);//check the politicla party num is valid;
	if (dist == nullptr || civilien == nullptr || party == nullptr)
	{
		if (dist == nullptr)
			throw DistrictException();
		if (civilien == nullptr)
			throw CivilienException();
		if (party == nullptr)
			throw PartyException();
	}
	else
	{
		if (civilien->getIsDelegate())
		{
			throw DeleagetsException();
		}
		civilien->getIsDelegate() = true;
		lstPolParty.setDelegate(party, districtNum, civilien);
	}
}
void AddVoter(ListPoliticalParty& lstPolParty, ListDistrict& lstDist)
{
	cout << "Please enter the civiline that voted" << endl;
	int id; int partyNum;
	cin >> id >> partyNum;
	Civilien* civilien = lstDist.findCivilien(id);//check that the Civilien is valid
	if (!civilien)
		throw CivilienException();
	District* dist = civilien->getDistrict();
	PoliticalParty* party = lstPolParty.findPoliticalParty(partyNum);//check the politicla party num is valid;
	if (dist == nullptr || party == nullptr)
	{
		if (dist == nullptr)
			throw DistrictException();
		if (party == nullptr)
			throw PartyException();
	}
	else if (!(civilien->getIsVoted()))
	{
		civilien->getIsVoted() = true;
		dist->setAmountOfVoters();
		party->setTheArrOfTheDelegates(dist->getSerial());
	}
	else
		throw AllReadyVotedException();
}

void ElectionResults(ListPoliticalParty& lstPolParty, ListDistrict& lstDist, int typeElection)
{
	ListT<PoliticalParty>::Iterator itrParty = lstPolParty.getList().begin();
	ArrCandidate* arr = new ArrCandidate[PoliticalParty::getNum()];//calculates to all the districtd
	setTheArrOfCandidates(arr, itrParty);// arr of only candidates
	ListT<District>::Iterator itrDistrict = lstDist.getList().begin();
	while (itrDistrict != nullptr)//run on all the district
	{
		ListT<PoliticalParty>::Iterator itrParty = lstPolParty.getList().begin();
		ArrCandidate* tempArr = new ArrCandidate[PoliticalParty::getNum()];//calculates for a single dostric
		setTheArrOfCandidates(tempArr, itrParty);
		PoliticalParty* party = (*itrDistrict)->findMaxPerDistrict(lstPolParty, arr, tempArr);
		if (typeElection == 1)
		{
			cout << "The name of district: " << (*itrDistrict)->getName() << endl;
		}
		cout << "The amount of delegates: " << (*itrDistrict)->getDelegates() << endl;
		if (dynamic_cast<DevidedDistrict*>(*itrDistrict))
			(*itrDistrict)->CalculateTheAmountOfDelegatesPerParty(lstPolParty, arr, party, tempArr);
		else
		{
			cout << "The candidate of the political party is: " << party->getCandidate()->getName() << endl;
			(*itrDistrict)->CalculateTheAmountOfDelegatesPerParty(lstPolParty, arr, party, tempArr);
		}
		++itrDistrict;
		delete[] tempArr;
	}
	bubbleSort(arr);
	for (int i = PoliticalParty::getNum() - 1; i >= 0; i--)
	{
		cout << "The candidate " << arr[i].getCandidate()->getName() << " got:";
		cout << arr[i].getSumOfDelegateThatEarned() << " delegates in total." << endl;
	}
	delete[]arr;
}


void SaveElection(ListPoliticalParty& lstPolParty, ListDistrict& lstDist, Election* Election)
{
	cout << "Please enter a file name: " << endl;
	string fileName;
	cin >> fileName;
	std::ofstream outfile(fileName);
	if (!outfile)
		throw LoadFailed();
	int kind = Election->getKindElection();
	outfile.write(rcastcc(&kind), sizeof(kind));
	Election->save(outfile);
	outfile.close();
}

void LoadElection( Election** Election)
{
	string fileName;
	std::ifstream infile;
	int kind;
	cout << "Please enter a file name that you want to load: " << endl;
	cin >> fileName;
	infile = std::ifstream(fileName);//open the file by its name
	if (!infile) //checking if the file is good
		throw LoadFailed();
	infile.read(rcastc(&kind), sizeof(kind));
 	if (kind == 2)
		*Election = new SimpleElection();
	else 
		*Election = new RegularElection();
	(*Election)->load(infile, kind);
	infile.close();
}


void ElectionMain(int Load_Save_Exit)
{
	Election* Election1 = nullptr;
	Date date;//date
	
	switch (static_cast<ChoiceOfStartedManue>(Load_Save_Exit))//the first choice
	{
	case ChoiceOfStartedManue::Create://the user choos to create an election 
	{
		cout << "Please Enter A Date" << endl;
		int d, m, y;
		cin >> d >> m >> y;
		date = Date(d, m, y);//create a date
		ElectionType();//if!2!1 error
		int typeElection;
		cin >> typeElection;
		while (typeElection != 2 && typeElection != 1)
		{
			cout << "ERROR:You choose wrong number" << endl;
			cout << "Please Try Again" << endl;
			cin >> typeElection;
		}
		if (typeElection == 2)
		{
			int amountOfDelegatse;
			try {
				cout << "please enter the amount of delegates:" << endl;
				cin >> amountOfDelegatse;
				Election1 = new SimpleElection(amountOfDelegatse, date);
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
		}
		else if (typeElection == 1)
			Election1 = new RegularElection(date);
	
		break;
	}
	case ChoiceOfStartedManue::Load://the user choos to load a file with the ditailse of the election
	{
		LoadElection(&Election1);
		break;
	}
	case ChoiceOfStartedManue::Exit://the user choos to exit from the program
	{
		exit(-1);
		break;
	}

	}


	int choice;

	ManueChoice();
	cin >> choice;
	while (static_cast<Choice>(choice) != Choice::Exit)//the second choice
	{
		switch (static_cast<Choice>(choice))
		{
		case Choice::District:
			try {
				AddDistrict(Election1->getLstParty(), Election1->getLstDist(), Election1);
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case Choice::Civilien:
			try {
				AddCivilien(Election1->getLstDist(), Election1);
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case Choice::PoiliticalParty:
			try {
				AddPoliticalParty(Election1->getLstParty(), Election1->getLstDist());
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case Choice::Delegates:
			try {
				AddDelegate(Election1->getLstParty(), Election1->getLstDist(), Election1);
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case Choice::ShowDistricts:
			try {
				Election1->getLstDist().printList(Election1->getKindElection());
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case Choice::ShowCiviliens:
			try {
				Election1->getLstDist().printListCivilienInAllDistricts(Election1->getKindElection());
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case Choice::ShowPoliticalParty:
			try {
				Election1->getLstParty().printListPoliticalParty(Election1->getKindElection());
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case Choice::Vote:
			try {
				AddVoter(Election1->getLstParty(), Election1->getLstDist());
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case Choice::Resultes:
			try {
				ElectionResults(Election1->getLstParty(), Election1->getLstDist(), Election1->getKindElection());
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case Choice::Exit:
			break;
		case Choice::SaveElection:
			try
			{
				SaveElection(Election1->getLstParty(), Election1->getLstDist(), Election1);
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		case Choice::LoadElection:
			try {
				LoadElection(&Election1);
			}
			catch (exception& e)
			{
				cout << e.what() << endl;
			}
			break;
		}
		ManueChoice();
		cin >> choice;

	}

}


int main()//the original manue 
{
	cout << "Please select one of the following option: " << endl;
	cout << "For create new round of election enter 1: " << endl;
	cout << "For load an excited round of election enter 2: " << endl;
	cout << "For exit enter 3: " << endl;
	int Load_Save_Exit;
	cin >> Load_Save_Exit;
	try {
		ElectionMain(Load_Save_Exit);
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
	}

}

