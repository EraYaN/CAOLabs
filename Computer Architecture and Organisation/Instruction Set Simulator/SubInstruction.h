#pragma once
#include "instruction.h"
class SubInstruction :
	public Instruction
{
	int regResult;
	int regOp1;
	int regOp2;
public:
	SubInstruction(int _regResult, int _regOp1, int _regOp2);
	~SubInstruction(void);
	void disassemble();
	int execute(Registers *r);
};

