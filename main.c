#include "keypad.h"

#define DATA1		0
#define DATA2		8
#define DATA3		16
#define DATA4		24

unsigned char* getData(unsigned char* dataUsers, unsigned int address);
void inputData(unsigned char* arrayInput, int counter, unsigned char getKey);
int checkData(unsigned char checkKey, unsigned char* dataUser, int counterId, int address);
unsigned int compareData(unsigned char* arrayInput, unsigned char* arrayData, unsigned int shift);

void main(void)
{
	unsigned char dataUsers[32];
	unsigned char inputUserId[4];
	unsigned char inputPassword[4];
	getData(dataUsers, DATA1);
	unsigned char getKey = 0;
	int  errorFlag = 0;
	int  trueUser = 0;
	int step2 = 0, step1 = 0;
	InitKeypad();
	int index = 0;
	while (1)
	{
		getKey = KEYPAD_GetKey();
		__delay_ms(100);

		if (getKey == 0xB || getKey == 0xD)
		{
			if (getKey == 0xB)
			{
				step1 = 1;
			}
			else if (getKey == 0xD && step1 == 1 && step2 != 1)
			{
				step2 = 1;
				index = 0;
			}
			else
			{
				errorFlag = 1;
			}
		}
		else if (getKey != 0xA && step2 == 0 && step1 == 1) {
			inputData(inputUserId, index, getKey);
			index++;
			if (index == 4)
			{
				if (!compareData(inputUserId, dataUsers, DATA1))
				{
					trueUser = DATA1;
				}
				else if (!compareData(inputUserId, dataUsers, DATA2))
				{
					trueUser = DATA2;
				}
				else if (!compareData(inputUserId, dataUsers, DATA3))
				{
					trueUser = DATA3;
				}
				else if (!compareData(inputUserId, dataUsers, DATA4))
				{
					trueUser = DATA4;
				}
			}
		}
		else if (getKey != 0xA && step1 == 1 && step2 == 1)
		{
			inputData(inputPassword, index, getKey);
			index++;
			if (index == 4)
			{
				if (!compareData(inputPassword, dataUsers, trueUser + 4))
				{
					PORTA = 0x00;
					__delay_ms(500);
					getKey = 0x0A;
					index = trueUser = step2 = 0;
				}
				else
				{
					errorFlag = 1;
				}
			}
		}
		else if (errorFlag == 1)
		{
			index = trueUser = step2 = errorFlag = 0;
			PORTA = 0x0E;
			__delay_ms(500);
		}

		PORTA = getKey;
		__delay_ms(100);

	}
}


unsigned char* getData(unsigned char* dataUsers, unsigned int address) {
	int counter = 0;
	while (counter<32) {
		dataUsers[counter] = EEPROM_READ(address + counter);
		counter++;
	}
	return dataUsers;
}

int checkData(unsigned char checkKey, unsigned char* dataUser, int counterId, int address)
{
	if (dataUser[counterId + address] == (char)checkKey) {
		return 0;
	}
	return 1;
}

void inputData(unsigned char* arrayInput, int counter, unsigned char getKey)
{
	arrayInput[counter] = getKey;
}


unsigned int compareData(unsigned char* arrayInput, unsigned char* arrayData, unsigned int shift)
{
	int index = 0;
	do
	{
		if (arrayInput[index] == arrayData[shift + index])
			index++;
		else
			return 1;
	} while (index < 4);
	return 0;
}