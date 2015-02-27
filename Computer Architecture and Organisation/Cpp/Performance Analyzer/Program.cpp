#include "Program.h"
#include <iostream>
#include <math.h>

using namespace std;

Program::Program(int numA, int numS, int numL, int numB)
{
	this->numArith = numA;
	this->numBranch = numB;
	this->numLoad = numL;
	this->numStore = numS;
	this->numTotal = numA+numB+numL+numB;
}
Program::Program(int numT, double fracA, double fracS, double fracL)
{
	this->numArith = floor(numT*fracA+0.5);
	this->numBranch = floor(numT*(1-(fracA+fracS+fracL))+0.5);
	this->numLoad = floor(numT*fracL+0.5);
	this->numStore = floor(numT*fracS+0.5);
	this->numTotal = floor(numT+0.5);
}


Program::~Program(void)
{
}

void Program::printStats(void){
	cout << "Program Stats" << endl;
	cout << "=====" << endl;
	cout << "#Arith: " << this->numArith << endl;
	cout << "#Branch: " << this->numBranch << endl;
	cout << "#Load: " << this->numLoad << endl;
	cout << "#Store: " << this->numStore << endl;
	cout << "#Total: " << this->numTotal << endl;	
}
