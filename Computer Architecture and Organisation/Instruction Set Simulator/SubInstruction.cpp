#include "SubInstruction.h"


SubInstruction::SubInstruction(int _regResult, int _regOp1, int _regOp2)
{
	this->regResult = _regResult;
	this->regOp1 = _regOp1;
	this->regOp2 = _regOp2;
}


SubInstruction::~SubInstruction(void)
{
}

void SubInstruction::disassemble(){
	cout << "sub $" << this->regResult << ", $" << this->regOp1 << ", $" << this->regOp2 << endl;
}

int SubInstruction::execute(Registers *r){
	int result = r->getRegister(this->regOp1)-r->getRegister(this->regOp2);
	r->setRegister(this->regResult,result);
	return r->getPC()+1;
}