#pragma once
#include <htc.h>

#define RowColDirection TRISB //Data Direction Configuration for keypad
#define ROW PORTB   //Lower four bits of P1 are used as ROWs
#define COL PORTB  //Higher four bits of P1 are used as COLs

void InitKeypad(void);
unsigned char KEYPAD_ScanKey(void);
unsigned char KEYPAD_GetKey(void);