#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <iostream>
#include "registers.h"

using namespace std;

class Instruction
{
public:
	Instruction();
	virtual void disassemble() = 0;
	virtual int execute(Registers *r) = 0;
};

#endif /* _INSTRUCTION_H_ */
