#pragma once
#include "instruction.h"
class BrneInstruction :
	public Instruction
{
	int regOp1;
	int regOp2;
	int regDisplacement;
public:
	BrneInstruction(int regOp1, int regOp2, int regDisplacement);
	~BrneInstruction(void);
	void disassemble();
	int execute(Registers *r);
};

