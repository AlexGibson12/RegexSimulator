#include <bits/stdc++.h>
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
	private:
		set<int> startingstates;
		set<int> finishedstates;
		set<char> alphabet;
		set<int> mappedstates;
		map<pair<int,char>,vector<int>> statevalues;
};
int main(){
	set<char> alphabet {'1','0'};
	map<pair<int,char>,vector<int>> statevalues;
	pair<int,char> node01 = {0,'1'};
	pair<int,char> node00 = {0,'0'};
	pair<int,char> node10 = {1,'0'};
	pair<int,char> node11 = {1,'1'};
	pair<int,char> node20 = {2,'0'};
	pair<int,char> node21 = {2,'1'};
	statevalues[node01] = vector<int>{0};
	statevalues[node00] = vector<int>{0,1};	
	statevalues[node10] = vector<int>{2};
	statevalues[node11] = vector<int>{3};
	statevalues[node20] = vector<int>{3};
	statevalues[node21] = vector<int>{3};
	set<int> startstates = {0};
	set<int> finishedstates = {2};
	NDA nda(alphabet,startstates,finishedstates,statevalues);
	cout << nda.simulate("010100");
	cout << "hey" << "\n";
}	

