#include <iostream>
#include "Computer.h"
#include "Program.h" 

using namespace std;

Computer::Computer(double crGHz, double cpiA, double cpiB, double cpiL, double cpiS){
	//construct
	this->clockRateGHz = crGHz;
	this->cpiArith = cpiA;
	this->cpiBranch = cpiB;
	this->cpiLoad = cpiL;
	this->cpiStore = cpiS;
}
Computer::~Computer(){
	//destruct
}
void Computer::printStats(){
	cout << "Computer Stats" << endl;
	cout << "=====" << endl;
	cout << "CPI Arith: " << this->cpiArith << endl;
	cout << "CPI Branch: " << this->cpiBranch << endl;
	cout << "CPI Load: " << this->cpiLoad << endl;
	cout << "CPI Store: " << this->cpiStore << endl;
	cout << endl;
	cout << "Global CPI: " << this->calculateGlobalCPI() << endl;
}

double Computer::calculateGlobalCPI(){
	return (this->cpiArith+this->cpiBranch+this->cpiLoad+this->cpiStore)/4;
}

double Computer::calculateExecutionTime(Program *p){
	return (this->cpiArith*p->numArith+
		this->cpiBranch*p->numBranch+
		this->cpiLoad*p->numLoad+
		this->cpiStore*p->numStore)*(1/this->clockRateGHz);
}

double Computer::calculateMIPS(Program *p){
	return p->numTotal/this->calculateExecutionTime(p)*1000; // 1000 because G / M = k
}
