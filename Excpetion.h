#pragma once
#include <iostream>

using namespace std;
namespace election {

	class CivilienException :public exception
	{
	public:
		CivilienException() :exception("there is already a civilian with this id.") {}
	};
	class CandidateException :public exception
	{
	public:
		CandidateException() :exception("this cevilien is already a candidate") {}
	};

	class DeleagetsException :public exception
	{
	public:
		DeleagetsException() :exception("already a delagate") {}
	};

	class DayNegativException :public exception
	{
	public:
		DayNegativException() :exception("Negativ day error") {}
	};
	class MounthException :public exception
	{
	public:
		MounthException() :exception("incorrect mounth") {}
	};

	class DayFloatException :public exception
	{
	public:
		DayFloatException() :exception("there is not a kind of day in this mounth") {}
	};
	class YearException :public exception
	{
	public:
		YearException() :exception("Error year") {}
	};

	class PartyException :public exception
	{
	public:
		PartyException() :exception("there is already a party with this name.") {}
	};

	class LoadFailed :public exception
	{
	public:
		LoadFailed() :exception("there is not a file with this name") {}
	};
	class FailedSimpleElection :public exception
	{
	public:
		FailedSimpleElection() :exception("ERROR:You have chosen a simple round of elections. There are no districts in this round") {}
	};

	class DistrictException :public exception
	{
	public:
		DistrictException() :exception("ERROR: There is already a district by this name.") {}
	};

	class SerialException :public exception
	{
	public:
		SerialException() :exception("Inccorect District num....") {}
	};

	class NegativPartyException :public exception
	{
	public:
		NegativPartyException() :exception("Incorrect political party number") {}
	};

	class AllReadyVotedException :public exception
	{
	public:
		AllReadyVotedException() :exception("The Civilien already voted...") {}
	};

	class Under18Exception :public exception
	{
	public:
		Under18Exception() :exception("The Civilien is to young...") {}
	};
	class LoadException :public exception
	{
	public:
		LoadException() :exception("Cant read The data.") {}
	};
	class IdException :public exception
	{
	public:
		IdException() :exception("Incorrect input for ID.") {}
	};
	class ToFewDelegates :public exception
	{
	public:
		ToFewDelegates() :exception("There Are to few delegates to the party.") {}
	};
}

