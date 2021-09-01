#include </data/data/com.termux/files/home/regular/stdc++.h>
#include "./nfa.cpp"
using namespace std;
class Parser{
	public:
		Parser(ifstream& fin){
			string x;
			while(fin >> x){
				for(int i = 0;i<x.size();i++){
					input+=x[i];
				}

			}
		}
		NDA expr(){
			
			NDA next = nextterm();
			NDA right = rightexpr();
			return either(next,right);
		}
		NDA rightexpr(){
			if(pointer<input.size() and input[pointer] == '|'){
				match('|');
				NDA next = nextterm();
				NDA right = rightexpr();
			
				return either(next,right);
				
			}
			return one_character(':');
		}
		NDA nextterm(){
			NDA terma = term();
			NDA right = rightterm();
			return concatenate(terma,right);
		}
		NDA rightterm(){
			if (pointer < input.size() and input[pointer]!='|' and input[pointer]!=')' and ('a' <=input[pointer] and input[pointer]<= 'z' || input[pointer] == '(')){
				NDA terma = term();
				NDA rightterma = rightterm();
				return concatenate(terma,rightterma);
			}
			return one_character(':');
			
		}
		NDA term(){
			NDA factora = factor();
			if(pointer < input.size() and input[pointer]  == '*' ){
				match('*');
				return star(factora);
			}else{
				return factora;
			}	
		}
		NDA factor(){

			if(pointer<input.size() and input[pointer] == '('){
				match('(');
				NDA expression = expr();
				match(')');
				return expression;
			}else if(pointer < input.size() and 'a'<=input[pointer] and input[pointer] <='z' and input[pointer]!=')' and input[pointer]!='|'){

				char t = input[pointer];
				match(input[pointer]);
				return one_character(t);
			}
			return one_character(':');
		}
		NDA parse(){
			pointer =0 ;
			return expr();
		}
		void match(char t){
			if(pointer < input.size() and input[pointer] == t){
				pointer+=1;
			}else{
				cout << "syntax error at " << pointer << "\n";
			}
		}
	private:
		string input;
		int pointer;
};


int main(){
	ifstream fin;
	fin.open("input.txt",ios::in);
	string input;
	fin >> input;
	Parser pars(fin);
	cout << pars.parse().simulate(input);

}
