#include <iostream>
using namespace std;
int main(){
	int T;
	while(cin>>T){
		int a, total=0;
		for(int i=0; i<5; ++i){
			cin>>a;
			if(a == T) total++;
		}
		cout << total << endl;
	}
	return 0;	
}