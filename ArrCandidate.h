#pragma once


namespace election {
	class Civilien;
	class ArrCandidate {
	private:
		Civilien* _candidate;
		int _sumOfDelegateThatEarned;//the amount of chairs that earned
		int _sumOfVotesThatEarned;// counting the votes per party
		double _presantageOfVotes;//counting the presntage of the vote per party
	public:
		ArrCandidate();//ctor
		int& getSumOfDelegateThatEarned(){ return _sumOfDelegateThatEarned; }//returning the sum of the delegates that earned 
		int& getSumOfVotesThatEarned() { return _sumOfVotesThatEarned; }//returning the sum of the votes
		double& getPresantageOfVotes(){ return _presantageOfVotes; }// returning the prestage of the votes
		/**********************Geters*************************/
		Civilien* getCandidate(){ return _candidate; }
		/**********************Seters*************************/
		void setCandidate(Civilien* candidate) { _candidate = candidate; }
		void setSumOfDelegateThatEarned(int sumOfDelegateThatEarned) { _sumOfDelegateThatEarned = sumOfDelegateThatEarned; }


	};



}


