#include "OriInstruction.h"


OriInstruction::OriInstruction(int _regResult, int _regOp1, int _regOp2)
{
	this->regResult = _regResult;
	this->regOp1 = _regOp1;
	this->regOp2 = _regOp2;
}


OriInstruction::~OriInstruction(void)
{
}

void OriInstruction::disassemble(){
	cout << "ori $" << this->regResult << ", $" << this->regOp1 << ", " << this->regOp2 << endl;
}

int OriInstruction::execute(Registers *r){
	int result = r->getRegister(this->regOp1) | this->regOp2;
	r->setRegister(this->regResult,result);
	//r->incPC();
	return r->getPC()+1;
}