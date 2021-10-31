#pragma once
#include <fstream>
#include "ArrCandidate.h"
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>
using namespace std;

namespace election {
	class ListDistrict;
	class ListPoliticalParty;
	class ListCiviliens;
	class PoliticalParty;
	class District
	{
	private:
		friend class ListDistrict;
		string _name;//""						//the name of the district
		static int _serial;//0					//index that count how many district there are
		int _serialPerDistrict;	//0				//the num of the district per district
		int _delegates;//0						//the amount of the delegates
		ListCiviliens* _pVotersList;//nullptr	//the amount of civilines per district that saves as list
		int _sizeOfCivilien;//0					//the size of the list
		int _amountOfVoters;//0					//the amoubt of the voters per district
		int _typeOf;//0							//index that shows us the type of the district
	public:
		District() = default;//ctor
		District(const string name, int delegates);//cons
		District(const District& district);//copy cons
		virtual ~District();//dtor
		void add(Civilien* civilien);//adding cevilien to the district 
		/**********************Geters*************************/
		string getName()const { return _name; }
		int getDelegates() const { return _delegates; }
		int getSerial() const { return _serialPerDistrict; }
		int getSizeOfCivilien() const { return _sizeOfCivilien; }
		static int getNumOfDistrict() { return _serial; }
		int getAmountOfVoters() const { return _amountOfVoters; }
		virtual int getTypeOf() const { return _typeOf; }
		virtual void setTypeOf(int num) { _typeOf = num; }
		ListCiviliens* getListOfVotersPerDistrict() const { return _pVotersList; }
		/**********************Seters*************************/
		void setAmountOfVoters() { _amountOfVoters++; }
		//printers
		void printDistrict(int typeElection);
		void printListCiviliens(int typeElection);
		virtual void save(std::ostream& o) const;//save the detailse of district to a file
		virtual void load(std::istream& i);//load the detailse from a file to the district

		//find the candidate that won in the district
		PoliticalParty* findMaxPerDistrict(ListPoliticalParty& lstPolParty, ArrCandidate* arr, ArrCandidate* tempArr);
		//calculating the amount of the delegates per political party
		virtual void CalculateTheAmountOfDelegatesPerParty(ListPoliticalParty& lstPolParty, ArrCandidate* arr, PoliticalParty* party, ArrCandidate* tempArr);
	};

	class DevidedDistrict :public District
	{
	private:
		int _typeOf;//the type of the district
	public:
		virtual ~DevidedDistrict();
		DevidedDistrict() = default;//ctor
		DevidedDistrict(string name, int delegates) :District(name, delegates), _typeOf(1) {}//ctor
		//calculating the amount of the delegates per political party
		virtual void CalculateTheAmountOfDelegatesPerParty(ListPoliticalParty& lstPolParty, ArrCandidate* arr, PoliticalParty* party, ArrCandidate* tempArr);
		virtual void save(std::ostream& o) const;//save the detailse of the devided district
		virtual void load(std::istream& i);//load from a file to the devided distirct
		virtual int getTypeOf() const { return _typeOf; }//get
		virtual void setTypeOf(int num) { _typeOf = num; }//set
	};
}

