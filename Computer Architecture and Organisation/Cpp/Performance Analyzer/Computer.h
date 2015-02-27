#pragma once
#include "Program.h" 

class Computer{
	double clockRateGHz;
	double cpiArith;
	double cpiStore;
	double cpiLoad;
	double cpiBranch;
public:	
	Computer(double crGHz, double cpiA, double cpiB, double cpiL, double cpiS);
	~Computer();

	void printStats();
	double calculateGlobalCPI();
	double calculateExecutionTime(Program *p);
	double calculateMIPS(Program *p);
};