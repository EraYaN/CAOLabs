#include <iostream>
#include "registers.h"

using namespace std;

Registers::Registers ()
{
	this->PC = 0;
	for(int i = 0; i<NUM_REGS; i++){
		this->regs[i] = 0;
	}
}

int Registers::getPC(){
	return this->PC;	
}

void Registers::setPC(int value){
	this->PC = value;
}

void Registers::incPC(){
	this->PC++;
}

void Registers::setRegister(int regNum, int value){
	if(regNum>=NUM_REGS||regNum<1){
		if(regNum!=0)
			cout << "Wrong register address." << endl;
		return;
	}
	this->regs[regNum] = value;
}

int Registers::getRegister(int regNum){
	if(regNum>=NUM_REGS||regNum<1){
		if(regNum!=0)
			cout << "Wrong register address." << endl;
		return 0;
	}
	return this->regs[regNum];
}

void Registers::print(){
	cout << "PC: " << this->PC << endl;
	for(int i = 0; i<NUM_REGS; i++){
		cout << "reg" << i << ": " << this->regs[i] << endl;
	}
}