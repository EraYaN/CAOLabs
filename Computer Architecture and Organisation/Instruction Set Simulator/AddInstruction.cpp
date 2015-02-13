#include "AddInstruction.h"


AddInstruction::AddInstruction(int _regResult, int _regOp1, int _regOp2)
{
	this->regResult = _regResult;
	this->regOp1 = _regOp1;
	this->regOp2 = _regOp2;
}


AddInstruction::~AddInstruction(void)
{
}

void AddInstruction::disassemble(){
	cout << "add $" << this->regResult << ", $" << this->regOp1 << ", $" << this->regOp2 << endl;
}

int AddInstruction::execute(Registers *r){
	int result = r->getRegister(this->regOp1)+r->getRegister(this->regOp2);
	r->setRegister(this->regResult,result);
	return r->getPC()+1;
}
