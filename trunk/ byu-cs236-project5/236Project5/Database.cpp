#include "Database.h"
#include "Graph.h"
#include <iostream>



Database::Database(void){}
Database::~Database(void){}

Database::Database(std::vector<Scheme> s, std::vector<Fact> f, std::vector<Rule> r, std::vector<Query> q){

	std::vector<Scheme>::iterator it;
	std::vector<Fact>::iterator factIter;
	std::vector<Query>::iterator queryIter;
	myRules = r;
	
    for ( it = s.begin() ; it < s.end(); it++ )
		database[it->getName()] = Relation(it->getName(), it->getAttributes());
    
	for ( factIter = f.begin(); factIter < f.end(); factIter++)
		database[factIter->getName()].addTuple(*factIter);

	//ProcessRules(r);
	
	for ( queryIter = q.begin(); queryIter < q.end(); queryIter++)
		ProcessQuery(*queryIter, r);

}

void Database::ProcessQuery(Query q, std::vector<Rule> rules){

	std::vector<Token> ProjectTokens;
	std::vector<Tuple> SelectTuples;
	std::vector<Token> queryTokens = q.getAttributes();
	Graph dependsOn = Graph(q.getName(), rules);

	std::vector<std::string> ruleList = dependsOn.makeList();
	Cycles optimizedCycles = dependsOn.getCycles();
	Cycle activeCycle;
	bool isInaCycle = false;
	bool shouldProcessRules = false;
	std::vector<Rule> ruleVector;

	for (int i = 0; i < ruleList.size(); i++){

		std::vector <Rule> rulebyID = getRulebyID(ruleList.at(i));
			for(int k = 0; k < rulebyID.size(); k++)
				ruleVector.push_back(rulebyID.at(k));

		if(!isInaCycle){
			for (int j = 0; j < optimizedCycles.size(); j++) {
				if (ruleList.at(i) == optimizedCycles.at(j).first){
					isInaCycle = true;
					activeCycle =  optimizedCycles.at(j);

				}
			}

			if(!isInaCycle){
				shouldProcessRules = true;
			}

		} else {

			if(ruleList.at(i) == activeCycle.second){
				shouldProcessRules = true;
			}
		}

		if(shouldProcessRules || i == ruleList.size() - 1){
			ProcessRules(ruleVector);
			ruleVector.clear();
			isInaCycle = false;
			shouldProcessRules = false;
		}

	}
	
	Relation r = Relation(database[q.getName()].Rename(q.getAttributes()));
	std::vector<Token>::iterator it;

	for(it = queryTokens.begin(); it < queryTokens.end(); it++){

		if(it->getTokenType() == STRING)
			SelectTuples.push_back(Tuple(r.getSchema(), q.getAttributes()));
		else 
			ProjectTokens.push_back(*it);
	}

	for(int i = 0; i < SelectTuples.size(); i++)
		r = r.Select(SelectTuples[i]);
	

	if(ProjectTokens.size() != 0)
		r = r.Project(ProjectTokens);
	
	std::cout << q.toString();
	if(r.getTupleSet().getTuples().size() == 0)
		std::cout << " No\n";
	else
		std::cout << " Yes(" << r.getTupleSet().getTuples().size() << ")\n";


	if(ProjectTokens.size() != 0)
		std::cout << r.toString();
}

bool Database::ProcessRule(Rule r){
	
	Relation joinedPredicates = ProcessPredicate(r.getPredicateNames().at(0), r.getPredicatesAttributes().at(0));

	for(unsigned int i = 1; i < r.getPredicateNames().size(); i++){
			Relation temp = ProcessPredicate(r.getPredicateNames().at(i), r.getPredicatesAttributes().at(i));
			joinedPredicates = joinedPredicates.Join(temp);
	}

	joinedPredicates = joinedPredicates.Project(Schema(r.getHead().getAttributes()));

	return database[r.getHead().getName()].Union(joinedPredicates);						// returns true if something was added to the database

}

void Database::ProcessRules(std::vector<Rule> r){

	std::vector<Rule>::iterator ruleIter;
	bool addedSomething;

	do {
		addedSomething = false;

		for ( ruleIter = r.begin(); ruleIter < r.end(); ruleIter++) {
			if(ProcessRule(*ruleIter))
				addedSomething = true;
		}
	} while (addedSomething);
}

Relation Database::ProcessPredicate(std::string name, std::vector<Token> attributes){
	std::vector<Token> ProjectTokens;
	std::vector<Tuple> SelectTuples;
	Relation r = Relation(database[name].Rename(attributes));
	std::vector<Token>::iterator it;

	for(it = attributes.begin(); it < attributes.end(); it++){

		if(it->getTokenType() == STRING)
			SelectTuples.push_back(Tuple(r.getSchema(), attributes));
		else
			ProjectTokens.push_back(*it);

	}

	for(int i = 0; i < SelectTuples.size(); i++)
		r = r.Select(SelectTuples[i]);
	
	if(ProjectTokens.size() != 0)
		r = r.Project(ProjectTokens);

	return r;

}

std::vector <Rule>  Database::getRulebyID(std::string s){
	std::vector<Rule> temp;
	for(int i = 0; i < myRules.size(); i++){
		if(s == myRules.at(i).getHead().getName())
			temp.push_back(myRules.at(i));
	}

	return temp;
}


std::string Database::toString(){
	std::string temp;

	std::map<std::string, Relation>::iterator iter;

	  for(iter = database.begin(); iter != database.end(); iter++) {
		  temp += iter->second.toString() + "\n";
	  }

	return temp;
}
