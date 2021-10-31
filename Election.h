#pragma once
using namespace std;
#include "Date.h"
#include "District.h"
#include "ListTemplate.h"
#include "ListPoliticalParty.h"
#include "ListDistrict.h"
#include <fstream>
namespace election {

	class Election
	{
	protected:
		int _kind;
		Date _date;//the date of the round election
		ListDistrict _lstDist;
		ListPoliticalParty _lstParty;
	public:
		Election() = default; //default ctor
		Election(const Date& date, int kind) :_date(date), _kind(kind) {}//copy ctor
		virtual ~Election() = default;//dtor 
		/*********Getters************/
		const Date& getDate() { return _date; }
		virtual const int& getKindElection() = 0;
		virtual ListDistrict& getLstDist() = 0;
		virtual ListPoliticalParty& getLstParty() = 0;
		/**********Setters************/
		void SetDate(const Date& other) { _date = other; }
		void SetKind(int num) { _kind = num; }
		virtual void save(std::ostream& o);//save the detailse of the election to a file
		virtual void load(std::istream& i, int kind);//load from a file the detailse of the election
	};

	class RegularElection :public Election
	{
	public:
		RegularElection(const Date& date) :Election(date, 1)
		{
		}
		RegularElection() = default;
		virtual const int& getKindElection() { return _kind; }
		virtual ListDistrict& getLstDist() { return _lstDist; }
		virtual ListPoliticalParty& getLstParty() { return _lstParty; }
		virtual ~RegularElection() = default;
		void save(std::ostream& o);//save the detailse of the election to a file
		void load(std::istream& i, int kind);//load from a file the detailse of the election
	};

	class SimpleElection :public Election
	{
	public:
		virtual const int& getKindElection() { return _kind; }
		SimpleElection(const int delegates, const Date& date): Election(date, 2)
		{
			District* _oneDist = new DevidedDistrict("New-York", delegates);
			_lstDist.getList().push_back(_oneDist);
			_lstDist.getList().setSize();
		}

		SimpleElection() = default;
		//const District* getDistrict() { return _oneDist; }
		virtual ListDistrict& getLstDist() { return _lstDist; }
		virtual ListPoliticalParty& getLstParty() { return _lstParty; }
		virtual ~SimpleElection() = default;
		void save(std::ostream& o);//save the detailse of the election to a file
		void load(std::istream& i, int kind);//load from a file the detailse of the election
	};




}