#pragma once

using namespace std;


class Program
{
public:
	int numArith;
	int numStore;
	int numLoad;
	int numBranch;
	int numTotal;

	Program(int numA, int numS, int numL, int numB);
	Program(int numT, double fracA, double fracS, double fracL);
	~Program(void);

	void printStats();
};

