#include </data/data/com.termux/files/home/regular/stdc++.h>
using namespace std;

class NDA{

	public:
		NDA(set<char> alphabeta,set<int> startingstatesa,set<int> finishedstatesa,map<pair<int,char>,vector<int>> statevaluesa){
			alphabet = alphabeta;
			startingstates = startingstatesa;
			finishedstates = finishedstatesa;
			statevalues = statevaluesa;
		}
		bool simulate(string input){
			set<int> currentstates = {};
			for(auto start : startingstates){
				mappedstates.clear();
				for(auto x:eclosure(start)){
					currentstates.insert(x);
				}
			}
			pair<int,char> currentpair;
			set<int> oldstates;
			char token;
			set<int> newstates;
			for(int i = 0;i<input.size();i++){
				token = input[i];
				newstates.clear();
				
				for(auto x: currentstates){
					
					currentpair.first = x;
					currentpair.second = token;
					if(statevalues.find(currentpair) != statevalues.end()){
						for(auto x:statevalues[currentpair]){

							newstates.insert(x);
							
							mappedstates.clear();
							for(auto y:eclosure(x)){
								newstates.insert(y);
							}	
						}
					}
				}
				currentstates = newstates;

			}	
			for(auto x:currentstates){

				if( finishedstates.find(x) != finishedstates.end()){
					return true;
				}
			}
			return false;
		}
		vector<int> eclosure(int state){
			pair<int,char> currentpair;
			currentpair.first = state;
			(currentpair.second) = '.';
			vector<int> states {state};
			mappedstates.insert(state);
			if( statevalues.find(currentpair) != statevalues.end()){
				for(auto x : statevalues[currentpair]){
					
		
					if(mappedstates.find(x) == mappedstates.end()){
						for(auto y: eclosure(x)){
							states.push_back(y);
						}
					}
							
					
				}
				
			}
			return states;
		}
		set<int> startingstates;
		set<int> finishedstates;
		set<char> alphabet;
		set<int> mappedstates;
		map<pair<int,char>,vector<int>> statevalues;
};
NDA star(NDA nda){
	if(nda.alphabet.find(':')!=nda.alphabet.end()){
		return nda;
	}
	map<pair<int,char>,vector<int>> newstates;
	pair<int,char> newpair;
	set<int> states;
	int totalstates; 
	vector<int> news;	
	for(auto state: nda.statevalues){
		newpair.first =(state.first).first + 1;
		newpair.second = (state.first).second;
		news.clear();
		for(auto x: state.second){
			news.push_back(x+1);
		}
		newstates[newpair] =news;
		states.insert((state.first).first);
		for(auto x:state.second){
			states.insert(x);
		}
	}
	totalstates = states.size();
	set<int> startingstates = {0};
	set<int> finishedstates = {totalstates+1};
	for(auto finished:nda.finishedstates){
		newpair.first = finished + 1;
		newpair.second = '.';
		newstates[newpair] = {0,totalstates+1};
		
	}
	newpair.first = 0;
	newpair.second = '.';
	newstates[newpair] = {1,totalstates+1};
	NDA ndaf(nda.alphabet,startingstates,finishedstates,newstates);
	return ndaf;
	
}
NDA concatenate(NDA first,NDA second){
	if(second.alphabet.find(':')!=second.alphabet.end()){
		return first;
		}
	set<char> alphabet;
	for(auto letter : first.alphabet){
		alphabet.insert(letter);
	}
	for(auto letter: second.alphabet){
		alphabet.insert(letter);

	}
	map<pair<int,char>,vector<int>> combinedstatevalues;
	int firststates = 0;
	int totalstates = 0;
	pair<int,char> newpair;
	set<int> firsta;
	set<int> seconda;
	for(auto pair : first.statevalues){
		combinedstatevalues[pair.first] = pair.second;
		
		firsta.insert((pair.first).first);
		for(auto x: pair.second){
			firsta.insert(x);
		}
	}
	firststates = firsta.size();
	for(auto pair :second.statevalues){
		newpair.first = (pair.first).first+firststates;
		newpair.second = (pair.first).second;
		vector<int> vals;
		for(auto x: pair.second){
			vals.push_back(firststates+x);
		}
		combinedstatevalues[newpair] = vals;
		totalstates+=1;
		seconda.insert((pair.first).first);
		for(auto x: pair.second){
			seconda.insert(x);
		}
	}
	totalstates = firsta.size()+seconda.size();
	set<int> startstates = {0};
	for(auto state: first.finishedstates){
		newpair.first = state;
		newpair.second = '.';
		
		for(auto x: second.startingstates){
			combinedstatevalues[newpair] = {x + firststates};
		}
	}	
	
	set<int> finished = {};
	for(auto x: second.finishedstates){
		finished.insert(x+firststates);
	}
	NDA nda(alphabet,startstates,finished,combinedstatevalues);
	return nda;
}

NDA one_character(char t){
	set<char> alphabet {t};
	map<pair<int,char>,vector<int>> statevalues;
	set<int> startstates = {0};
	set<int> finishedstates = {1};
	statevalues[{0,t}] = {1};
	NDA nda(alphabet,startstates,finishedstates,statevalues);
	return nda;
}
NDA either(NDA first, NDA second){
	if(second.alphabet.find(':') != second.alphabet.end()){
       		return first;	 
	}
	set<char> alphabet;
	for(auto x: first.alphabet){
        	alphabet.insert(x);
	}
	for(auto x: second.alphabet){
		alphabet.insert(x);
	}
	map<pair<int,char>,vector<int>> combinedstatevalues;                                                   int firststates = 0;
        int totalstates = 0;
        pair<int,char> newpair;                           set<int> firsta;
        set<int> seconda;         
	vector<int> vals;
	for(auto pair : first.statevalues){     
		vals.clear();
		for(auto x:pair.second){
			vals.push_back(x+1);
		}
		combinedstatevalues[{(pair.first).first+1,(pair.first).second}] = vals;                                                                                                       				firsta.insert((pair.first).first);                for(auto x: pair.second){                                 firsta.insert(x);                         }                                         }
	firststates = firsta.size();                      for(auto pair :second.statevalues){                       newpair.first = (pair.first).first+firststates+1;                                                     newpair.second = (pair.first).second;                                                               vals.clear();                   			for(auto x: pair.second){                                 vals.push_back(firststates+1+x);                                                              }
                combinedstatevalues[newpair] = vals;
                totalstates+=1;
                seconda.insert((pair.first).first);
                for(auto x: pair.second){
                        seconda.insert(x);
                }
        }
        totalstates = firsta.size()+seconda.size()
;
	combinedstatevalues[{0,'.'}] = {};
	for(auto x: first.startingstates){
		combinedstatevalues[{0,'.'}].push_back( x+1);	
	}
	for(auto x: second.startingstates){
		combinedstatevalues[{0,'.'}].push_back( x+firsta.size()+1);
	}
	set<int> start {0};

	set<int> end {};
	for(auto x: first.finishedstates){
		end.insert(x+1);
	}
	for(auto x: second.finishedstates){
		end.insert(x+1+firsta.size());
	}
	NDA nda(alphabet,start,end,combinedstatevalues);
	return nda;
}


