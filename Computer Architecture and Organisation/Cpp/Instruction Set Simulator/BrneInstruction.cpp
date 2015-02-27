#include "BrneInstruction.h"


BrneInstruction::BrneInstruction(int _regOp1, int _regOp2, int _regDisplacement)
{
	this->regOp1 = _regOp1;
	this->regOp2 = _regOp2;
	this->regDisplacement = _regDisplacement;
}


BrneInstruction::~BrneInstruction(void)
{
}

void BrneInstruction::disassemble(){
	cout << "brne $" << this->regOp1 << ", $" << this->regOp2 << ", " << this->regDisplacement << endl;
}

int BrneInstruction::execute(Registers *r){
	int PC = r->getPC();
	if(r->getRegister(this->regOp1)!=r->getRegister(this->regOp2)){			
		PC += 1 + this->regDisplacement;
		//r->setPC(PC);
	} else {	
		PC = r->getPC()+1;
	}
	return PC;
}
