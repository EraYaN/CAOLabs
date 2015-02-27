#include <iostream>
#include "simulator.h"
#include "program.h"
#include "registers.h"
#include "AddInstruction.h" 
#include "SubInstruction.h" 
#include "OriInstruction.h" 
#include "BrneInstruction.h" 

void loadProgram (Program *program)
{
	//for(int i = 0; i<$2; i+=$3){$4+=$1;}
	program->appendInstruction (new OriInstruction (1, 0, 12));
	program->appendInstruction (new OriInstruction (2, 0, 10));
	program->appendInstruction (new OriInstruction (3, 0, 1));
	program->appendInstruction (new AddInstruction (4, 4, 1));
	program->appendInstruction (new SubInstruction (2, 2, 3));
	program->appendInstruction (new BrneInstruction (2, 0, -3));
}

using namespace std;

int main (void)
{
	Registers *registers	= new Registers ();
	Program	*program	= new Program ();

	/*registers->setPC(100);
	registers->setRegister(4,5421);
	registers->setRegister(8,1456);
	registers->setRegister(16,8754);
	registers->setRegister(24,6547);
	registers->print();*/
	loadProgram (program);

	Simulator theSimulator = Simulator (registers, program);

	theSimulator.ui();

	//registers->print();

#if _DEBUG
	system("pause");
#endif
	return 0;
}
