#pragma once
#include "instruction.h"
#include "registers.h"
class AddInstruction :
	public Instruction
{
	int regResult;
	int regOp1;
	int regOp2;
public:
	AddInstruction(int _regResult, int _regOp1, int _regOp2);
	~AddInstruction(void);
	void disassemble();
	int execute(Registers *r);
};

