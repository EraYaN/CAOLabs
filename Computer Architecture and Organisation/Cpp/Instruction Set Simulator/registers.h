#ifndef _REGISTERS_H_
#define _REGISTERS_H_
#define NUM_REGS 32
class Registers
{
	int PC;
	int regs[NUM_REGS];
public:
	Registers();

	void setRegister(int regNum, int value);
	int getRegister(int regNum);
	void setPC(int value);
	int getPC();
	void print();
	void incPC();
};

#endif	/* _REGISTERS_H_ */
