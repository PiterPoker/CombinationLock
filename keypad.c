#include "keypad.h"

// Function name: InitKeypad
void InitKeypad(void)
{
	RowColDirection = 0x0F;		// Set PORTB pin values zero
	PORTA = 0xA;
	TRISA = 0;
}

unsigned char KEYPAD_ScanKey()
{

	unsigned char ScanKey = 0x10, i, key;

	for (i = 0; i<0x04; i++)            // Scan All the 4-Rows for key press
	{
		ROW = ScanKey;                // Select 1-Row at a time for Scanning the Key
		key = COL & 0x0F;             // Read the Column, for key press

		if (key != 0x00)               // If the KEY press is detected for the selected
			break;                   // ROW then stop Scanning,

		ScanKey = (ScanKey << 1); // Rotate the ScanKey to SCAN the remaining Rows
	}


	key = key | ScanKey;         // Retun the row and COL status to decode the key
	return(key);
}

unsigned char KEYPAD_GetKey()
{
	unsigned char key;

	__delay_ms(1);

	key = KEYPAD_ScanKey();        // Scan for the key pressed.

	switch (key)                       // Decode the key
	{
	case 0x11: key = '1'; break;
	case 0x12: key = '2'; break;
	case 0x14: key = '3'; break;
	case 0x21: key = '4'; break;
	case 0x22: key = '5'; break;
	case 0x24: key = '6'; break;
	case 0x41: key = '7'; break;
	case 0x42: key = '8'; break;
	case 0x44: key = '9'; break;
	case 0x81: key = 0xB; break;
	case 0x82: key = '0'; break;
	case 0x84: key = 0xD; break;
	default: key = 0xA;
	}
	return(key);                      // Return the key
}