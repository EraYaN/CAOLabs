#include <iostream>
#include "Computer.h"
#include "Program.h" 

using namespace std;

int main(){
	Computer *c1 = new Computer(1,2,4,2,3);
	Computer *c2 = new Computer(1.2,4,3,2,4);
	Computer *c3 = new Computer(2,2,6,2,4);
	int numCs = 3;
	Computer *cs[] = {c1,c2,c3};
	Program *pA = new Program(2000,100,100,50);
	Program *pB = new Program(2000,0.1,0.4,0.25);
	Program *pC = new Program(500,100,2000,200);
	Program *ps[] = {pA,pB,pC};
	int numPs = 3;
	
	cout << "Computers" << endl;
	for(int i=0; i<numCs; i++){
		cout << "c" << i << " data" << endl;
		cs[i]->printStats();
		cout << endl << endl;
	}

	cout << "Programs" << endl;
	for(int i=0; i<numPs; i++){
		cout << "p" << i << " data" << endl;
		ps[i]->printStats();
		cout << endl << endl;
	}

	cout << "Simulations" << endl;
	for(int i=0; i<numCs; i++){
		for(int j=0; j<numPs; j++){
			cout << "Sim p" << j << " on c" << i << " outputs" << endl;
			cout << "Ex. Time: " <<cs[i]->calculateExecutionTime(ps[j]) << endl;
			cout << "MIPS: " <<cs[i]->calculateMIPS(ps[j]) << endl;
			cout << endl << endl;
		}
	}

	

#if _DEBUG
	system("pause");
#endif
	return 0;
}