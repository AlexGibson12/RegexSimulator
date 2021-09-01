#include <bits/stdc++.h>
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
		string expr(){
			
			string next = nextterm();
			string right = rightexpr();
			if(right.size()!=0){
				return '(' + next + ')' + '|' + '(' + right + ')';

			}else{
				return next;
			}
		}
		string rightexpr(){
			if(pointer<input.size() and input[pointer] == '|'){
				match('|');
				string next = nextterm();
				string right = rightexpr();
				if(right.size()!=0){
					cout << "here";
					cout << next << "\n" << right << "\n";
					return '(' + next + ')' + '|' + '(' + right + ")";
				}else{
					return next;
				}
			}
			return "";
		}
		string nextterm(){
			string terma = term();
			string right = rightterm();
			if (right.size()!=0){
			return  terma + right ;
			
			}else{
				return terma;
			}
		}
		string rightterm(){
			if (pointer < input.size() and input[pointer]!='|' and input[pointer]!=')' and ('a' <=input[pointer] <= 'z' || input[pointer] == '(')){
				string terma = term();
				string rightterma = rightterm();
				if(rightterma.size()!=0){
					return  terma   + rightterma ;
				}else{
					return terma;
				}
			}
			return "";
			
		}
		string term(){
			string factora = factor();
			if(pointer < input.size() and input[pointer]  == '*' ){
				match('*');
				return '(' + factora + ')' + '*';
			}else{
				return factora;
			}	
		}
		string factor(){

			if(pointer<input.size() and input[pointer] == '('){
				match('(');
				string expression = expr();
				match(')');
				return expression;
			}else if(pointer < input.size() and 'a'<=input[pointer] <='z' and input[pointer]!=')' and input[pointer]!='|'){

				string t(1,input[pointer]);
				match(input[pointer]);
				return t;
			}
			return "";
		}
		string parse(){
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
	Parser pars(fin);
	cout << pars.parse();

}
