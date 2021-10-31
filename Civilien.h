#pragma once
#include <fstream>
using namespace std;
#define rcastcc reinterpret_cast<const char*>
#define rcastc reinterpret_cast<char*>

namespace election {
	class District;
	class Civilien
	{
	private:
		string _name;//name of the civilien
		int _id;//the id
		int _birthYear;//birth year
		District* _district;//pointer to a district that the civilien from
		bool _isVoted;//checking if the civilien is already voted
		bool _isDelegate;//checking if the cevilien is a delegate of a political party
		bool _isCandidate;//checking if the civilien is a candidate of a political party 
	public:
		Civilien() = default;//ctor
		Civilien(District* district) : _district(district), _isVoted(false), _isDelegate(false), _isCandidate(false), _id(0), _birthYear(0), _name(""){}//ctor
		Civilien(const string name, int id, int birthYear, District* district);//ctor
		Civilien(const Civilien& civilien);//copy ctor
		~Civilien() = default;//delete
		/**********************Geters*************************/
		int getID()const { return _id; }
		int getBirthYear()const { return _birthYear; }
		string getName()const { return _name; }
		District* getDistrict()const { return _district; }
		bool& getIsVoted() { return _isVoted; }
		bool& getIsDelegate() { return _isDelegate; }
		bool& getIsCandidate() { return _isCandidate; }
		//prints
		void printCivilien();


		void save(std::ostream& o);//save the detailse of the civilien to the file
		void load(std::istream& i, District* district);//load from a file the detailse of the civilien


	};

}

