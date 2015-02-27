#pragma once
#include "instruction.h"
class OriInstruction :
	public Instruction
{
	int regResult;
	int regOp1;
	int regOp2;
public:
	OriInstruction(int _regResult, int _regOp1, int _regOp2);
	~OriInstruction(void);
	void disassemble();
	int execute(Registers *r);
};

